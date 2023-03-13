from numpy import sort
import streamlit as st
import pandas as pd
import hashlib, uuid
from datetime import date as dt, datetime
import io
import utils
import csv
import re
from streamlit_option_menu import option_menu
from st_aggrid import GridOptionsBuilder, AgGrid, GridUpdateMode, DataReturnMode, JsCode


df = pd.DataFrame()

def hasher(col):
    return col.apply(lambda x: hashlib.md5(x.encode('utf-8')).hexdigest() if x is not None else 'N/A')

def convert_df(df, pat):
    if pat:
        return df.to_csv(header = False, index=False, quoting=csv.QUOTE_NONE, escapechar=' ').encode('utf-8')
    else:
        return df.to_csv(index = False, quoting=csv.QUOTE_NONE, escapechar=' ').encode('utf-8')

df_selections = pd.DataFrame()
def set_df(df):
    global df_selections
    df_selections = df

def get_df():
    return df_selections

def df_query(select_list):
    if len(select_list) == 1: #just one cmd
        return select_list[0]

    query = ""
    for i in range(len(select_list)):
        if i+1 == len(select_list): #if last element
            query += select_list[i]
        else:
            query += select_list[i] + ' & '

    return query

def main() -> None:
    st.title("EGFR DASHBOARD")

    col1, col2, col3 = st.columns(3)
    ids = sorted(df['mrn'].unique())
    id_selections = st.sidebar.multiselect('MRN',options=ids)
    all_ids = st.sidebar.checkbox("Select All MRN")

    add_slider = st.sidebar.checkbox("Age Slider")
    age_r = []
    age_d = []
    age_unk = False

    if add_slider:
        age_a, age_b = st.sidebar.columns([3,10])
        with age_a:
            age_slider = st.radio('AGE SLIDER',('Age','Aged','UNK'))
        with age_b:
            if age_slider == 'Age':
                max_age = int(df['current_age'].max())
                age_r = st.slider('CURRENT AGE', 0, round(max_age), (0, 100))
            elif age_slider == 'Aged':
                max_age_d = int(df['aged'].max())
                age_d = st.slider('AGED', 0, round(max_age_d), (0, 100))
            else:
                age_unk = True


    gender = sorted(df['gender'].unique())
    gender_selections = st.sidebar.multiselect('GENDER',options=gender)

    rcs = sorted(df['race_category'].unique())
    rc_selections = st.sidebar.multiselect('RACE CATEGORY',options=rcs)

    diags = sorted(df['submitteddiagnosis'].unique())
    diags_selections = st.sidebar.multiselect('SUBMITTED DIAGNOSIS',options=diags)

    specs = sorted(df['specsite'].unique())
    spec_selections = st.sidebar.multiselect('SPECIMEN SITE',options=specs)

    meds = sorted(df['medication_name'].unique())
    med_selections = st.sidebar.multiselect('MEDICATION NAME',options=meds)

    treats = sorted(df['treatment_plan_name'].unique())
    treat_selections = st.sidebar.multiselect('TREATMENT PLAN',options=treats)

    smokes = df['smoking_history'].unique()
    smoke_selections = st.sidebar.multiselect('SMOKING HISTORY?',options=smokes)

    st.header("")
    if all_ids:
        st.warning("'Select All MRN' MUST BE DESELECTED TO NARROW POPULATION")
    side_stA, side_stB = st.columns([1,10])
    alts_split = df['alterationname'].str.split(',')
    alts = set()
    for row in alts_split:
        row = [i.lstrip() for i in row]
        alts = alts.union(row)
    alts = list(alts)
    alts = sorted(alts, key=str.casefold)

    with side_stA:
        alt_pick = st.radio('FILTER',('Select','Search'))
    with side_stB:
        if alt_pick == 'Search':
            alt_selections = st.text_input('ALTERATION')
        else:
            alt_selections = st.multiselect('ALTERATION',options=alts)

    st.header("")
    st.header("")

    side_a, side_b = st.sidebar.columns([3,9])
    icd_split = list(df['icd10_all'].str.split(';').apply(lambda x: x[-1]).str.split(','))
    icds = set()
    for row in icd_split:
        row = [i.lstrip() for i in row]
        icds = icds.union(row)

    icds = list(icds)
    icds = sorted(icds, key=str.casefold)
    with side_a:
        icd_pick = st.radio('ICD-10 FILTER',('Select','Search'))
    with side_b:
        if icd_pick == 'Search':
            icd_selections = st.text_input('ICD-10')
        else:
            icd_selections = st.multiselect('ICD-10',options=icds)

    if all_ids:
        id_selections = ids

    empty_df = pd.DataFrame(columns=df.columns)
    set_df(empty_df)


    date_c = st.sidebar.date_input("COLLECTION DATE",[], min_value = dt(1950,1,1), max_value=dt.today())
    date_m = st.sidebar.date_input("MEDICATION DATE RANGE",[], min_value = dt(1950,1,1), max_value=dt.today())

    show = False # show selections
    with st.expander("Raw Data"):
        if all_ids:
            set_df(df)
            show = True
        else:
            query_builder = []
            if id_selections:
                query_builder.append('mrn == @id_selections')
            if gender_selections:
                query_builder.append('gender == @gender_selections')
            if rc_selections:
                query_builder.append('race_category == @rc_selections')
            if diags_selections:
                query_builder.append('submitteddiagnosis == @diags_selections')
            if spec_selections:
                query_builder.append('specsite == @spec_selections')
            if med_selections:
                query_builder.append('medication_name == @med_selections')
            if treat_selections:
                query_builder.append('treatment_plan_name == @treat_selections')

            if alt_selections and alt_pick == "Select":
                regex = '''?&|!{}[]()^~*:\\"'+-'''
                replace = ['\\' + l for l in regex]
                alt_clean = str.maketrans(dict(zip(regex, replace)))
                fixed_list = [s.translate(alt_clean) for s in alt_selections]

                query_builder.append('alterationname.str.contains("|".join(@fixed_list),regex=True)')
            elif alt_selections and alt_pick == "Search":
                query_builder.append('alterationname.str.contains(@alt_selections, case=False)')

            if icd_selections and icd_pick == "Select":
                query_builder.append('icd10_all.str.contains("|".join(@icd_selections),regex=True)')
            elif icd_selections and icd_pick == "Search":
                query_builder.append('icd10_all.str.contains(@icd_selections, case=False)')

            if add_slider:
                if len(age_r) == 2:
                    query_builder.append('current_age >= @age_r[0] & current_age <= @age_r[1]')
                if len(age_d) == 2:
                    query_builder.append('aged >= @age_d[0] & aged <= @age_d[1]')
                if age_unk:
                    query_builder.append('current_age.isnull() & aged.isnull()')

            if len(date_c) == 2:
                query_builder.append('colldate >= @date_c[0] & colldate <= @date_c[1]')
            if len(date_m) == 2:
                query_builder.append('firstdose >= @date_m[0] & lastdose <= @date_m[1]')
            if smoke_selections:
                query_builder.append('smoking_history == @smoke_selections')

            query = df_query(query_builder)
            if query != '':
                set_df(df.query(query))
                show = True

        #st.dataframe(get_df())
        gb = GridOptionsBuilder.from_dataframe(get_df())
        options = gb.build()
        grid = AgGrid(
            get_df(),
            gridOptions=options,
            data_return_mode='AS_INPUT',
            update_mode='MODEL_CHANGED',
            fit_rows_on_grid_load=True,
            theme='streamlit', #Add theme color to the table
            height=600,
            width='100%',
        )


    col1.metric("Number of Patients Selected", str(len(set(df_selections['mrn'].unique())))) #set to get unique
    col2.metric("Rows Returned", len(df_selections))

    meta = ''
    if len(age_r) == 2:
        meta += ('Age Range: ' + str(age_r))
    elif len(age_d) == 2:
        meta += ('Aged Range: ' + str(age_d))
    elif age_unk:
        meta += ('Age Range: Unknown')
    else:
        meta += ('Age Range: Not Specified')

    meta += '\t' + ('Gender: ' + str(gender_selections))
    meta += '\t' + ('Race Category: ' + str(rc_selections))
    meta += '\t' + ('Diagnosis: ' + str(diags_selections))
    meta += '\t' + ('Specimen Site: ' + str(spec_selections))
    meta += '\t' + ('Medication: ' + str(med_selections))
    meta += '\t' + ('Treatment Plan: ' + str(treat_selections))
    meta += '\t' + ('Alterations: ' + str(alt_selections))
    meta += '\t' + ('ICD-10: ' + str(icd_selections))
    meta += '\t' + ('Collection Date: ' + str(date_c))
    meta += '\t' + ('Medication Date Range: ' + str(date_m))
    meta += '\t' + ('Smoking History: ' + str(smoke_selections))

    df_csv = get_df()
    csv = convert_df(df_csv, False)
    st.download_button(
        "Export Table",
        csv,
        "data.csv",
        key='download-csv'
    )

    df_pat = get_df()['mrn'].unique()
    df_pat_s = pd.Series(df_pat)
    # store user selections
    df_pat_s.loc[-1] = str(meta)
    df_pat_s.index += 1
    df_pat_s = df_pat_s.sort_index()

    csv_pat = convert_df(df_pat_s, True)
    st.download_button(
        "Export Patient List",
        csv_pat,
        "patient_list.csv",
        key='download-csv'
    )

    if show:
        utils.plot_selections(df_selections)


if __name__ == "__main__":
    st.set_page_config(
        page_title="PCC EGFR Mutations",
        #page_icon="chart_with_upwards_trend",
        layout="wide",
        initial_sidebar_state="expanded",
    )
    st.markdown(
    """
    <style>
    [data-testid="stSidebar"][aria-expanded="true"] > div:first-child{
        width: 400px;
    }
    """,
    unsafe_allow_html=True,
    )
    df = utils.get_full_df()
    main()



import streamlit as st 
import icd10
import pandas as pd
import sys
from datetime import date as dt, datetime
from streamlit_option_menu import option_menu
from st_aggrid import GridOptionsBuilder, AgGrid, GridUpdateMode, DataReturnMode, JsCode
import csv
import utils
import io
import pyodbc
import plotly.express as px
import plotly.graph_objects as go
import calendar


df = pd.DataFrame()

####################################
df_selections = pd.DataFrame()
def set_df(df):
    global df_selections
    df_selections = df

def get_df():
    return df_selections    

def df_query(select_list):
    if len(select_list) == 1: 
        return select_list[0]
    
    query = ""
    for i in range(len(select_list)):
        if i+1 == len(select_list): 
            query += select_list[i]
        else:
            query += select_list[i] + ' & '

    return query


def convert_df(df, pat):
    if pat:
        return df.to_csv(header = False, index=False, quoting=csv.QUOTE_NONE, escapechar=' ').encode('utf-8')
    else:
        return df.to_csv(index = False, quoting=csv.QUOTE_NONE, escapechar=' ').encode('utf-8')

####################################


def main() -> None:
    st.title("Surgical Oncology Charges Dashboard")

    id_selections = []
    uploaded_file = []

    icd_split = set(df['primary_icd10'].astype(str) + ' ' + df['primary_diagnosis'].astype(str))
    icds = sorted(icd_split, key=str.casefold)
    icd_split = set(df['secondary_icd10'].astype(str) + ' ' + df['secondary_diagnosis'].astype(str))
    icd_second = sorted(icd_split, key=str.casefold)	

    check_import = st.sidebar.checkbox("Import Patient List")
    if check_import:
        uploaded_file = st.sidebar.file_uploader("Import File", type=['csv'])
        if uploaded_file:

            meta = ""
            for line in uploaded_file:
                meta = line.decode('utf-8')
                break

            meta_list = meta.split('\t')
            with st.sidebar.expander("Patient List Search Criteria"):
                st.write(meta_list)
            
            df_pat = pd.read_csv(uploaded_file, comment='"', names=['mrn'], converters={'mrn': lambda x: str(x)})
       
            df_pat['mrn'] = df_pat['mrn'].astype(str)
            ids = df_pat['mrn'].unique()
            id_selection_file = sorted(ids)
            #st.write(id_selection_file)

    col1, col2, col3, col4 = st.columns(4)

    st.sidebar.subheader("")
    final_crg = st.sidebar.checkbox("Final Charge")
    st.sidebar.subheader("")
    mod62 = ''
    mod82 = ''
    mod62_ie = st.sidebar.checkbox("MOD62")
    mod62_a, mod62_b = st.sidebar.columns([1,9])
    if mod62_ie:   
        with mod62_b: 
            mod62 = st.radio('Select ',('Include MOD62','Exclude MOD62'))
    mod82_ie = st.sidebar.checkbox("MOD82")
    mod82_a, mod82_b = st.sidebar.columns([1,9])
    if mod82_ie:
        with mod82_b:
            mod82 = st.radio('Select',('Include MOD82','Exclude MOD82'))

    side_a, side_b = st.sidebar.columns([3,9])
    procs = sorted(df['proc_name'].unique())
    proc_ids = sorted(df['proc_id'].unique())
    with side_a:
        proc_pick = st.radio('Proc Filter',('Select', 'Search', 'Select ID',))
    with side_b:
        if proc_pick == 'Search':
            proc_selections = st.text_input('Enter Procedure')
        elif proc_pick == 'Select ID':
            proc_selections = st.multiselect('Procedure ID',options=proc_ids)
        else:
            proc_selections = st.multiselect('Procedure Name',options=procs)


    side_ab, side_bb = st.sidebar.columns([3,9])
    providers = sorted(df['billing_provider'].unique())
    providers_ids = sorted(df['billing_prov_id'].unique())
    with side_ab:
        bill_pick = st.radio('Provider Filter',('Select','Search','Select ID'))
    with side_bb:
        if bill_pick == 'Search':
            billing_selections = st.text_input('Enter Billing Provider Name')
        elif bill_pick == 'Select ID':
            billing_selections = st.multiselect('Billing Provider ID',options=providers_ids)
        else:
            billing_selections = st.multiselect('Billing Provider Name',options=providers)

    
    side_rA, side_rB = st.sidebar.columns([3,9])
    ref_providers = sorted(df['referring_provider'].unique())
    ref_providers_ids = sorted(df['referring_prov_id'].unique())
    with side_rA:
        ref_pick = st.radio('Referring Filter',('Select','Search','Select ID'))
    with side_rB:
        if ref_pick == 'Search':
            ref_selections = st.text_input('Enter Referring Provider Name')
        elif ref_pick == 'Select ID':
            ref_selections = st.multiselect('Referring Provider ID',options=ref_providers_ids)
        else:
            ref_selections = st.multiselect('Referring Provider Name',options=ref_providers)

    icd_blocks = {}
    icd_second_blocks = {}
    for chapter, block, block_description in icd10.chapters:
        icd_sub = []
        for row in icds:
            if row[0:1] == block[0:1]:
                icd_sub.append(row)
        icd_sub_second = []
        for row in icd_second:
            if row[0:1] == block[0:1]:
                icd_sub_second.append(row) 
        if icd_sub is not None:
            icd_blocks[block + ': ' + block_description] = icd_sub
        if icd_sub_second is not None:
            icd_second_blocks[block + ': ' + block_description] = icd_sub_second
    
    icd_filter_a = st.checkbox("Primary ICD-10")
    icd_filter_searchA = []
    block_sub_selection_a = []
    if icd_filter_a:
        icd_filter_searchA = st.checkbox("Search Primary Diagnosis")

    if icd_filter_searchA:
        a1, a2 = st.columns(2)
        with a1:
            block_sub_selection_a = st.text_input('Enter Primary Diagnosis ')
    else:
        a1, a2 = st.columns(2)
        with a1:
            if icd_filter_a:
                blocks = sorted(icd_blocks)
                block_selection = st.selectbox('ICD-10 Primary Block',options=blocks)
                if block_selection:
                    with a2:
                        block_sub_selection_a = st.multiselect('ICD-10 Primary Code',options=sorted(icd_blocks[block_selection]))

    icd_filter_b = st.checkbox("Secondary ICD-10")
    icd_filter_searchB = []
    block_sub_selection_b = []
    if icd_filter_b:
        icd_filter_searchB = st.checkbox("Search Secondary Diagnosis")

    if icd_filter_searchB:
        b1, b2 = st.columns(2)
        with b1:
            block_sub_selection_b = st.text_input('Enter Secondary Diagnosis ')
    else:
        b1, b2 = st.columns(2)
        with b1:
            if icd_filter_b:     
                blocks = sorted(icd_blocks) 
                block_selection = st.selectbox('ICD-10 Secondary Block',options=blocks)
                if block_selection:
                    with b2:
                        block_sub_selection_b = st.multiselect('ICD-10 Secondary Code',options=sorted(icd_second_blocks[block_selection]))
            

    cpt_filter = st.checkbox("CPT CODE")
    c1, c2 = st.columns(2)
    cpt_selections = []
    cpt_sub_selections = []
    if cpt_filter:
        cpts = df['cpt_code'].unique()
        cpt_cat = []
        for c in cpts:
            cpt_cat.append(c[:2])
        cpt_cat = sorted(set(cpt_cat))
        with c1:
            cpt_selections = st.selectbox('CPT Category',options=cpt_cat)
        
        cpt_sub = []
        if cpt_selections:
            for c in cpts:
                if cpt_selections == c[:2]:
                    cpt_sub.append(c)
        with c2:
            cpt_sub_selections = st.multiselect('CPT Code',options=sorted(cpt_sub))

    if 'date_s' not in st.session_state:
        st.session_state['date_s'] = []

    if st.session_state['date_s'] is not None:
        date_s = st.sidebar.date_input("Service Date",st.session_state['date_s'], min_value = dt(1950,1,1), max_value=dt.today())

    regex = '''?&|!{}[]()^~*:\\"'+-'''
    replace = ['\\' + l for l in regex]
    alt_clean = str.maketrans(dict(zip(regex, replace)))

    empty_df = pd.DataFrame(columns=df.columns)
    set_df(empty_df)
    
    query_builder = []
        
    if final_crg:
        query_builder.append('charge_final_is_1 == 1')
    if mod62 == 'Include MOD62':
        query_builder.append('mod_62 == 1')
    elif mod62 == 'Exclude MOD62':
        query_builder.append('mod_62 == 0')
    if mod82 == 'Include MOD82':
        query_builder.append('mod_82 == 1')
    elif mod82 == 'Exclude MOD82':
        query_builder.append('mod_82 == 0')

    if proc_selections and proc_pick == "Select":
        proc_fixed_list = [s.translate(alt_clean) for s in proc_selections]
        query_builder.append('proc_name.str.contains("|".join(@proc_fixed_list),regex=True)')
    elif proc_selections and proc_pick == "Select ID":
        query_builder.append('proc_id == @proc_selections')
    elif proc_selections and proc_pick == "Search":
        query_builder.append('proc_name.str.contains(@proc_selections, case=False)')

    if billing_selections and bill_pick == "Select":
        billing_fixed_list = [s.translate(alt_clean) for s in billing_selections]
        query_builder.append('billing_provider.str.contains("|".join(@billing_fixed_list),regex=True)')
    elif billing_selections and bill_pick == "Select ID":
        query_builder.append('billing_prov_id == @billing_selections')
    elif billing_selections and bill_pick == "Search":
        query_builder.append('billing_provider.str.contains(@billing_selections, case=False)')

    if ref_selections and ref_pick == "Select":
        ref_fixed_list = [s.translate(alt_clean) for s in ref_selections]
        query_builder.append('referring_provider.str.contains("|".join(@ref_fixed_list),regex=True)')
    elif ref_selections and ref_pick == "Select ID":
        query_builder.append('ref_prov_id == @ref_selections')
    elif ref_selections and ref_pick == "Search":
        query_builder.append('referring_provider.str.contains(@ref_selections, case=False)')

    if block_sub_selection_a:
        icd_query = []
        for row in block_sub_selection_a:
            icd_query.append(row.split(' ',1)[0])
        if icd_filter_searchA: 
            query_builder.append('primary_diagnosis.str.contains(@block_sub_selection_a, case=False)')
        else:
            query_builder.append('primary_icd10 == @icd_query')
    if block_sub_selection_b:
        icd_query = []
        for row in block_sub_selection_b:
            icd_query.append(row.split(' ',1)[0])
        if icd_filter_searchB: 
            query_builder.append('secondary_diagnosis.str.contains(@block_sub_selection_b, case=False)')
        else:
            query_builder.append('secondary_icd10 == @icd_query')

    if cpt_sub_selections:
        query_builder.append('cpt_code == @cpt_sub_selections')

    if len(date_s) == 2:
        query_builder.append('service_date >= @date_s[0] & service_date <= @date_s[1]')

    query = df_query(query_builder)
    if query != '':
        set_df(df.query(query))

    agDf = get_df()

    displayGrid = GridOptionsBuilder.from_dataframe(agDf)
    displayGrid.configure_side_bar() #Add a sidebar
    displayGrid.configure_default_column(groupable=True, value=True, enableRowGroup=True, editable=False)
    gridOptions_pat = displayGrid.build()

    demo = AgGrid(
        agDf,
        gridOptions=gridOptions_pat,
        height=800,
        theme='streamlit',
        update_mode='MODEL_CHANGED'
    )

    
    col1.metric("Number of Patients Selected", str(len(set(df_selections['pat_id'].unique())))) #set to get unique
    col2.metric("Rows Returned", len(df_selections))
    #col3.metric("Latest Refresh", df['latest_refresh_date'][0].strftime("%m/%d/%y %H:%M"))
    if len(date_s) == 2:
        col3.metric("Service Date Range", date_s[0].strftime("%m/%d/%y") + ' - ' + date_s[1].strftime("%m/%d/%y"))

    meta = ''
    meta += '\t' + ('Procedure Name: ' + str(proc_selections))
    meta += '\t' + ('Billing Provider Name: ' + str(billing_selections))
    meta += '\t' + ('Primary ICD-10 ' + str(block_sub_selection_a))
    meta += '\t' + ('Secondary ICD-10: ' + str(block_sub_selection_b))
    meta += '\t' + ('CPT Code: ' + str(cpt_sub_selections))
    meta += '\t' + ('Service Date: ' + str(date_s))

    df_csv = get_df()
    csv = convert_df(df_csv, False)
    st.download_button(
        "Export Table",
        csv,
        "charges.csv",
        key='download-csv'
    )

    df_pat = get_df()['pat_id']
    df_pat = df_pat.drop_duplicates()
    df_pat.loc[-1] = str(meta)
    df_pat.index += 1
    df_pat = df_pat.sort_index()
    
    csv = convert_df(df_pat, True)
    st.download_button(
        "Export Patient List",
        csv,
        "patient_list.csv",
        key='download-csv'
    )

    
    if not df_selections.empty:
        bar_yr = st.selectbox('Select Year',sorted(df_selections['service_date'].dt.to_period('Y').drop_duplicates(),reverse=True))
        if bar_yr:
            df_q = df_selections[df_selections['service_date'].dt.to_period('Y') == bar_yr]
            num_months = len(df['service_date'].dt.strftime("%m").unique().tolist())
            if not df_q.empty:
                cola,colb = st.columns(2)
                df_s = df_q[['pat_mrn_id','service_date', 'proc_name','billing_provider']]
                df_s = df_s.drop_duplicates()
                
                df_proc = df_q.groupby(['billing_provider',df_q.service_date.dt.month])["proc_name"].count().reset_index(name="procedure_count")
                #df_proc['service_date'] = df_proc['service_date'].apply(lambda x: calendar.month_abbr[x])
                fig=px.line(df_proc, x='service_date', y='procedure_count', color='billing_provider', title='PROCEDURES PER PROVIDER', height=700)
                fig.update_layout(
                    xaxis_title = 'Month',
                    yaxis_title = 'Procedure Count',
                    xaxis = dict
                    (
                        tickmode = 'linear',
                        tick0 = 1,
                        dtick = 1
                    )
                )
                st.plotly_chart(fig, use_container_width=True)

if __name__ == "__main__":
    st.set_page_config(
        page_title="Surgical Oncology Dashboard",
        layout="wide",
        initial_sidebar_state="expanded",
    )
    st.markdown(
    """
    <style>
    [data-testid="stSidebar"][aria-expanded="true"] > div:first-child{
        width: 500px;
    }
    """,
    unsafe_allow_html=True,
    )
    df = utils.get_full_df()

    #st.sidebar.text('Latest Refresh: ' + df['latest_refresh_date'][0].strftime("%m/%d/%y %H:%M"))
    a,b = st.sidebar.columns([6,4])
    with a:
        st.text('Latest Refresh: ' + df['latest_refresh_date'][0].strftime("%m/%d/%y %H:%M"))
        refresh_btn = st.text_input('Refresh Passkey:')
    side_a, side_b = st.sidebar.columns(2)
    if refresh_btn == utils.pw:
        with side_a:
            with st.spinner("Please wait..."):
                cnxn = utils.cnxn
                f = open('SURGONC/sql/surgonc_refresh.sql','r')
                query = f.read()
                cursor = cnxn.cursor()
                cursor.execute(query)
                cnxn.commit()
                # strange bug, query must be executed twice to take effect
                try:
                    pd.read_sql(query,cnxn)
                except:
                    st.sidebar.warning("Table Refreshed. Please re sign-in.")
    main()


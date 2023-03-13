import streamlit as st
import pandas as pd
import plotly.express as px
import io
import utils
import csv

df_pat_selections = pd.DataFrame()

def set_df(df):
    global df_pat_selections
    df_pat_selections = df

def get_df():
    return df_pat_selections    

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

def main() -> None:
    st.header("Patient View")

    col1, col2, col3 = st.columns(3)
    uploaded_file = st.file_uploader("Import Patient List", type=['csv'])

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
        id_selection = st.sidebar.selectbox('SELECT MRN',options=ids)


        query_builder = []
        if id_selection:
            query_builder.append('mrn == @id_selection')
        
        query = df_query(query_builder)
        if query != '':
            set_df(df.query(query))

        cur_pat_df = get_df()['mrn'].unique()
        cur_pat = str(cur_pat_df[0])

        if 'pat_subset' not in st.session_state:
            st.session_state['pat_subset'] = []
        

        add_subset = st.sidebar. button('Add Patient')
        if add_subset:
            if cur_pat not in st.session_state['pat_subset']:
                st.session_state['pat_subset'].append(cur_pat)
        st.sidebar.header("")

        sub_selections =[]
        sub_selections = st.sidebar.multiselect("PATIENT SUBSET",default = st.session_state['pat_subset'], options = st.session_state['pat_subset'])
        st.session_state['pat_subset'] = sub_selections
        
        query_builder = []
        if sub_selections:
            query_builder.append('mrn == @sub_selections')
        
        sub_charts = st.sidebar.button('Graph Subset')

        df_pat = sorted(get_df()['mrn'].unique())
        df_pat_s = pd.Series(df_pat)
        df_pat_s.loc[-1] = meta
        df_pat_s.index += 1
        df_pat_s = df_pat_s.sort_index()

        csv_pat = convert_df(df_pat_s, True)
        custom_pat = st.sidebar.download_button(
            "Custom Patient List",
            csv_pat,
            "custom_patient_list.csv",
            key='download-csv',
        )
        if custom_pat: #reset
            del st.session_state['pat_subset']
        
        if sub_charts:
            query = df_query(query_builder)
            if query != '':
                set_df(df.query(query))

            col1.metric("Patients Selected", str(len(set(df_pat_selections['mrn'].unique()))))
            col2.metric("Rows Returned", len(df_pat_selections))

            with st.expander("All Patients Data"):
                st.write(get_df())

            csv = convert_df(get_df(), False)
            st.download_button(
                "Export Table",
                csv,
                'patients_table.csv',
                key='download-csv'
            )
            utils.plot_selections(get_df())
            
        else:
            col1.metric("Patients Imported", str(len(ids)))
            # at this point we only have df with ONE selected mrn from patient list
            
            with st.expander("Patient Data: " + cur_pat):
                st.write(get_df())

            csv = convert_df(get_df(), False)

            st.download_button(
                "Export Table",
                csv,
                'patient_table.csv',
                key='download-csv'
            )
            utils.plot_patient(get_df())
            


if __name__ == "__main__":
    st.set_page_config(
        page_title="PCC EGFR Mutations",
        #page_icon="chart_with_upwards_trend",
        layout="wide",
        initial_sidebar_state="expanded",
    )
    df = utils.get_full_df()
    main()


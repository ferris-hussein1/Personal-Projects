import streamlit as st
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
import hashlib
import io
from base64 import b64encode
from datetime import date as dt, datetime


import pyodbc


def hasher(col):
    return col.apply(lambda x: hashlib.md5(x.encode('utf-8')).hexdigest() if x is not None else 'N/A')

#  CONNECTION STRING REMOVED ****
cnxn=pyodbc.connect(cnxnstr,autocommit=True)

f = open('EGFR/sql/egfr.sql','r')
query = f.read()
df = pd.read_sql_query(query, con=cnxn)
#"""
#df = pd.read_csv('pat.csv', sep = ',')


#DF Processing
#df['mrn'] = hasher(df['mrn'])   ## just a column hasher for deid
df['mrn'] = df['mrn'].astype(str)
df['firstdose'] = pd.to_datetime(df['firstdose'])
df['lastdose'] = pd.to_datetime(df['lastdose'])
df['colldate'] = pd.to_datetime(df['colldate'])
df['race_category'] = df['race_category'].astype(str)
df['specsite'] = df['specsite'].astype(str)
df['totaldoses'] = df['totaldoses'].astype(str)
df['icd10_all'] = df['icd10_all'].astype(str)
df['medication_name'] = df['medication_name'].fillna("UNKNOWN")
df['treatment_plan_name'] = df['treatment_plan_name'].fillna("UNKNOWN")
df['current_age'] = df['current_age'].astype(int, errors='ignore')
df['aged'] = df['aged'].astype(int, errors='ignore')
#####


def get_full_df():
    return df

def plot_selections(df_selections):
    opts = ['Medication (First Dose - Last Dose)', 'Treatment Plan (Start Date - Last Encounter)']
    gantt = st.selectbox('Select Timeline',options=opts)

    if gantt and len(set(df_selections['mrn']))>0:
        if gantt == 'Medication (First Dose - Last Dose)':
            col1, col2, col3 = st.columns(3)

            fig = px.timeline(
                df_selections,
                x_start="firstdose",
                x_end="lastdose",
                y="medication_name",
                color="mrn",
                hover_data=["totaldoses"]
                )
            fig.update_yaxes(autorange="reversed")
            st.plotly_chart(fig, use_container_width=True)

        if gantt == 'Treatment Plan (Start Date - Last Encounter)':
            col1, col2, col3 = st.columns(3)
            fig = px.timeline(
                df_selections,
                x_start="plan_start_date",
                x_end="last_enc",
                y="treatment_plan_name",
                color="mrn", )

            fig.update_yaxes(autorange="reversed")
            st.plotly_chart(fig, use_container_width=True)

        buffer = io.StringIO()
        fig.write_html(buffer, include_plotlyjs='cdn', default_height='200%')
        html_bytes = buffer.getvalue().encode()
        st.download_button(
            label='Export to HTML',
            data=html_bytes,
            file_name='medication.html',
            mime='text/html'
        )

    plot1, plot2 = st.columns(2)
    bar1, bar2 = st.columns(2)

    if len(df_selections['mrn'])>1:
        with plot1:
            diag = df_selections['submitteddiagnosis'].unique()
            df_pi = df_selections[['mrn','submitteddiagnosis']]
            df_pi = df_pi.drop_duplicates()
            values = df_pi['submitteddiagnosis'].value_counts()

            fig=px.histogram(df_pi, x='submitteddiagnosis', color='submitteddiagnosis', barmode='stack',range_y=[0,values],title='Submitted Diagnoses')
            st.plotly_chart(fig, use_container_width=True)

        with plot2:
            demo = df_selections['race_category'].unique()
            df_pi = df_selections[['mrn','race_category']]
            df_pi = df_pi.drop_duplicates()
            values = df_pi['race_category'].value_counts()

            fig_pi = go.Figure(
                go.Pie(
                labels = demo,
                values = values,
                hoverinfo = "label+percent",
                textinfo = "value",
                title='Race Category'
            ))
            st.plotly_chart(fig_pi, use_container_width=True)


        with bar1:
            df_s = df_selections[['mrn','specsite','gender', 'submitteddiagnosis']]
            df_s = df_s.drop_duplicates()
            values = df_s['mrn'].value_counts()
            fig=px.histogram(df_s, x='specsite', color='submitteddiagnosis', barmode='stack',range_y=[0,values],title='Specimen Site')
            st.plotly_chart(fig, use_container_width=True)

        with bar2:
            df_s = df_selections[['mrn','survival_status','gender']]
            df_s = df_s.drop_duplicates()
            values = df_s['mrn'].value_counts()
            fig=px.histogram(df_s, x='survival_status', color='gender', barmode='stack',range_y=[0,values],title='Known Survival Status')
            st.plotly_chart(fig, use_container_width=True)

        box1, box2 = st.columns(2)
        with box1:
            fig = px.box(df_selections, x="gender", y="current_age", color ="gender", range_y=[0,100], title='Alive: Age & Gender Breakdown')
            st.plotly_chart(fig, use_container_width=True)
        with box2:
            fig = px.box(df_selections, x="gender", y="aged", color ="gender", range_y=[0,100], title='Deceased: Age & Gender Breakdown')
            st.plotly_chart(fig, use_container_width=True)


def plot_patient(df_plot):
    cur_pat_df = df_plot['mrn'].unique()
    id = str(cur_pat_df[0])

    fname = str(df_plot['firstname'].unique()[0])
    lname = str(df_plot['lastname'].unique()[0])
    age = df_plot['current_age'].unique()[0]
    aged = df_plot['aged'].unique()[0]
    race = str(df_plot['race_category'].unique()[0])
    smoker = str(df_plot['smoking_history'].unique()[0])

    with st.expander("PATIENT DETAILS"):
        st.text("MRN: " + id)
        st.text("Name: " + fname + ' ' + lname)
        if not pd.isna(age):
            st.text("Age: " + str(age))
        elif not pd.isna(aged):
            st.text("Aged: " + str(aged))
        else:
            st.text("Age: Unknown")
        st.text("Race: " + race)
        st.text("Smoking History: " + smoker)

    with st.expander("NOTES"):
        note_taker = st.text_area('Input')
        cur_date = str(datetime.today())
        if st.button("Process Notes"):
            notes = note_taker
            st.download_button(
            "Export Notes",
            notes,
            cur_date + "_notes.txt",
            key='download-txt',
            )

    opts = ['Medication (First Dose - Last Dose)', 'Treatment Plan (Start Date - Last Encounter)']
    gantt = st.selectbox('Select Timeline',options=opts)

    if gantt:
        if gantt == 'Medication (First Dose - Last Dose)':
            fig = px.timeline(
                df_plot,
                x_start="firstdose",
                x_end="lastdose",
                y="medication_name",
                color="mrn",
                hover_data=["totaldoses"])
            fig.update_yaxes(autorange="reversed")
            st.plotly_chart(fig, use_container_width=True)
        if gantt == 'Treatment Plan (Start Date - Last Encounter)':
            fig = px.timeline(
                df_plot,
                x_start="plan_start_date",
                x_end="last_enc",
                y="treatment_plan_name",
                color="mrn", )

            fig.update_yaxes(autorange="reversed")
            st.plotly_chart(fig, use_container_width=True)

        buffer = io.StringIO()
        fig.write_html(buffer, include_plotlyjs='cdn')
        html_bytes = buffer.getvalue().encode()
        st.download_button(
            label='Export to HTML',
            data=html_bytes,
            file_name='medication.html',
            mime='text/html'
        )

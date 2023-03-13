import pandas as pd
import pyodbc

#  CONNECTION STRING REMOVED ****

f = open('SURGONC/sql/surgonc.sql','r')
query = f.read()
df = pd.read_sql_query(query, con=cnxn)

df['pat_id'] = df['pat_id'].astype(str)
df['pat_mrn_id'] = df['pat_mrn_id'].astype(str)
df['pat_name'] = df['pat_name'].astype(str)
df['charge_final_is_1'] = pd.array(df['charge_final_is_1'], dtype=pd.Int64Dtype())
df['primary_diagnosis'] = df['primary_diagnosis'].astype(str)
df['secondary_diagnosis'] = df['secondary_diagnosis'].astype(str)
df['primary_icd10'] = df['primary_icd10'].astype(str)
df['billing_provider'] = df['billing_provider'].astype(str)
df['billing_prov_id'] = df['billing_prov_id'].astype(str)
df['referring_provider'] = df['referring_provider'].astype(str)
df['referring_prov_id'] = df['referring_prov_id'].astype(str)
df['cpt_code'] = df['cpt_code'].astype(str)
df['proc_id'] = pd.array(df['proc_id'], dtype=pd.Int64Dtype())
df['pat_enc_csn_id'] = pd.array(df['pat_enc_csn_id'], dtype=pd.Int64Dtype())
df['primary_dx_id'] = pd.array(df['primary_dx_id'], dtype=pd.Int64Dtype())
df['dx_two_id'] = pd.array(df['dx_two_id'], dtype=pd.Int64Dtype())
df['dx_three_id'] = pd.array(df['dx_three_id'], dtype=pd.Int64Dtype())
df['dx_four_id'] = pd.array(df['dx_four_id'], dtype=pd.Int64Dtype())
df['dx_five_id'] = pd.array(df['dx_five_id'], dtype=pd.Int64Dtype())
df['dx_six_id'] = pd.array(df['dx_six_id'], dtype=pd.Int64Dtype())
df['account_id'] = pd.array(df['account_id'], dtype=pd.Int64Dtype())
df['department_id'] = pd.array(df['department_id'], dtype=pd.Int64Dtype())
df['post_date'] = pd.to_datetime(df['post_date'])
df['service_date'] = pd.to_datetime(df['service_date'])
df['claim_date'] = pd.to_datetime(df['claim_date'])
df['latest_refresh_date'] = pd.to_datetime(df['latest_refresh_date'])

def get_full_df():
    return df
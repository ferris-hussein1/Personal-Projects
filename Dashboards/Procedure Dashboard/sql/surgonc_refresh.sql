insert overwrite table surgonc_dash

with t1 as (
    select distinct
        crg.patient_id as pat_id
        ,crg.tx_id
        ,pt.pat_mrn_id
        ,pt.pat_name
        ,crg.pat_enc_csn_id
        ,crg.proc_id
        ,eap.proc_name
        ,crg.cpt_code
        ,crg.modifier_one
        ,crg.modifier_two
        ,crg.modifier_three
        ,crg.modifier_four
        ,crg.procedure_quantity
        ,crg.post_date
        ,crg.service_date
        ,zc.name as transaction_type
        ,crg.account_id
        ,crg.billing_prov_id
        ,prov.prov_name as billing_provider
        ,pat.referring_prov_id
        ,rfr.prov_name as referring_provider
        ,crg.primary_dx_id
        ,edg.dx_name as primary_diagnosis
        ,edg.current_icd10_list as primary_icd10
        ,crg.dx_two_id
        ,edg2.dx_name as secondary_diagnosis
        ,edg2.current_icd10_list as secondary_icd10
        ,crg.dx_three_id
        ,crg.dx_four_id
        ,crg.dx_five_id
        ,crg.dx_six_id
        ,crg.rvu_total
        ,crg.rvu_work
        ,crg.claim_date
        ,crg.department_id
        ,dep.department_name
        ,loc.loc_name
        ,case when crg.modifier_one='62' or crg.modifier_two='62' or crg.modifier_three='62' or crg.modifier_four='62' then 1 else 0 end Mod_62
        ,case when crg.modifier_one='82' or crg.modifier_two='82' or crg.modifier_three='82' or crg.modifier_four='82' then 1 else 0 end Mod_82
    from transactions crg
    LEFT JOIN patient pt on (crg.patient_id = pt.pat_id)
    LEFT JOIN clarity_ser prov on (prov.prov_id = crg.billing_prov_id)
    LEFT JOIN clarity_eap eap on (eap.proc_id = crg.proc_id)
    LEFT JOIN clarity_edg edg on (crg.primary_dx_id = edg.dx_id)
    LEFT JOIN clarity_edg edg2 on (crg.dx_two_id = edg2.dx_id)
    LEFT JOIN hsp_account pat on (pat.prim_enc_csn_id = crg.pat_enc_csn_id)
    LEFT JOIN clarity_ser rfr on (rfr.prov_id = pat.referring_prov_id)
    LEFT JOIN zc_tx_type_ha zc on (zc.tx_type_ha_c = crg.tx_type_c)
    LEFT JOIN clarity_loc loc on loc.loc_id=crg.loc_id
    LEFT JOIN clarity_dep dep on dep.department_id=crg.department_id
    where billing_prov_id in('REMOVED')
    and crg.tx_type_c = 1
    and crg.void_date is null
),
t2 as (  --Each provider bills a proc based on their own contribution in a service
    select tx_id,
    row_number() over (partition by pat_id,service_date,proc_id,billing_prov_id,modifier_one,modifier_two,modifier_three,modifier_four order by post_date desc) charge_final_is_1
    from t1
)

select
    t1.pat_id
    ,t1.pat_mrn_id
    ,t1.pat_name
    ,t1.pat_enc_csn_id
    ,t1.proc_id
    ,t1.proc_name
    ,t1.cpt_code
    ,t1.modifier_one
    ,t1.modifier_two
    ,t1.modifier_three
    ,t1.modifier_four
    ,t1.procedure_quantity
    ,t1.post_date
    ,t1.service_date
    ,t1.transaction_type
    ,t1.account_id
    ,t1.billing_prov_id
    ,t1.billing_provider
    ,t1.referring_prov_id
    ,t1.referring_provider
    ,t1.primary_dx_id
    ,t1.primary_diagnosis
    ,t1.primary_icd10
    ,t1.dx_two_id
    ,t1.secondary_diagnosis
    ,t1.secondary_icd10
    ,t1.dx_three_id
    ,t1.dx_four_id
    ,t1.dx_five_id
    ,t1.dx_six_id
    ,t1.rvu_total
    ,t1.rvu_work
    ,t1.claim_date
    ,t1.department_id
    ,t1.department_name
    ,t1.loc_name
    ,t1.mod_62
    ,t1.mod_82
    ,t2.charge_final_is_1
    ,cast(now() as timestamp) as latest_refresh_date
from t1
left join t2 on t2.tx_id=t1.tx_id
order by pat_id,service_date,proc_id,billing_prov_id,modifier_one,modifier_two,modifier_three,modifier_four,t2.charge_final_is_1
;
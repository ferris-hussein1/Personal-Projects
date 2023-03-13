WITH TOB AS
(
    with t1 as
    (
    select distinct pat_id
    , tobacco_use
    , case
        when tobacco_use in ('Smoker, Current Status Unknown', 'Former', 'Some Days', 'Every Day', 'Light Smoker', 'Heavy Smoker') then 'Yes'
        when tobacco_use in ('Never', 'Passive Smoke Exposure - Never Smoker') then 'No'
        else null -- unknown
        end as 'smoking_history'
    from pcc_datalake_base.social_hx
    )
    select pat_id, max(smoking_history) as smoking_history
    from t1
    group by pat_id
)
, demo as
(
select distinct
coalesce(fcm.pmi_mrn, fcm.pmi_report_id) as patient_id
, pmi_gender
, case WHEN pt.race_firstone like '%White%'
        AND NOT(
            pt.race_firstone like '%Filipino%'
            OR pt.race_firstone like '%Asian%'
            OR pt.race_firstone like '%Asian Indian%'
            OR pt.race_firstone like '%Chinese%'
            OR pt.race_firstone like '%Malaysian%'
            OR pt.race_firstone like '%Japanese%'
            OR pt.race_firstone like '%Korean%'
            OR pt.race_firstone like '%Sri Lankan%'
            OR pt.race_firstone like '%Indonesian%'
            OR pt.race_firstone like '%Bangladeshi%'
            OR pt.race_firstone like '%Vietnamese%'
            OR pt.race_firstone like '%Pakistani%'
            OR pt.race_firstone like '%Thai%'
            OR pt.race_firstone like '%Hmong%'
            OR pt.race_firstone like '%Laotian%'
            OR pt.race_firstone like '%Cambodian%'
            OR pt.race_firstone like '%Taiwanese%'
            OR pt.race_firstone like '%Black%'
            OR pt.race_firstone like '%Native%'
            OR pt.race_firstone like '%Pacific%'
            OR pt.race_firstone like '%Samoan%'
            OR pt.race_firstone like '%Guamanian%'
            OR pt.race_firstone like '%Chamorro%') then 'White'
    WHEN pt.race_firstone like '%Black%'
        AND NOT (
            pt.race_firstone like '%Filipino%'
            OR pt.race_firstone like '%Asian%'
            OR pt.race_firstone like '%Asian Indian%'
            OR pt.race_firstone like '%Chinese%'
            OR pt.race_firstone like '%Malaysian%'
            OR pt.race_firstone like '%Japanese%'
            OR pt.race_firstone like '%Korean%'
            OR pt.race_firstone like '%Sri Lankan%'
            OR pt.race_firstone like '%Indonesian%'
            OR pt.race_firstone like '%Bangladeshi%'
            OR pt.race_firstone like '%Vietnamese%'
            OR pt.race_firstone like '%Pakistani%'
            OR pt.race_firstone like '%Thai%'
            OR pt.race_firstone like '%Hmong%'
            OR pt.race_firstone like '%Laotian%'
            OR pt.race_firstone like '%Cambodian%'
            OR pt.race_firstone like '%Taiwanese%'
            OR pt.race_firstone like '%White%'
            OR pt.race_firstone like '%Native%'
            OR pt.race_firstone like '%Pacific%'
            OR pt.race_firstone like '%Samoan%'
            OR pt.race_firstone like '%Guamanian%'
            OR pt.race_firstone like '%Chamorro%') then 'Black'
    WHEN (pt.race_firstone like '%Filipino%'
            OR pt.race_firstone like '%Asian%'
            OR pt.race_firstone like '%Asian Indian%'
            OR pt.race_firstone like '%Chinese%'
            OR pt.race_firstone like '%Malaysian%'
            OR pt.race_firstone like '%Japanese%'
            OR pt.race_firstone like '%Korean%'
            OR pt.race_firstone like '%Sri Lankan%'
            OR pt.race_firstone like '%Indonesian%'
            OR pt.race_firstone like '%Bangladeshi%'
            OR pt.race_firstone like '%Vietnamese%'
            OR pt.race_firstone like '%Pakistani%'
            OR pt.race_firstone like '%Thai%'
            OR pt.race_firstone like '%Hmong%'
            OR pt.race_firstone like '%Laotian%'
            OR pt.race_firstone like '%Cambodian%'
            OR pt.race_firstone like '%Taiwanese%')
        AND NOT(
            pt.race_firstone like '%White%'
            OR pt.race_firstone like '%Black%'
            OR pt.race_firstone like '%Native%'
            OR pt.race_firstone like '%Pacific%'
            OR pt.race_firstone like '%Samoan%'
            OR pt.race_firstone like '%Guamanian%'
            OR pt.race_firstone like '%Chamorro%') then 'Asian'
    WHEN (pt.race_firstone like '%Pacific Islander%'
            OR pt.race_firstone like '%Native Hawaiian%'
            OR pt.race_firstone like '%Samoan%'
            OR pt.race_firstone like '%Guamanian%'
            OR pt.race_firstone like '%Chamorro%')
        AND NOT (
            pt.race_firstone like '%White%'
            OR pt.race_firstone like '%Black%'
            OR pt.race_firstone like '%Filipino%'
            OR pt.race_firstone like '%Asian%'
            OR pt.race_firstone like '%Asian Indian%'
            OR pt.race_firstone like '%Chinese%'
            OR pt.race_firstone like '%Malaysian%'
            OR pt.race_firstone like '%Japanese%'
            OR pt.race_firstone like '%Korean%'
            OR pt.race_firstone like '%Sri Lankan%'
            OR pt.race_firstone like '%Indonesian%'
            OR pt.race_firstone like '%Bangladeshi%'
            OR pt.race_firstone like '%Vietnamese%'
            OR pt.race_firstone like '%Pakistani%'
            OR pt.race_firstone like '%Thai%'
            OR pt.race_firstone like '%Hmong%'
            OR pt.race_firstone like '%Laotian%'
            OR pt.race_firstone like '%Cambodian%'
            OR pt.race_firstone like '%Taiwanese%') then 'Native Hawaiian or Other Pacific Islander'

    WHEN pt.race_firstone like '%Native American%'
        AND NOT (
            pt.race_firstone like '%Filipino%'
            OR pt.race_firstone like '%Asian%'
            OR pt.race_firstone like '%Asian Indian%'
            OR pt.race_firstone like '%Chinese%'
            OR pt.race_firstone like '%Malaysian%'
            OR pt.race_firstone like '%Japanese%'
            OR pt.race_firstone like '%Korean%'
            OR pt.race_firstone like '%Sri Lankan%'
            OR pt.race_firstone like '%Indonesian%'
            OR pt.race_firstone like '%Bangladeshi%'
            OR pt.race_firstone like '%Vietnamese%'
            OR pt.race_firstone like '%Pakistani%'
            OR pt.race_firstone like '%Thai%'
            OR pt.race_firstone like '%Hmong%'
            OR pt.race_firstone like '%Laotian%'
            OR pt.race_firstone like '%Cambodian%'
            OR pt.race_firstone like '%Taiwanese%'
            OR pt.race_firstone like '%White%'
            OR pt.race_firstone like '%Black%'
            OR pt.race_firstone like '%Pacific%'
            OR pt.race_firstone like '%Samoan%'
            OR pt.race_firstone like '%Guamanian%'
            OR pt.race_firstone like '%Chamorro%')then 'Native American'
    WHEN pt.race_firstone like 'Unknown' or  pt.race_firstone is NULL then 'Unknown'
    WHEN pt.race_firstone like 'Patient Refused' then 'Patient Refused'
    ELSE 'Other' END as 'Race_Category'
, tob.smoking_history
, case when (lower(pt.survival_status) <> 'deceased' or lower(pt.survival_status) is null) and pt.death_date is null then
(
    (year(cast(now() as timestamp)) - year(fcm.pmi_dob)
    +case when month(fcm.pmi_dob) > month(cast(now() as timestamp) ) then -1
        when month(fcm.pmi_dob) = month(cast(now() as timestamp) ) and day(fcm.pmi_dob) > day(cast(now() as timestamp) ) then -1
        else 0 end)
) end as age
, (year(pt.death_date) - year(fcm.pmi_dob)
   +case when month(fcm.pmi_dob) > month(cast(now() as timestamp) ) then -1
         when month(fcm.pmi_dob) = month(cast(now() as timestamp) ) and day(fcm.pmi_dob) > day(cast(now() as timestamp) ) then -1
         else 0
     end) as aged
, pt.survival_status
from pcc_datalake_patient_matching.fmi_clarity_matches fcm
join tob
on tob.pat_id = fcm.clr_pat_id
join pcc_datalake_base.demographic pt
on pt.pat_id = fcm.clr_pat_id
--where fcm.pmi_mrn is not null
--and fcm.pmi_mrn <> 'NULL'
)
-- eliminate cases where multiple patients are linked to one report_id. No definitive match
, many_to_one as
(
    select patient_id, count(1)
    from demo
    group by patient_id
    having count(1) >1
)
select * from demo
where patient_id not in (select patient_id from many_to_one)
order by patient_id
;

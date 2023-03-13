-- Run in Hive
DROP TABLE CBIO_PATIENT_MAPPING;
CREATE TABLE CBIO_PATIENT_MAPPING AS 
WITH CBIO AS
(
    select distinct
    fcm.clr_pat_id
    , coalesce(pm.mrn, pm.report_id) as patient_id
    from pmi pm 
    left join fmi_clarity_matches fcm
    on fcm.pmi_report_id = pm.report_id
)
select clr_pat_id, patient_id, md5(patient_id) as patient_id_deid from CBIO
;

DROP TABLE CBIO_SAMPLE_MAPPING;
CREATE TABLE CBIO_SAMPLE_MAPPING AS 
WITH CBIO AS
(
    select distinct sam.report_id
    , fcm.clr_pat_id
    from sample sam
    left join fmi_clarity_matches fcm
    on fcm.pmi_report_id = sam.report_id
)
select clr_pat_id, report_id, md5(report_id) as report_id_deid from CBIO
;

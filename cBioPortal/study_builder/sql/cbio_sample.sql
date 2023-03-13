select distinct coalesce(pmi.mrn,sam.report_id) as patient_id
, sam.report_id
, pmi.submitteddiagnosis
, sam.testtype
, sam.specformat
, pmi.specsite
, pmi.medfacilname
, summ.alterationcount
, summ.clinicaltrialcount
, summ.sensitizingcount
, summ.resistivecount
from sample sam
left join fmi_clarity_matches fcm
on fcm.pmi_report_id = sam.report_id
left join pmi pmi
on pmi.report_id = fcm.pmi_report_id
left join summaries summ
on summ.report_id = fcm.pmi_report_id
;

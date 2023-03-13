from impala.dbapi import connect
from impala.util import as_pandas
import hashlib, uuid
import sys
import pandas as pd
import tarfile
import os.path
from pandas import DataFrame

import subprocess
import hashlib
from datetime import date
from datetime import datetime


param = sys.argv[1]

def hasher(col):
    return col.apply(lambda x: hashlib.md5(x.encode()).hexdigest() if x is not None else 'N/A')

def create_table(table_name, df):
    return 0

def tar_study():
    with tarfile.open('study.tar.gz', "w:gz") as tar:
        tar.add('./study', arcname=os.path.basename('./study'))

# add functionality to build study from cohort
if param == 'cohort':
    sys.exit()

if param == 'merge_maf':
    cmd = "awk '(NR == 1) || (FNR > 1)' *.maf > data_mutations_extended.txt"
    subprocess.run(cmd, shell=True)

if param == 'vcf2maf':
    done_vcf = []
    for f in os.listdir('/gpfs/data/PCC/cBioPortal/maf'):
        fname = os.path.splitext(f)[0]
        done_vcf.append(fname)

    start = datetime.now()
    for f in sorted(os.listdir('/integration'), reverse = False):
        fname = os.path.splitext(f)[0]
        hname = hashlib.md5(fname.encode()).hexdigest()
        # avoid running vcf2maf if done already
        if (hname not in done_vcf) and ('vep' not in f) and (f.endswith('vcf')):
            perl = "singularity exec --bind /gpfs/data/PCC singularity/vcf2maf_1.6.19.sif perl singularity/vcf2maf/vcf2maf.pl --vep-path /usr/local/bin/ --vep-data singularity/data/vep/GRCh37 --ncbi-build GRCh37 --tumor-id {hash} --input-vcf /integration/{file}.vcf --output-maf /maf/{hash}.maf --ref-fasta singularity/data/vep/GRCh37/homo_sapiens/102_GRCh37/Homo_sapiens.GRCh37.75.dna.primary_assembly.fa.gz".format(file = fname, hash = hname)
            subprocess.run(perl, shell=True)

    end = datetime.now()
    run_time = end - start
    print('Vcf2Maf Run Time: ' + str(run_time) + '\n')


if param == 'build_study':
    #IMPALA Connection
    conn = connect(
        host='',
        port='',
        auth_mechanism='GSSAPI',
        use_ssl = True,
        kerberos_service_name='impala',
        database='',
    )

    try:
        print("Data Clinical Sample...")
        f = open('study_builder/sql/cbio_sample.sql','r')
        query = f.read()
        df = pd.read_sql_query(query, con=conn)
        df['patient_id'] = hasher(df['patient_id'])
        df['report_id'] = hasher(df['report_id'])
        all_sample = df['report_id']
        df1 = pd.read_csv('template/data_clinical_sample.txt', sep ='\t')
        df1.to_csv('study/data_clinical_sample.txt', sep='\t', index=False)
        df.to_csv('study/data_clinical_sample.txt', mode = 'a', sep='\t', header = False, index=False)
        print(df.head())

        df = DataFrame(df['report_id'])
        print(df.head())
        df = DataFrame.transpose(df)
        df1 = pd.read_csv('template/case_lists/cases_all.txt', sep ='\t')
        df1.to_csv('study/case_lists/cases_all.txt', sep='\t', index=False)
        df.to_csv('study/case_lists/cases_all.txt', mode = 'a', sep='\t', header = False, index=False)
        df1 = pd.read_csv('template/case_lists/cases_sequenced.txt', sep ='\t')
        df1.to_csv('study/case_lists/cases_sequenced.txt', sep='\t', index=False)
        df.to_csv('study/case_lists/cases_sequenced.txt', mode = 'a', sep='\t', header = False, index=False)

        print("Data Clinical Patient...")
        f = open('sql/cbio_patients.sql','r')
        query = f.read()
        df = pd.read_sql_query(query, con=conn)
        df['patient_id'] = hasher(df['patient_id'])
        df1 = pd.read_csv('template/data_clinical_patient.txt', sep ='\t')
        df1.to_csv('study/data_clinical_patient.txt', sep='\t', index=False)
        df.to_csv('study/data_clinical_patient.txt', mode = 'a', sep='\t', header = False, index=False)
        print(df.head())

        #print(list(all_sample))
        maf_dir = 'maf/'
        for maf in os.listdir(maf_dir):
            maf_name = os.path.splitext(maf)[0]
            if maf_name in list(all_sample):
                cmd = 'cp -u ' + str(maf_dir) + '{m} maf_processed/'.format(m=maf)
                subprocess.run(cmd, shell=True)

        cmd = "awk 'FNR==1 {{next}} FNR==2 && NR!=2{{next;}}{{print}}' maf_processed/*.maf > study/data_mutations_extended.txt"
        subprocess.run(cmd, shell=True)

        tar_study()

    except Exception as e:
        print(e)

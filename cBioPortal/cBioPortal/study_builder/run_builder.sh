#!/usr/bin/env bash
module add python/gpu/3.7.6
pip install impyla
pip install kerberos

truncate -s 0 study/data*.txt
python study_builder.py build_study

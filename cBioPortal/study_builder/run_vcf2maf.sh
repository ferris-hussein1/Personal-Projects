#!/usr/bin/env bash
module add python/gpu/3.7.6
module load singularity/3.7.1

srun --partition=cpu_short --nodes=1 --ntasks=1 --cpus-per-task=1 --time=02:00:00 python study_builder.py vcf2maf > result.log

MAILTO=ferris.hussein

30 2 * * * ssh <\server removed\> sh study_builder/run_aws_sync.sh
00 6 * * * ssh <\server removed\> sh study_builder/run_vcf2maf.sh 2>&1
00 8 * 1 * ssh <\server removed\> sh study_builder/run_builder.sh
00 8 * * 1 rsync <\server removed\>:study_builder/study.tar.gz study.tar.gz

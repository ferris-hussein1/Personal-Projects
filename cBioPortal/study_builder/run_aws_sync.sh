#!/usr/bin/env bash

module load aws-cli/2

aws s3 sync <Bucket Removed> <Destination Removed> --exclude "*" --include "*.vcf"

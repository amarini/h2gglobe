#!/bin/bash

set -x

source "version.sh"

mkdir -p pileup

dir=/store/group/phys_higgs/cmshgg/reduced/${version}/mc/Summer12_S10_8TeV
dir=/store/user/amarini/reduced/reduction_RDMC_June2013_v1
dir=/store/user/amarini/reduced/reduction_RDMC_June2013_v1/mc/Summer12_DR53X-PU_RD1_START53_V7N

cd pileup 
rm *.root
cmsLs $dir | awk '{ print $5}' | grep '/' | grep -v broken | grep -v root > samples.txt 

echo "Hadding and copying"
../parallel --eta --joblog parallel_pileupMerger.log --progress "python ../Macros/pileup/pileupMerger.py --putBack {1}" :::: samples.txt



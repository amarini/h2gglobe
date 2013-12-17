#!/bin/bash
set +v

LABEL=2013_12_18

echo "Checking and creating pevents"
#Create Pevents -- allow mkfitter to do them concurrently is not a good idea

function create_pevents(){
	dat=$1
	tmpdat=${dat/datafile/tmp_datafile}
	echo "Dat file $dat tmp $tmpdat"
	[ -e $tmpdat.pevents ] || { cp $dat $tmpdat ; python fitter.py  -i $tmpdat --dryRun &> $tmpdat.log ; }
	echo "Done $tmpdat"
	}

create_pevents "massfac_mva_binned/datafiles_massfacmva_legacy.dat"  & 
create_pevents "massfac_mva_binned/datafiles_massfacmva_legacy_systs.dat"  & 
create_pevents "massfac_mva_binned/datafiles_massfacmva_legacy_7TeV.dat"  & 
create_pevents "massfac_mva_binned/datafiles_massfacmva_legacy_7TeV_systs.dat"  & 

create_pevents "baseline/datafiles_cutbased_legacy.dat"  & 
create_pevents "baseline/datafiles_cutbased_legacy_systs.dat"  & 
create_pevents "baseline/datafiles_cutbased_legacy_7TeV.dat"  & 
create_pevents "baseline/datafiles_cutbased_legacy_7TeV_systs.dat"  & 

wait

#### MVA ####
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy.dat -n 80  --onlySig -l legacy_paper_8TeV_${LABEL} -o ${USER}_mva_8TeV_Sig  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy.dat -n 50  --onlyBkg -l legacy_paper_8TeV_${LABEL} -o ${USER}_mva_8TeV_Bkg  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy_systs.dat -n 10   -l legacy_paper_8TeV_${LABEL} -o ${USER}_mva_8TeV_Syst  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy.dat -n 50  --onlyData -l legacy_paper_8TeV_${LABEL} -o ${USER}_mva_8TeV_Data  &
###### MVA 7TeV ###
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy_7TeV.dat -n 50  --onlyData -l legacy_paper_7TeV_${LABEL} -o ${USER}_mva_7TeV_Data  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy_7TeV.dat --onlySig -l legacy_paper_7TeV_${LABEL} -o ${USER}_mva_7TeV_Sig  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy_7TeV.dat -n 50  --onlyBkg -l legacy_paper_7TeV_${LABEL} -o ${USER}_mva_7TeV_Bkg  &
./mk_fitter.py -i massfac_mva_binned/datafiles_massfacmva_legacy_7TeV_systs.dat -n 10  -l legacy_paper_7TeV_${LABEL} -o ${USER}_mva_7TeV_Syst  &
##
###### CIC ######
./mk_fitter.py -i baseline/datafiles_cutbased_legacy.dat --onlySig -l legacy_paper_8TeV_${LABEL} -o ${USER}_cic_8TeV_Sig  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy.dat -n 50  --onlyBkg -l legacy_paper_8TeV_${LABEL} -o ${USER}_cic_8TeV_Bkg  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy_systs.dat   -l legacy_paper_8TeV_${LABEL} -o ${USER}_cic_8TeV_Syst  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy.dat -n 50  --onlyData -l legacy_paper_8TeV_${LABEL} -o ${USER}_cic_8TeV_Data  &
####### CIC 7TeV ###
./mk_fitter.py -i baseline/datafiles_cutbased_legacy_7TeV.dat -n 50  --onlyData -l legacy_paper_7TeV_${LABEL} -o ${USER}_cic_7TeV_Data  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy_7TeV.dat --onlySig -l legacy_paper_7TeV_${LABEL} -o ${USER}_cic_7TeV_Sig  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy_7TeV.dat -n 50  --onlyBkg -l legacy_paper_7TeV_${LABEL} -o ${USER}_cic_7TeV_Bkg  &
./mk_fitter.py -i baseline/datafiles_cutbased_legacy_7TeV_systs.dat  -l legacy_paper_7TeV_${LABEL} -o ${USER}_cic_7TeV_Syst  &

echo "Waiting"
wait
echo "DONE"
set -v

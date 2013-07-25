#!/bin/bash

. setup.sh

#rm mc_sig_grav/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_03/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_sig_grav.txt

#rm mc_spin2_summer12_s10/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_05/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_spin2_summer12_s10.txt

#rm data_2012/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_06/data ${storedir}/data data_2012.txt

#rm mc_dy_summer12_s10/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_02/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_dy_summer12_s10.txt
#
#rm mc_bkg_summer12_s10/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_03/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_bkg_summer12_s10.txt
#
#rm mc_bkg_summer12_s10_2/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_04/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_bkg_summer12_s10_2.txt
#
#rm mc_sig_summer12_s10/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V14_00_03/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_sig_summer12_s10.txt

#rm mc_spin2_summer12_s10/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_02/mc/Summer12_S10_8TeV ${storedir}/mc/Summer12_S10_8TeV mc_spin2_summer12_s10.txt

#DoubleElectron_Run2012A-22Jan2013-v1_AOD
#DoubleElectron_Run2012C-22Jan2013-v1_AOD
#DoublePhoton_Run2012B-22Jan2013-v1_AOD
#DoublePhoton_Run2012D-22Jan2013-v1_v3
#DoubleElectron_Run2012B-22Jan2013-v1_AOD
#DoubleElectron_Run2012D-22Jan2013-v1_v2
#DoublePhoton_Run2012C-22Jan2013-v2_AOD
#Photon_Run2012A_22Jan2013-v1_AOD

#rm data2012_RERECO/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_05/data /store/group/phys_higgs/cmshgg/reduced/rereco_june2013/data data2012_RERECO.txt
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_05/data ${storedir}/data data2012_RERECO.txt

#rm mc2012RD_1/*.dat
#rm mc2012RD_1/*.log
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/ ${storedir}/mc/Summer12_RD1 mc2012RD_1.txt
#rm mc2012RD_2/*.dat
#rm mc2012RD_2/*.log
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_RD1 ${storedir}/mc/Summer12_RD1 mc2012RD_2.txt
#rm mc2012RD_3/*.dat
#rm mc2012RD_3/*.log
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/ ${storedir}/mc/Summer12_RD1 mc2012RD_3.txt
#rm mc2012RD_4/*.dat
##rm mc2012RD_4/*.log
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_RD1 ${storedir}/mc/Summer12_RD1 mc2012RD_4.txt
#rm mc2012RD_5/*.dat
##rm mc2012RD_5/*.log
#./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N ${storedir}/mc/Summer12_DR53X-PU_RD1_START53_V7N mc2012RD_5.txt
#rm mcEWK/*.dat
#./AnalysisScripts/mk_reduction_dat.py /store/user/amarini/ ${storedir} mcEWK.txt

rm mc2012RD_6/*.log
./AnalysisScripts/mk_reduction_dat.py /store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N ${storedir}/mc/Summer12_DR53X-PU_RD1_START53_V7N mc2012RD_6.txt 

tar zcf ${version}.tgz  AnalysisScripts/{common,reduction,aux,*.py}

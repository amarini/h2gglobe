#!/bin/bash

#./submit_reduction.sh data2012_RERECO DoubleElectron_Run2012A-22Jan2013-v1_AOD 10
#./submit_reduction.sh data2012_RERECO DoubleElectron_Run2012C-22Jan2013-v1_AOD 80
#./submit_reduction.sh data2012_RERECO DoublePhoton_Run2012B-22Jan2013-v1_AOD 80
#./submit_reduction.sh data2012_RERECO DoublePhoton_Run2012D-22Jan2013-v1_v3 80 
#./submit_reduction.sh data2012_RERECO DoubleElectron_Run2012B-22Jan2013-v1_AOD 80
#./submit_reduction.sh data2012_RERECO DoubleElectron_Run2012D-22Jan2013-v1_v2 80
#./submit_reduction.sh data2012_RERECO DoublePhoton_Run2012C-22Jan2013-v2_AOD 80
#./submit_reduction.sh data2012_RERECO Photon_Run2012A_22Jan2013-v1_AOD 20

#./submit_reduction.sh mc2012RD_1 DYJetsToLL_M-50_TuneZ2Star_8TeV_T2CHCSCS 50
#
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-120_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-121_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-123_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-124_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-125_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-126_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-127_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-129_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 GluGluToHToGG_M-130_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-100_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-110_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-120_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-123_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-125_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-126_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-127_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-128_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-130_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-135_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 TTH_HToGG_M-145_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-115_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-120_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-121_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-123_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-124_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-125_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-126_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-135_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 VBF_HToGG_M-145_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-120_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-125_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-126_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-128_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-130_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-135_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-140_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-145_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-150_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#./submit_reduction.sh mc2012RD_2 WH_ZH_HToGG_M-95_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  10
#
#
#./submit_reduction.sh mc2012RD_3 GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_pf  30
#./submit_reduction.sh mc2012RD_3 GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_pp  30
#./submit_reduction.sh mc2012RD_3 GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV_ext-pythia6_pf  30
#./submit_reduction.sh mc2012RD_3 GJet_Pt40_doubleEMEnriched_TuneZ2star_8TeV_ext-pythia6_pp  30

#./submit_reduction.sh mc2012RD_4 GluGluToHToGG_M-115_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1   10
#./submit_reduction.sh mc2012RD_4 TTH_HToGG_M-140_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 TTH_HToGG_M-95_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 VBFHToGG_M-125_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1   10
#./submit_reduction.sh mc2012RD_4 VBF_HToGG_M-128_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1   10
#./submit_reduction.sh mc2012RD_4 VBF_HToGG_M-130_8TeV-powheg-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 WH_ZH_HToGG_M-105_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 WH_ZH_HToGG_M-115_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 WH_ZH_HToGG_M-123_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10
#./submit_reduction.sh mc2012RD_4 WH_ZH_HToGG_M-140_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1   10
#./submit_reduction.sh mc2012RD_4 WH_ZH_HToGG_M-90_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2   10


#./submit_reduction.sh mc2012RD_5 DiPhotonBox_Pt-10To25_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1 50
#./submit_reduction.sh mc2012RD_5 DiPhotonJets_M0_8TeV-madgraph_Summer12_DR53X-PU_RD1_START53_V7N-v1 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_ff 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_pf 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_pp 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_ff 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_pf 50
#./submit_reduction.sh mc2012RD_5 QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1_pp 50

#./submit_reduction.sh mc2012RD_6 DiPhotonBox_Pt-10To25_8TeV-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1 30
#./submit_reduction.sh mc2012RD_6 DiPhotonBox_Pt-250ToInf_8TeV_ext-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v1 30
#./submit_reduction.sh mc2012RD_6 DiPhotonBox_Pt-25To250_8TeV_ext-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  30
#./submit_reduction.sh mc2012RD_6 DiPhotonBorn_Pt-10To25_8TeV_ext-pythia6_Summer12_DR53X-PU_RD1_START53_V7N-v2  30
#./submit_reduction.sh mc2012RD_6 DiPhotonJets_8TeV-madgraph-tarball-v2_Summer12_DR53X-PU_RD1_START53_V7N-v1    30
./submit_reduction.sh mc2012RD_6 DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_RD1_START53_V7N-v1    30

#./submit_reduction.sh mcEWK EWK 10

#./submit_reduction.sh    data_2012             Photon_Run2012A-13Jul2012-v1                    10
#./submit_reduction.sh    data_2012             Photon_Run2012A-recover-06Aug2012-v1            1
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012B-13Jul2012-v1              50
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012C-24Aug2012-v2              10
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012C-EcalRecover_11Dec2012-v1  4
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012C-PromptReco-v2             60
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012C-PromptReco-v2_sub2        10
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012D-PromptReco-v1             60
#./submit_reduction.sh    data_2012             DoublePhoton_Run2012D-PromptReco-v1_sub2        10
#./submit_reduction.sh    data_2012             run2012D_DE                                     80
#
#./submit_reduction.sh     mc_bkg_summer12_s10_2 DiPhotonJets_8TeV-madgraph-tarball-v2_Summer12_DR53X-PU_S10_START53_V7A-v1              40
#./submit_reduction.sh     mc_dy_summer12_s10    DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1   50
#
#./submit_reduction.sh     mc_bkg_summer12_s10   DiPhotonBox_Pt-10To25_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1     5
#./submit_reduction.sh     mc_bkg_summer12_s10   DiPhotonBox_Pt-250ToInf_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1   10
#./submit_reduction.sh     mc_bkg_summer12_s10   DiPhotonBox_Pt-25To250_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1    10
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pp  20
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pf  30
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt-20to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_ff  20
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pp   10
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pf   20
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_ff   30
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pp       10
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_pf       20
#./submit_reduction.sh     mc_bkg_summer12_s10   QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_ff       30
#./submit_reduction.sh     mc_bkg_summer12_s10   WGToLNuG_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1   10
#./submit_reduction.sh     mc_bkg_summer12_s10   WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1    10
#./submit_reduction.sh     mc_bkg_summer12_s10   WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1    10
#./submit_reduction.sh     mc_bkg_summer12_s10   WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1   10
#./submit_reduction.sh     mc_bkg_summer12_s10   ZGToLLG_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1    10
#./submit_reduction.sh     mc_bkg_summer12_s10   ZZJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v3    10
#./submit_reduction.sh     mc_bkg_summer12_s10   ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1   10
#./submit_reduction.sh     mc_bkg_summer12_s10   ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1   10
#
#./submit_reduction.sh     mc_bkg_summer12_s10   Wpgg_dR02   8
#./submit_reduction.sh     mc_bkg_summer12_s10   Wmgg_dR02   8
#./submit_reduction.sh     mc_bkg_summer12_s10   Zgg_dR02    8 
#./submit_reduction.sh     mc_bkg_summer12_s10   ttgg_dR02   2
#
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt40_v2_ff   40
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt40_v2_pf   80
#./submit_reduction.sh     mc_bkg_summer12_s10   GJet_Pt40_v2_pp   60
#
#./submit_reduction.sh     mc_bkg_summer12_s10   TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S8_START52_V9-v1    20
#
#./submit_reduction.sh     mc_bkg_summer12_s10   TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1    20
#./submit_reduction.sh     mc_bkg_summer12_s10   TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S8_START52_V9-v1    20
#
#
#./submit_reduction.sh     mc_sig_summer12_s10   \*     5
#./submit_reduction.sh     mc_spin2_summer12_s10 \*     5



wait

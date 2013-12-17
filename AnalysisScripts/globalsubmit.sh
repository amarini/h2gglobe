#!/bin/bash
set -v
#### MVA ####
screen -m -d -S submit -t "CONTROL" bash -c "while sleep 1h ; do bjobs ; done" ; 

 screen -r submit -d -X screen -fn -t mva_8TeV_Sig  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_8TeV_Sig  -q 8nh -l sub &>log_1.txt" ;
 screen -r submit -d -X screen -fn -t mva_8TeV_Bkg  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_8TeV_Bkg  -q 8nh -l sub &>log_2.txt" ;
 screen -r submit -d -X screen -fn -t mva_8TeV_Syst -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_8TeV_Syst -q 8nh -l sub &>log_3.txt" ;
 screen -r submit -d -X screen -fn -t mva_8TeV_Data -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_8TeV_Data -q 8nh -l sub &>log_4.txt" ;
### MVA 7TeV####
 screen -r submit -d -X screen -fn -t mva_7TeV_Data -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_7TeV_Data -q 8nh -l sub &>log_5.txt" ;
 screen -r submit -d -X screen -fn -t mva_7TeV_Sig  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_7TeV_Sig  -q 8nh -l sub &>log_6.txt" ;
 screen -r submit -d -X screen -fn -t mva_7TeV_Bkg  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_7TeV_Bkg  -q 8nh -l sub &>log_7.txt" ;
 screen -r submit -d -X screen -fn -t mva_7TeV_Syst -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_mva_7TeV_Syst -q 8nh -l sub &>log_8.txt" ;

#### CIC #####
 screen -r submit -d -X screen -fn -t cic_8TeV_Sig  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_8TeV_Sig  -q 8nh -l sub &>log_9.txt" ;
 screen -r submit -d -X screen -fn -t cic_8TeV_Bkg  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_8TeV_Bkg  -q 8nh -l sub &>log_10.txt" ;
 screen -r submit -d -X screen -fn -t cic_8TeV_Syst -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_8TeV_Syst -q 8nh -l sub &>log_11.txt" ;
 screen -r submit -d -X screen -fn -t cic_8TeV_Data -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_8TeV_Data -q 8nh -l sub &>log_12.txt" ;
### CIC 7TeV####
 screen -r submit -d -X screen -fn -t cic_7TeV_Data -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_7TeV_Data -q 8nh -l sub &>log_13.txt" ;
 screen -r submit -d -X screen -fn -t cic_7TeV_Sig  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_7TeV_Sig  -q 8nh -l sub &>log_14.txt" ;
 screen -r submit -d -X screen -fn -t cic_7TeV_Bkg  -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_7TeV_Bkg  -q 8nh -l sub &>log_15.txt" ;
 screen -r submit -d -X screen -fn -t cic_7TeV_Syst -l bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;  python submit_fitter.py -d ${USER}_cic_7TeV_Syst -q 8nh -l sub &>log_16.txt" ;

set +v

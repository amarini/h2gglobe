#!/bin/bash
set -v
#### MVA ####
screen -m -d -S check -t "CONTROL" bash -c "while sleep 1h ; do bjobs ; done"

 screen -r check -d -X screen -fn -t mva_8TeV_Sig  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_8TeV_Sig  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_8TeV_Bkg  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_8TeV_Bkg  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_8TeV_Syst bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_8TeV_Syst ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_8TeV_Data bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_8TeV_Data ); do sleep 360 ; done" 
### MVA 7TeV####                                                                                                    
 screen -r check -d -X screen -fn -t mva_7TeV_Data bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_7TeV_Data ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_7TeV_Sig  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_7TeV_Sig  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_7TeV_Bkg  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_7TeV_Bkg  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t mva_7TeV_Syst bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_mva_7TeV_Syst ); do sleep 360 ; done" 
                                                                                                                   
#### CIC #####                                                                                                     
 screen -r check -d -X screen -fn -t cic_8TeV_Sig  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_8TeV_Sig  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_8TeV_Bkg  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_8TeV_Bkg  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_8TeV_Syst bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_8TeV_Syst ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_8TeV_Data bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_8TeV_Data ); do sleep 360 ; done" 
### CIC 7TeV####                                                                                                    
 screen -r check -d -X screen -fn -t cic_7TeV_Data bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_7TeV_Data ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_7TeV_Sig  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_7TeV_Sig  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_7TeV_Bkg  bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_7TeV_Bkg  ); do sleep 360 ; done" 
 screen -r check -d -X screen -fn -t cic_7TeV_Syst bash -c "cd $PWD ;source ~/.bashrc; eval \`scramv1 runtime -sh\`;while( ! ./check_fitter.py ${USER}_cic_7TeV_Syst ); do sleep 360 ; done" 

set +v

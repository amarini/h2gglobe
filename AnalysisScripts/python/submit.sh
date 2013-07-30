#!/bin/bash

FILE="scale"
DIR="/store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N/DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_RD1_START53_V7N-v1/"
DIR="/store/group/phys_higgs/cmshgg/processed/V15_00_05/mc/Summer12_DR53X-PU_S10_START53_V7C/DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_S10_START53_V7C-v1_v3"
OUT="$PWD/outputV150005"
QUEUE=8nh
NJOBS=100

[ -z "$1" ] || DIR=$1
[ -z "$2" ] || FILE=$2
[ -z "$3" ] || OUT=$3

mkdir $OUT
for i in `seq 0 $((NJOBS-1))`; do bsub -q $QUEUE -o $OUT/${FILE}_$i.txt <<EOF
 cd $PWD
 export "SCRAM_ARCH=$SCRAM_ARCH"
 eval \`scramv1 runtime -sh\`
 python computeScale.py --path=$DIR --nJobs=$NJOBS --jobId=$i
EOF

done

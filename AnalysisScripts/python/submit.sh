#!/bin/bash

FILE="scale"
DIR="/eos/cms/store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N/DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_RD1_START53_V7N-v1/"
OUT="$PWD/output"
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

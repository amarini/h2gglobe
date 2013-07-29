#!/bin/bash

FILE=$1
[ -z "$1" ] && FILE="scale"

DIR=$2
[ -z "$2" ] && DIR="output"

echo "DIRECTORY=$DIR"
echo "FILES=$FILE"

cd $DIR 
tail -n 20 ${FILE}_*.txt  | grep 'Sw\|nT'  | sed 's/Sw=/@/' | sed 's/nT=//' | tr '\n' ' ' | sed 's/@/\r\n/g' | awk 'BEGIN{Sw=0;nT=0;}{Sw+=$1;nT+=$2;}END{print nT " " Sw " " nT/Sw ;}'
cd - &> /dev/null

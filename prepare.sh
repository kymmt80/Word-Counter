#!/bin/bash
if [ ! -d "testcases" ]; then
mkdir -p testcases;
fi
cd input
var1=$(ls)
i=1
for line in $var1
do
    cp $line ../testcases/"$i".csv
    i=$((i+1))
done

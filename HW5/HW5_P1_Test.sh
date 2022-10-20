#!/bin/bash 
count=$1 
rm input 
rm your_output 
rm standard_output 
echo "================== input ======================" 
echo ${count} | tee input 
for (( i=0; i<${count}; i++ )); 
do 
  echo $RANDOM 
done | tee -a input 
echo "============= execution result ================" 
cat input | ./HW5_P1 | tee your_output 
tail -n +2 input | sort -n > standard_output 
echo "====== differences from correct result =======" 
diff  your_output  standard_output 
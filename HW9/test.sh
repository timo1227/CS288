#!/bin/bash 
count=$1 
echo "==== ============== Writing files ======================" 
for (( i=0; i<${count}; i++ )); 
do 
  echo $RANDOM 
done | ./HW9_Problem1_prg1
ls -l ./numbers.txt ./numbers.bin  
echo "================== Reading files ======================" 
for (( i=0; i<$2; i++ )); 
do 
  echo $(($RANDOM % ${count})) 
done | ./HW9_Problem1_prg2 
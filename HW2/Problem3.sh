#!/bin/bash

# Save arguments to variables
args=("$@")

# Sort the array in accending order
for ((i=0; i<${#args[@]}; i++))
do
    for ((j=i+1; j<${#args[@]}; j++))
    do
        if [ ${args[i]} -gt ${args[j]} ]
        then
            temp=${args[i]}
            args[i]=${args[j]}
            args[j]=$temp
        fi
    done
done

# Print the sorted array
echo "Sorted Array: ${args[@]}"

#!/bin/bash

# Save arguments to variables
path=$1

# Function to reverse an Array
function reverseArray() {
    local -n array=$1
    local -n reversedArray=$2
    local i
    for (( i=${#array[@]}-1; i>=0; i-- )); do
        reversedArray+=("${array[i]}")
    done
}

# Check if arg is Directory 
if [ -d $path ]
then
    OIFS=$IFS
    IFS=$'\n'
    # Get all files in directory
    files=($(ls -p $path | grep -v /))
    # Reverse the array
    reverseArray files reversedFiles

    # Print the reversed array
    echo "Original Array: ${files[@]}"
    echo "Reversed Array : ${reversedFiles[@]}"

    # Restore IFS
    IFS=$OIFS
else
    echo "$path is not a valid directory"
fi


#!/bin/bash

traverse_del() {
    for file in "$1"/*; do
        if [ -d "$file" ]; then
            echo "Entering subdirectory $file"
            traverse_del "$file"
        else
            # Check if file is size 0
            if [ ! -s "$file" ]; then
                echo "$file is empty , deleting"
                rm "$file"
            fi
        fi
    done
}

# Save the current directory
curDir=$(pwd)
# Check if Dir is Passed and Exists
if [ $# -eq 1 ]
then 
    if [ -d $1 ]
    then
        curDir=$1
    else
        echo "Directory does not exist"
        exit 1
    fi
fi

traverse_del $curDir

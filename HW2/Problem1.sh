#!/bin/bash

# Save arguments to variables
args=( $@ )

# Check if arg is Directory or File
for arg in ${args[@]}
do
    if [ -d $arg ]
    then
        echo "Directory"
    elif [ -f $arg ]
    then
        # Save File Size
        size=$(stat -c%s "$arg")
        # Check if File Size 
        if [ $size -gt 1048576 ]
        then
            echo "Large File"
        elif [ $size -gt 102400 ]  && [ $size -lt 1048576 ]
        then
            echo "Medium File"
        else
            echo "Small File"
        fi

    else
        echo "$arg is not valid"
    fi
done


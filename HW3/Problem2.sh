#!/bin/bash

# Function to traverse the directory
function traverse ()
{
    directory=$1
    user=$2
    for file in $directory/*; do
        if [ -d "$file" ]; then
            traverse $file $user
        else
            # Checking if file is owned by user
            if [ "$(ls -l $file | grep $user | wc -l)" -eq 1 ]; then
                # Checking if file is Readable to all
                if [ "$(ls -l $file | grep r..r..r.. | wc -l)" -eq 1 ]; then 
                    # Extract file Date and Time
                    fileDate=$(ls -l $file | grep -o -E '[A-Z][a-z]{2} .. ([0-9]{2}:[0-9]{2} || [0-9]{4})')
                    # Extract Permission
                    permission=$(ls -l $file | grep -o -E 'r..r..r..')

                    echo "Path: $file"
                    echo "Permission: $permission"
                    echo "Date: $fileDate"
                    echo ""

                fi
            fi
        fi
    done
}

# Set Initial Variables

dir=$1
userID=$2

echo "The directory is $dir"
echo "The user is $userID"
echo ""

# Check if user exist 

if [ ! $(id -u $userID) ]; then
    exit 1
fi

# Check if the directory exists
if [ -d $dir ]; then
    traverse $dir $userID
else
    echo "Directory does not exist"
    exit 1
fi


# Downloaded using scp 
# scp timestrada@34.139.65.240:/home/timestrada/CS288/HW3/Problem2.sh /Users/Timo/Desktop/CS288/HW3   


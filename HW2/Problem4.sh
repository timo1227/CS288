#!/bin/bash

# itterate through Bash Commands under the /bin directory
for file in /bin/*
do
    # if the file is a regular file
    if [ -f $file ]
    then
        #only allow files that begin with a letter
        if [[ $file =~ ^/bin/[a-z] ]]
        then
            # Grab the file's first letter
            firstLetter=${file:5:1}
            # Create Map of first letter to count
            declare -A letterCount
            # If the letter is not in the map, add it
            if [ -z ${letterCount[$firstLetter]} ]
            then
                letterCount[$firstLetter]=1
            # If the letter is in the map, increment it
            else
                letterCount[$firstLetter]=$((${letterCount[$firstLetter]}+1))
            fi
        fi
    fi
done

# Print the map in alphabetical order
for letter in {a..z}
do
    if [ -n ${letterCount[$letter]} ]
    then
        #if the count is empty, print 0
        if [ -z ${letterCount[$letter]} ]
        then
            echo $letter: 0
        else
            echo $letter: ${letterCount[$letter]}
        fi
    fi
done


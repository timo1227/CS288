#!/bin/bash

traverse_del() {
    for file in "$1"/*; do
        # Check if directory is empty
        if [ -d "$file" ]; then
            if [ "$(ls -A $file)" ]; then
                traverse_del "$file"
            else
                echo "$file is empty , deleting"
                rmdir "$file"
            fi
        else
            rm "$file"
        fi
    done
}

dir=$1
echo "$dir"
echo "$(ls -A $dir)"
traverse_del $dir
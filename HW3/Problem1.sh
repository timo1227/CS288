#!/bin/bash

# Function to combine the txt files into one file

function combineText()
{
    file=$1
    # cat file to AllPages.txt
    cat $file >> WikiPages/AllPages.txt
    # Remove the file
    rm $file
}

# Set Initial Variables
firstLetter=A
secondLetter=A
domain="http://en.wikipedia.org/wiki/"

# The directory to save the wiki pages
mkdir WikiPages
directory=WikiPages

# The html2text options
html2textOptions="-nobs -style pretty"

# The wget options
wgetOptions="-q"

# The file extension
fileExtension=.html

# The file extension for the text files
textFileExtension=.txt

# Cobine the domain and the first letter to get the first page
Page=$domain$firstLetter$secondLetter

# Use wget to download the first page with the wget options and save it in the directory
wget $wgetOptions -O $directory/$firstLetter$secondLetter$fileExtension $Page

# Convert the html file to a text file
html2text $html2textOptions $directory/$firstLetter$secondLetter$fileExtension > $directory/$firstLetter$secondLetter$textFileExtension

# Delete the html file
rm $directory/$firstLetter$secondLetter$fileExtension


# Count the words in the first page
combineText $directory/$firstLetter$secondLetter$textFileExtension

echo "Downloading All Data ..."

# Loop through the alphabet until firstLetter is Z and secondLetter is Z
while [ $firstLetter$secondLetter != '00' ]; do
    # If secondLetter is Z then increment firstLetter and set secondLetter to A
    if [ $secondLetter = Z ]; then
        firstLetter=$(echo $firstLetter | tr '[A-Z]' '[B-Z]')
        secondLetter=A
    else
        # Increment secondLetter
        secondLetter=$(echo $secondLetter | tr '[A-Z]' '[B-Z]')
    fi
    # Combine the domain and the first letter to get the first page
    Page=$domain$firstLetter$secondLetter
    # Use wget to download the first page with the wget options and save it in the directory
    wget $wgetOptions -O $directory/$firstLetter$secondLetter$fileExtension $Page

    # Convert the html file to a text file
    html2text $html2textOptions $directory/$firstLetter$secondLetter$fileExtension > $directory/$firstLetter$secondLetter$textFileExtension

    # Delete the html file
    rm $directory/$firstLetter$secondLetter$fileExtension

    combineText $directory/$firstLetter$secondLetter$textFileExtension

    if [ $firstLetter$secondLetter = ZZ ]; then
        firstLetter=0
        secondLetter=0
    fi
done

echo "Download and Conversion Complete."
echo ""

# Print top 5 words and their frequency from the wordCount array
echo "Top 5 words and their frequency"
echo "Frequency Word"
echo "----------------"
grep -o -i "[a-z]*" WikiPages/AllPages.txt | sort | uniq -c | sort -nr | head -5

# Delete All temp files and Directory
rm WikiPages/AllPages.txt
rmdir WikiPages
#!/bin/sh

TMP_FILE=temp_temp.tmp
if [ ! $# -eq 3 ]
then
    echo "Usage: replace.sh match pattern file";
    exit;
fi
sed -e "s/$1/$2/g" $3 > $TMP_FILE
mv $TMP_FILE $3

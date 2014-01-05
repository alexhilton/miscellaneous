#!/bin/sh
if [ $# -lt 1 ];
then
    echo "Usage: mycp.sh from [to], default to is current directory;";
    exit;
fi
if [ -d $1 ];
then
    OPT=-r
fi
if [ $# -eq 1 ];
then
    TO=$PWD
fi
cp $OPT $1 $TO;
FILE=${1##/*/};
if [ -d $TO/$FILE ];
then
    chmod -R 744 $TO/$FILE;
else
    chmod 744 $TO/$FILE;
fi

#!/bin/sh

if [ ! $# -eq 1 ]
then
    echo "You must specify the tar.gz package";
    exit
fi
TARGET=${1%%.tgz}
#VERSION=${TARGET:+([0-9])}
#echo $TARGET
#echo $VERSION
#exit
tar xfz $1
if [ -d $TARGET ]
then
    TARGET="$TARGET-1"
    echo $TARGET;
fi
mv alps $TARGET
rm -fr $1

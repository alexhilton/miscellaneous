#!/bin/bash

if [ $# != 2 ]; then
    echo "usage $0 line file";
    exit;
fi
sed -n -e "1 i$1" -e "1 s/^ //" -e 'p' $2;

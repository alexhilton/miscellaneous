#!/bin/bash

str="hello, world";
empty='';
if [ -n "$empty" ]; then
    echo "'$empty' is not empty";
else
    echo "'$empty' is a empty string";
fi

if [ -f "$empty" ]; then
    echo "'$empty' is a file and exists";
else
    echo "'$empty' is not a file";
fi

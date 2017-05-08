#!/bin/bash
echo Spliting 
TRAINFILE="breast-cancer-wisconsin.data"
echo Shuffling the file
gshuf $TRAINFILE -o "$TRAINFILE.shuffle"
echo Number of lines
LINENUMBER="$(wc -l $TRAINFILE | grep -Eo '[0-9]{1,10}')"
echo "${LINENUMBER}"
EACHCOUNT="$(($LINENUMBER /10))"
echo $(($LINENUMBER - $EACHCOUNT * 9))

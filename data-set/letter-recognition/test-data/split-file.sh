#!/bin/bash
LINE_COUNT=`wc -l letter-recognition.sorted | awk '{print $1;}'`
echo $LINE_COUNT
LINE_NUMBER=$(( LINE_COUNT/26 ))
echo $LINE_NUMBER
csplit letter-recognition.sorted $LINE_NUMBER {25}

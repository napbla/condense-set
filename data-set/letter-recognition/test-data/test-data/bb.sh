#!/bin/bash
for i in $(seq 0 9); do
	gshuf mydata.s0$i -o mydatashuffle.s0$i
done	

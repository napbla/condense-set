#!/bin/bash
for i in $(seq 0 9); do
		rm  mydata.s0$i
	
	for j in $(seq 0 25); do
		cat data$j.s0$i >> mydata.s0$i
	done
done

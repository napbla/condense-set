#!/bin/bash
for i in $(seq 0 9); do
	cp mydatashuffle.s0$i data$i.tes
	for j in $(seq 0 9); do
		if [ $j != $i ]; then
			cat mydatashuffle.s0$j >> data$i.tra
		fi
	done
done

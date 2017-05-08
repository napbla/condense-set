#!/bin/bash
rm report.txt
for i in $(seq 0 9); do
	echo "data $i" 
	for j in $(seq 1 10); do
		echo "k=$j"
		echo "full set"
		echo -n "$i & $j & " >> report.txt
		/usr/bin/time ./knn2 data$i.tra data$i.tes , 0 $j 0 0 > k$j-data$i.res 2> time.log
		cat time.log | grep -Eo '[0-9]{1,4}.[0-9]{1,4}' | head -1 | tr '\n' ' ' >> report.txt
		echo -n "& " >> report.txt
		tail -n 1 k$j-data$i.res | tr '\n' ' ' >> report.txt
		echo -n "& " >> report.txt
		echo "condense set"
		/usr/bin/time ./knn2 data$i.con data$i.tes , 0 $j 0 0 > ck$j-data$i.res 2> time.log
		cat time.log | grep -Eo '[0-9]{1,4}.[0-9]{1,4}' | head -1 | tr '\n' ' ' >> report.txt
		echo -n "& " >> report.txt
		tail -n 1 ck$j-data$i.res | tr '\n' ' ' >> report.txt
		echo "" >> report.txt
    done
done

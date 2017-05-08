#!/bin/bash
# Map character to integer eg. A -> 1, B -> 2
chr () {
	local val
	[ "$1" -lt 256 ] || return 1
	printf -v val %o "$1"; printf "\\$val"
	# That one requires bash 3.1 or above.
}

cp letter-recognition.data letter-recognition.mapped

for i in $(seq 65 90); do
		sed -ie "s/$(chr "$i")/$(($i-65))/g" letter-recognition.mapped
done
# Why error ?
rm letter-recognition.mappede

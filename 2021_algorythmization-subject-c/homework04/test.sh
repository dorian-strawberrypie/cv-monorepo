#!/bin/bash

DIR="test_data"

for F in {0000..0100} ; do
	if [ ! -e $DIR/${F}_in.txt ] ; then
		echo "All ok"
		exit 1
	fi

	./a.out < $DIR/${F}_in.txt > out

	if ! diff out $DIR/${F}_out.txt ; then
		echo "Mismatch: $F"
		exit 1
	fi
done
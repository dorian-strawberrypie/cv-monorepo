#!/bin/bash

DIR="CZE"

for F in {0000..0100} ; do
	if [ ! -e $DIR/${F}_in.txt ] ; then
		echo "All ok"
		exit 1
	fi

	./a.out < $DIR/${F}_in.txt > out.txt

	if ! diff out.txt $DIR/${F}_out.txt ; then
		echo "Mismatch: $F"
		exit 1
	fi
done

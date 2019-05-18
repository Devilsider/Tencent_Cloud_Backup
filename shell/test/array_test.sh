#!/bin/bash
a=(3 10 2 3 4 7 8 9 10)
x=0
while [$x < ${#a[*]}]
do
	echo ${a[x]}
	x=$(($x+1))
done


b=(3 10 2 3 4 7 8 9 10)
i=0
while((i<10))
do
	echo ${b[$i]}
	i=$(($i+1))
done


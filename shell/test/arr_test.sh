#!/bin/bash
a=(3 10 6 5 9 2 8 1 4 7)
i=0
while((i<10))
do 
	echo ${a[i]}
	i=$(($i+1))
done


#!/bin/bash
a=(3 10 20 38 78 90 78 632 1010 2323)
for ((i=1;i<10;++i))
do 
	for ((j=0;j<10-i;++j))
	do
		if [ ${a[j]} -gt ${a[j+1]} ]
		then
			temp=${a[j]}
			a[j]=${a[j+1]}
			a[j+1]=$temp
		fi
	done
done
for ((i=0;i<10;++i))
do
	echo ${a[i]}
done


#!/bin/bash
for myfile in /home/ubuntu/
do
	if [ -d "$myfile" ]
	then
		echo "$myfile(dir)"
	else
		echo "$myfile"
	fi
done


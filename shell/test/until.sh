#!/bin/bash
myvar=0
until [ $myvar -eq 10 ]
do
	echo $myvar
	myvar=$(($myvar+1))
done


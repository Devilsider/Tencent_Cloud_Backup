#!/bin/bash
a="hello"
echo "hello b$aa"
echo "hello b${a}a"
echo "${a}a"
echo '${a}a'
echo '\${a}a'
read a
echo $?
echo $a 
a=What\'s\your\\"topic"\"\?
echo $a 
echo `date`
echo $(date)
echo `pwd`
echo $(pwd)


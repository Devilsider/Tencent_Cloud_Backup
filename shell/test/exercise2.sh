#!/bin/bash
#this is mu first shell
read dir
mkdir ${dir}
cp -rf /home/ubuntu/20190410/* ${dir}
ls -l /home/ubuntu/20190410/*|grep ^d|wc -l > dir.txt


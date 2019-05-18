#!/bin/bash
echo "please input a year"
read year
test $(($year%400)) -eq 0 -o $(($year%4)) -eq 0 -a $(($year%100)) -ne 0


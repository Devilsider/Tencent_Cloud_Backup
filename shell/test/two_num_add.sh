#!/bin/bash
function add()
{
	return $(($1+$2))
}
a=10
b=20
add a b
echo $?

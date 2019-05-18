#!/bin/bash
echo "Is it morning?Please answer yes or no."
read yes_or_no
case "$yes_or_no" in
	yes|y|Yes|YES)
		echo "Good Morning!";;
	[nN]*)
		echo "Good Afternoon";;
		*)
		echo "Sorry,$yes_or_no not recognized.Enter yes or no."
		exit 1;;
esac


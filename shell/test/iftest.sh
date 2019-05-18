#!/bin/bash
if test -f $1 -a -r $1 -a -w $1 
then
	cat $1
elif test -d $1 
then
	cd $1
	if test -e ls.sh 
	then
		chmod +x ls.sh
		./ls.sh
	else
		touch ls.sh
		echo "#!/bin/bash">>ls.sh
		echo "ll /home">>ls.sh
		chmod +x ls.sh
		./ls.sh
	fi
fi

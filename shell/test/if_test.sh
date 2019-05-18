#!/bin/bash
	if[-f $1 -a -r $1 -a -w $1]
	$1 -a -r $1 -a -w$1
	then
		cat $1
	elif[-d $1]
	then
		cd $1
		if[-e ls.sh]
		then
			chmod +x ls.sh
			./ls.sh
		else
			touch ls.sh
			echo "#!/bin/bash">>ls.sh
			echo "ls -li/etc>etc.list">>ls.sh
			chmod +x ls.sh
			./ls.sh
		fi
	fi


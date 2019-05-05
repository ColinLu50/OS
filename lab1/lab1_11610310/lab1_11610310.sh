#!/bin/bash
IFS=$'\n\b'

#function sudocode()
#{
#	queue q
#	q.add(root)
#	while q is not empty
#		curr = q.get()
#		show all in curr
#		if curr is a directory
#			q.add(curr)
#		
#}



function displayDir()
{	
	
	currName=`basename $1`
	echo "[$currName]" >> $2
	for file in `ls $1`
	do
		# echo $file
		abpath=`readlink -e $1/$file`
		echo $abpath >> $2
	done
	echo '' >> $2
}

function iterAllFile()
{
	dir_count=0
	file_count=0
	queue=("$1")
	head=0
	tail=1
	

	while [ $head -lt $tail ]
	do
		curr=${queue[$head]}
		unset queue[$head]
		# print all files in this folder
		displayDir $curr "$2"

		let "head+=1"
		for file in `ls $curr`
		do
			
			if [ -d "$curr/$file" ] # if is a directory
			then
				tmp="$curr/$file"
				queue[$tail]=$tmp
				let "tail+=1"
				let "dir_count+=1"
			else
				let "file_count+=1"
			fi
		done
	done
	echo "[Directories Count]:$dir_count" >> $2
	echo "[Files Count]:$file_count" >> $2
}


# testdir=/home/luning/workspace/OS

testdir=`readlink -e $1`

if [ -f "$2" ]
then
	true>$2
else
	mkdir -p `dirname $2`
fi

iterAllFile $testdir $2

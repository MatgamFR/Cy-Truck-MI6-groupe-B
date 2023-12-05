#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Error don't have any argument'"
	exit 1
fi

if [ ! -f $1 ]
then
	echo "Error $1 is not a File"
	exit 2
fi

clear_terminal () {
	echo "${enDefaut}"
	reset > /dev/null
	}
	
help=0
d1=0
d2=0
l=0
t=0
s=0

for i in `seq 2 $#`
do
	case ${!i} in
		"-h") help=1 d1=0 d2=0 l=0 t=0 s=0
		break  ;;
		"-d1") d1=1  ;;
		"-d2") d2=1  ;;
		"-l") l=1  ;;
		"-s") s=1  ;;
		"-t") t=1  ;;
		*) echo "The argument ${!i} don't exist'"
	esac
done

if [ $help -eq 1 ]
then
	clear_terminal
	echo "-h displays help menu"
fi

if [ $d1 -eq 1 ]
then
	clear_terminal
	echo "ça arrive bientot tkt"
fi

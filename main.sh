#!/bin/bash

##count time
debut=$(date +%s)

#with and height terminal
width=$(tput cols)
height=$(tput lines)

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
	#echo "${enDefaut}"
	reset > /dev/null
	}
	
initialiser_variables () {
	# COULEURS

	fdNoir='\033[40m'
	fdRouge='\033[41m'
	fdVert='\033[42m'
	fdJaune='\033[43m'
	fdBleu='\033[44m'
	fdRose='\033[45m'
	fdCyan='\033[46m'
	fdGris='\033[47m'
	# fdDefaut='\033[49m'

	enNoir='\033[30m'
	enRouge='\033[31m'
	enVert='\033[32m'
	enJaune='\033[33m'
	enBleu='\033[34m'
	enRose='\033[35m'
	enCyan='\033[36m'
	enGris='\033[37m'
	# enDefaut='\033[39m'

	enGras='\033[1m'
	enSouligner='\033[4m'
	enClignotant='\033[5m'
	enSurligner='\033[7m'
	enCache='\033[8m'

	enDefaut='\033[0m'

	# GENERALES
	nbre_radios=0
	nbre_page_radio=0

	la_pageRadio=1
	# sous_recherche=" "
	fichier_log=""

	tete_de_page=""
	pied_de_page=""

	# affiche les fréquences ou non
	bool_show_freq=false # bool_show_freq=true

} # fin de initialiser_variables

create_space () {
	for i in `seq 0 $n`
	do
		echo -n " "
	done
}
	
help=0
d1=0
d2=0
l=0
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

clear_terminal
initialiser_variables


if [ $help -eq 1 ]
then
	n=$(echo "($width - 9)/2" | bc)
	create_space 
	echo -e "${enGras}${enRouge}Help Menu${enDefaut}"
	n=$(echo "($width - 67)/2" | bc)
	create_space
	echo -e "${enGras}${enVert}                    _________________________________________________"
    create_space 
    echo "            /|     |                                                 |"
    create_space 
    echo "            ||     |                                                 |"
    create_space 
    echo -e "       .----|-----,|                     ${enDefaut}CY-TRUCK${enGras}${enVert}                    |"
    create_space 
    echo "       ||  ||   ==||                                                 |"
    create_space 
    echo "  .-----'--'|   ==||                                                 |"
    create_space 
    echo "  |)-      ~|     ||_________________________________________________|"
    create_space 
    echo "  | ___     |     |____...==..._  >\______________________________|"
    create_space 
    echo " [_/.-.\'--'-------- //.-.  .-.\\\/   |/            \\\ .-.  .-. //"
    create_space 
    echo "   ( o )'===''''''''''( o )( o )     o              '( o )( o )'"
    create_space 
    echo -e "    '-'                '-'  '-'                       '-'  '-'${enDefaut}"
    echo
	echo "-h displays help menu"
	echo -e "${enGras}Press [Enter] to continue${enDefaut}"
	read -p ""
fi

if [ $d1 -eq 1 ]
then
	echo "ça arrive bientot tkt"
fi

if [ $l -eq 1 ]
then
	#sort -t';' -n -k1 -k2 $1 | head -n10 | LC_NUMERIC="C" awk -F';' -W sprintf=num '{sum += $5}END{print sum}'> temp1.csv
	
	#En une ligne : sort -t';' -n -k1 -k2 $1 | LC_NUMERIC="C" awk -F';' -W sprintf=num 'BEGIN {a=0; sum=0} {if(a!=$1){print sum ";" $6; a++; sum=0} else {sum+=$5}}' | sort -t';' -n -r -k1 | head -10
	
	sort -t';' -n -k1 -k2 $1 > temp1.csv
	LC_NUMERIC="C" awk -F';' -W sprintf=num 'BEGIN {a=0; sum=0} {if(a!=$1){print sum ";" a; a++; sum=0} else {sum+=$5}}' temp1.csv | sort -t';' -n -r -k1 > temp2.csv
	head -10 temp2.csv
	
	#sort -t';' -r  -n -k5 data.csv | head -n10 > 10long.csv
	#cat 10long.csv
fi


fin=$(date +%s)
duree=$(( $fin -$debut ))


##display script time
echo -e "$duree secondes"

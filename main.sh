#!/bin/bash

##count time
debut=$(date +%s)

#copy data.csv n move it to data's folder
script_dir=$(dirname "$(readlink -f "$0")")
cp "$script_dir/data.csv" "$script_dir/data/"

#with and height terminal
width=$(tput cols)
height=$(tput lines)

if [ $# -lt 2 ]
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
t=0

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
	#sort -t';' -d -k6 > temp/temp2.data
	grep ";1;" $1 | awk -F';' -W sprintf=num '{count[$6]++} END {for(i in count){printf("%s;%d\n", i, count[i])}}' | sort -t';' -n -r -k2,2 | head -10  > temp/tempd1.data
	
	gnuplot histd1.txt
	convert -rotate 90 images/d1.png images/d1.png
	
	xdg-open images/d1.png
fi

if [ $d2 -eq 1 ]
then
	LC_NUMERIC="C" awk -F';' -W sprintf=num '{count[$6]+=$5} END {for(i in count){printf("%s;%f\n", i, count[i])}}' $1 | sort -t';' -r -n -k2,2 | head -10  > temp/tempd2.data
	
	gnuplot histd2.txt
	convert -rotate 90 images/d2.png images/d2.png
	
	xdg-open images/d2.png
fi

if [ $l -eq 1 ]
then
	#sort -t';' -n -k1 -k2 $1 | head -n10 | LC_NUMERIC="C" awk -F';' -W sprintf=num '{sum += $5}END{print sum}'> temp1.csv
	
	LC_NUMERIC="C" awk -F';' -W sprintf=num '{count[$1]+=$5} END {for(i in count){printf("%d;%f\n", i, count[i])}}' $1 | sort -t';' -r -n -k2 | head -10 | sort -t' ' -r -n -k1,1 > temp/templ.data
	
	gnuplot hist.txt
	
	xdg-open images/l.pdf
	
	#sort -t';' -r  -n -k5 data.csv | head -n10 > 10long.csv
	#cat 10long.csv
fi


if [ $t -eq 1 ]
then
	#Un awk optimiser et c'est cool, count compte le nombre de fois ou la ville est la fin trajet et au millieu, count2 compte le nombre de fois ou c'est un début de trajet, donc on aditionne les 2 pour avoir le totale 
	awk -F';' -W sprintf=num '{count[$4]++; if($2 == 1){count2[$3]++}} END {for(i in count){printf("%s;%d;%d\n", i, count[i]+count2[i], count2[i])}}' $1 > temp/temps.data
	
	#Une ligne permettant de compter le nombre de ligne dans temp/temps.data pour permettre de faire la boucle for dans la programme c
	a=`cat temp/temps.data | wc -l`
	
	#des cuts pour séparer la colonne 1 et 2 dans des fichiers differents
	cut -d';' -f1 temp/temps.data > temp/temps2.data
	cut -d';' -f2 temp/temps.data > temp/temps3.data
	cut -d';' -f3 temp/temps.data > temp/temps4.data
	
	#compilation du programme c
	cd progc
	make
	cd ..
	
	#On lance le programme avec comme argument le nombre de ligne du fichier et les sorties du programme vont dans temp/tempsfini.data
	./progc/cy_truck $a | head -10 > temp/tempsfini.data
	
	gnuplot hist_t.txt
	
	xdg-open images/t.pdf
	
	#sort -t' ' -k1 -n -r temp/temps3.data > temp/temps3.data
fi


if [ $s -eq 1 ]
then
	cut -d';' -f1,5 $1 | tail -n +2 > temp/tempt.data
	
	#LC_NUMERIC="C" awk -F';' -W sprintf=num '{count[$1]+=$5; countmoy[$1]++; if($5 >= countmax[$1]){countmax[$1]=$5}; if(($5 <= countmin[$1]) || (countmin[$1] == 0)){countmin[$1]=$5}} END {for(i in count){printf("%d;%.3f;%.3f;%.3f;%.3f\n", i, countmin[i], count[i]/countmoy[i], countmax[i], countmax[i]-countmin[i])}}' $1 > temp/tempt.data
	
	
	a=`cat temp/tempt.data | wc -l`
	b=`cat $1 | grep ";1;" | awk -F';' '{if($1 >= max){max = $1}} END {print max}'`
	#b=`cat $1 | grep ";1;" | wc -l`
	
	cd progc
	make
	cd ..
	
	./progc/cy_truck $a $b | head -50 | awk -W sprintf=num '{x++; printf("%d;%s\n", x, $1)}' > temp/temptfini.data
	
	gnuplot hists.txt
	
	xdg-open images/s.pdf
fi


fin=$(date +%s)
duree=$(( $fin -$debut ))


##display script time
echo -e "$duree secondes"

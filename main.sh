#!/bin/bash

##count time & +%s.%N allow to display decimals
beginning=$(date +%s.%N)

#copy data.csv n move it to data's folder
script_dir=$(dirname "$(readlink -f "$0")")
cp "$script_dir/$1" "$script_dir/data/"

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

	fdBlack='\033[40m'
	fdRed='\033[41m'
	fdGreen='\033[42m'
	fdYellow='\033[43m'
	fdBlue='\033[44m'
	fdPink='\033[45m'
	fdCyan='\033[46m'
	fdGrey='\033[47m'
	# fdDefault='\033[49m'

	enBlack='\033[30m'
	enRed='\033[31m'
	enGreen='\033[32m'
	enYellow='\033[33m'
	enBleu='\033[34m'
	enPink='\033[35m'
	enCyan='\033[36m'
	enGrey='\033[37m'
	# enDefault='\033[39m'

	enBold='\033[1m'
	enUnderline='\033[4m'
	enBlinkers='\033[5m'
	enHighlight='\033[7m'
	enHidden='\033[8m'

	enDefault='\033[0m'

	# GENERALES
	nbre_radios=0
	nbre_page_radio=0

	la_pageRadio=1
	# sous_recherche=" "
	fichier_log=""

	header=""
	footer=""

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
	echo -e "${enBold}${enRed}Help Menu${enDefault}"
	n=$(echo "($width - 67)/2" | bc)
	create_space
	echo -e "${enBold}${enGreen}                    _________________________________________________"
    create_space 
    echo "            /|     |                                                 |"
    create_space 
    echo "            ||     |                                                 |"
    create_space 
    echo -e "       .----|-----,|                     ${enDefault}CY-TRUCK${enBold}${enGreen}                    |"
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
    echo -e "    '-'                '-'  '-'                       '-'  '-'${enDefault}"
    echo
	echo "-h | displays help menu"
	echo "-d1 | creates a graph with the 10 drivers who have made the most trips, sorted by descending order"
	echo "-d2 | creates a graph with the 10 drivers who traveled the longest distance, sorted by descending order"
	echo "-l | creates a graph with the 10 longest trips, sorted by ascending trip ID number"
	echo "-t | creates a graph the 10 most crossed cities, the first vertical bar is the total number of trips who pass through this city and the second vertical bar is the number of time where this city has been the departure city, sorted by alphabetical order"
	echo "-s | creates  a graph with the minimum, maximum, and average distance of the steps for 50 trips who have the biggest gap in the distance of their steps, sorted by descending order"
	echo -e "${enBold}Press [Enter] to continue${enBold}"
	read -p ""
fi

if [ $d1 -eq 1 ]
then
	#sort -t';' -d -k6 > temp/temp2.data
	grep ";1;" $1 | awk -F';' -W sprintf=num '{count[$6]++} END {for(i in count){printf("%s;%d\n", i, count[i])}}' | sort -t';' -n -r -k2,2 | head -10  > temp/tempd1.data
	
	gnuplot <<-EOF
	set terminal png font "Arial,9"
	set output 'demo/d1.png'
	set style data histogram
	set style fill solid 0.5
	set style histogram clustered
	set xtics rotate by -270
	set y2tics rotate by -270
	set bmargin 14
	set tmargin 5
	set datafile separator ";"

	unset ytics
	set y2tics nomirror
	set y2range [0:*]
	set y2label "Nb routes"
	set ylabel "Histogramme horizontal" rotate by -270
	set xlabel "Drivers Names" rotate by -180
	
	set size square
	set boxwidth 2 
	
	plot "temp/tempd1.data" using 2:xtic(1) axis x1y2 notitle lc rgb "blue"
	EOF
	
	convert -rotate 90 demo/d1.png demo/d1.png
	
	xdg-open demo/d1.png
fi

if [ $d2 -eq 1 ]
then
	LC_NUMERIC="C" awk -F';' -W sprintf=num '{count[$6]+=$5} END {for(i in count){printf("%s;%f\n", i, count[i])}}' $1 | sort -t';' -r -n -k2,2 | head -10  > temp/tempd2.data
	
	gnuplot <<-EOF
	set terminal png font "Arial,7.5"
	set output 'demo/d2.png'
	set style data histogram
	set style fill solid 0.5
	set style histogram clustered
	set xtics rotate by -270
	set y2tics rotate by -270
	set bmargin 14
	set tmargin 5
	set datafile separator ";"

	unset ytics
	set y2tics nomirror
	set y2range [0:*]
	set y2label "Distance (Km)"
	set ylabel "Histogramme horizontal" rotate by -270
	set xlabel "Drivers Names" rotate by -180
	
	set size square
	set boxwidth 2 
	
	plot "temp/tempd2.data" using 2:xtic(1) axis x1y2 notitle lc rgb "blue" 
	EOF
	convert -rotate 90 demo/d2.png demo/d2.png
	
	xdg-open demo/d2.png
fi

if [ $l -eq 1 ]
then
	#sort -t';' -n -k1 -k2 $1 | head -n10 | LC_NUMERIC="C" awk -F';' -W sprintf=num '{sum += $5}END{print sum}'> temp1.csv
	
	LC_NUMERIC="C" awk -F';' -W sprintf=num '{count[$1]+=$5} END {for(i in count){printf("%d;%f\n", i, count[i])}}' $1 | sort -t';' -r -n -k2 | head -10 | sort -t' ' -r -n -k1,1 > temp/templ.data
	
	gnuplot <<-EOF
	set terminal png font "Arial,6"
	set output "demo/l.png"
	set title "Histogramme"
	set style data histogram
	set style fill solid 0.5
	set style histogram clustered
	set datafile separator ";"
	
	set yrange [0:*]
	set ylabel "Distance (Km)" rotate by -270
	set xlabel "Route ID"
	
	set size square
	set boxwidth 2 
	
	plot "temp/templ.data" using 2:xtic(1) notitle lc rgb "blue"
	EOF
	
	xdg-open demo/l.png
	
	#sort -t';' -r  -n -k5 data.csv | head -n10 > 10long.csv
	#cat 10long.csv
fi


if [ $t -eq 1 ]
then
	#Un awk optimiser et c'est cool, count compte le nombre de fois ou la ville est la fin trajet et au millieu, count2 compte le nombre de fois ou c'est un début de trajet, donc on aditionne les 2 pour avoir le totale 
	awk -F';' '{
    if ($2 == 1) {
        count2[$3]++;
        if (!visited[$1, $3]){
        	count[$3]++;
        }
        visited[$1, $3]++;
    }
    if ($3 != $4 && !visited[$1, $4]) {
        count[$4]++;
        visited[$1, $4]++;
    }
} 
END {
    for (i in count) {
        printf("%s;%d;%d\n", i, count[i], count2[i]);
    }
}' $1 > temp/temps.data
	
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
	
	gnuplot <<-EOF
	set terminal png font "Arial,6" lw 0
	set output "demo/t.png"
	set title "Histogramme"
	set style data histogram
	set style fill solid 0.5
	set style histogram clustered
	set datafile separator ";"
	set bmargin 13
	
	set ylabel "Nb Routes" rotate by -270
	set xlabel "Town Names"
	set xtic rotate by 45 right
	
	set size square
	set boxwidth 2
	
	plot "temp/tempsfini.data" using 2:xtic(1) notitle lc rgb "blue", '' using 3:xtic(1) lc rgb "green" notitle
	EOF
	
	xdg-open demo/t.png
	
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
	
	gnuplot <<-EOF
	set terminal png font "Arial,6"
	set output "demo/s.png"
	set title "Histogramme"
	set style data lines
	set style fill solid 0.5
	set datafile separator ";"
	
	set xrange [1:*]
	set xtic rotate by 45 right
	set xlabel "Route ID"
	set ylabel "Distance (Km)" rotate by -270
	
	plot "temp/temptfini.data" using 1:3:5:xtic(2) with filledcurves below title "Distance Max/Min (Km)" lc rgb "blue", '' u 1:4 lc rgb "blue" title "Distance Average (Km)"
	EOF
	
	xdg-open demo/s.png
fi


end=$(date +%s.%N)
#ici awk permet d'ajuster le nombre de chiffres derrière la virgule pour l'affichage du temps
duration=$(echo "$end -$beginning" | bc )
##awk '{printf "%.2f", $1}'
cd temp/
rm -r *

##display script time
echo -e "$duration secondes"

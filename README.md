# Cy-Truck-MI6-groupe-B

Bienvenue sur notre projet CY-Truck qui permet la visulation d'un set de données d'une entreprise de transport de marchandises.

**Comment faire fonctionner le programme ?**

Après avoir téléchargé le dossier CY-Truck sur git-hub, il suffit d'écrire sur un terminal la commande : bash main.sh data.csv -cmd
Il faudra bien sûr remplacer cmd par le nom du traitement. Les différents différents supportés par ce programme :

* -d1 : Trie et affiche dans l'ordre décroisant les 10 chauffeurs avec le plus de trajets sur un histogramme horizontal

* -d2 : Trie et affiche dans l'ordre décroisant les 10 chauffeurs qui ont parcouru le plus de distance sur un histogramme horizontal

* -l : Trie et affiche dans l'ordre croissant les 10 plus longs trajets par numéro d'identifiant sur un histogramme vertical

* -t : Trie et affiche un histogramme vertical des 10 villes les plus parcourues dans l'ordre alphabétique. L'histogramme bleu affiche le nombre total de trajet qui traverse les 10 les plus parcourues. L'histogramme vert affiche le nombre de fois chaque ville à été une ville de départ.

* -s : Affiche un histogramme avec la distance minimale, maximale et moyenne des étapes pour les 50 trajets qui ont le plus grand écart dans la distance de leurs étapes, triés par ordre décroissant

Il est évidemment possible d'éxécuter plusieurs traitement tel que : bash main.sh data.csv -d1 -d2 -l

Vous pouvez également saisir la commande -h  qui explique les différents traitement en anglais.
Les résultats après excécution du programme seront dans "images", mais vous pouvez visualiser les histogrammes sans l'éxecution du programme nécesssaire dans le dossier "démo".

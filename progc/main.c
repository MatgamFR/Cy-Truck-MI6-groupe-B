#include "truck.h"

int main(int arg, char** argv){

	if(arg==2){
		//Va prendre les fichiers temp/temps2.data et temp/temps2.data en mode lecture et les stocker dans fichier et fichier2
		FILE * fichier = fopen("temp/temps2.data", "r");
		if(fichier == NULL){
			printf("the file temp/temps2.data cannot be opened");
			exit(01);
		}
		FILE * fichier2 = fopen("temp/temps3.data", "r");
		if(fichier2 == NULL){
			printf("the file temp/temps3.data cannot be opened");
			exit(02);
		}
		FILE * fichier3 = fopen("temp/temps4.data", "r");
		if(fichier3 == NULL){
			printf("the file temp/temps4.data cannot be opened");
			exit(03);
		}
		
		//Creation d'une chaine de caractere pour la ville et d'un int pour la distance
		char c[50];
		int d;
		int d2;
		
		//On recupere le nom de la ville et on l'a met dans c, de la meme façon pour la distance et d, le "%[^\n]\n" signifie qu'on prend tant qu'on tombe pas sur un \n
		fscanf(fichier, "%[^\n]\n", c);
		fscanf(fichier2, "%d", &d);
		fscanf(fichier3, "%d", &d2);
		
		//On cree une varible de type camion et on met les valeurs qu'on vient de récup dans cam.v et cam.v2, le strdup(c) signifie que c'est une copie de c, sinon ça va bug et prendre toujours la meme chaine de caractere (a cause des pointeurs tout ça)
		camion cam;
		cam.v = d;
		cam.v2 = d2;
		cam.v3 = strdup(c);
		
		//Creation avl avec cam en valeur
		pAvl a=creerArbre(cam);
		
		//Prend le nombre de ligne avec l'argument $a qu'on a donne dans main.sh, et on fait -1 car on deja mis le premier element
		int nbligne = atoi(argv[1])-1;
		
		//boucle for pour traverser toutes les lignes des fichiers
		for(int i=0; i<nbligne; i++){
			int h=0;
			
			//Meme chose que tout a l'heure
			fscanf(fichier, "%[^\n]\n", c);
			fscanf(fichier2, "%d", &d);
			fscanf(fichier3, "%d", &d2);
			
			//printf("%s\n", c);
			
			//Pareil
			camion cam;
			cam.v = d;
			cam.v2 = d2;
			cam.v3 = strdup(c);
			
			//printf("%d\n", i);
			
			//La on insert dans l'avl
			insertionAVL(a, cam, &h);
		}
		//On fait le parcours infixe mais inverse
		parcoursInfixeInverse(a);
	}
	else{
		traitement_s(atoi(argv[1]), atoi(argv[2]));
		
		/*FILE * fichier = fopen("temp/tempt.data", "r");
		
		int d;
		float f;
		float f2;
		float f3;
		float f4;
		
		fscanf(fichier, "%d;%f;%f;%f;%f", &d, &f, &f2, &f3, &f4);
		
		printf("%d %f\n", d, f);
		
		camion cam;
		
		cam.v7 = f4;
		cam.v2 = d;
		cam.v4 = f;
		cam.v5 = f2;
		cam.v6 = f3;
		
		pAvl a=creerArbre(cam);
		
		int nbligne = atoi(argv[1])-1;
		
		for(int i=0; i<nbligne; i++){
			int h=0;
			fscanf(fichier, "%d;%f;%f;%f;%f", &d, &f, &f2, &f3, &f4);
			//printf("%d %f\n", d, f);
			
			camion cam;
		
			cam.v7 = f4;
			cam.v2 = d;
			cam.v4 = f;
			cam.v5 = f2;
			cam.v6 = f3;
			
			insertionAVL2(a, cam, &h);
		}
		//On fait le parcours infixe mais inverse
		parcoursInfixeInverse2(a);*/
	}
	
	return 0;
}

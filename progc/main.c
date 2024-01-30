#include "truck.h"

//function to free the AVL allocation's memory
void freeAvl(pAvl a){
	if(a != NULL){
		freeAvl(a->fg);
		freeAvl(a->fd);
		//free(a->cam.v3);
		
		free(a);
	}
}

int main(int arg, char** argv){
	if(arg==2){
		//It's taking the temp/temps2.data and temp/temps3.data files n we r giving them the read mode, then we save them as  Fichier n Fichier2
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
		
		//Create a character string for the city n integer for the distance
		char c[50];
		int d;
		int d2;
		
		//We r saving the city's name to move it in c. The same thing for the distance and d. The symbol "%[^\n]\n" means we r taking as much information as we need while it didn't cross a \n
		fscanf(fichier, "%[^\n]\n", c);
		fscanf(fichier2, "%d", &d);
		fscanf(fichier3, "%d", &d2);
		
		//We r creating a variable called camion n we r moving the values we just got in cam.v n cam.v2. strdu(c) means it's a copy of the variable c, otherwise there will be error n it will always take the same character string (cause of pointers mainly)
		camion cam;
		cam.v = d;
		cam.v2 = d2;
		cam.v3 = strdup(c);
		
		//To create an AVL by using cam value for the avl's root
		pAvl a=creerArbre(cam);

		//It's taking the lines numbers with the $a argument that we got in main.sh. -1 cause we already got the 1st element
		int nbligne = atoi(argv[1])-1;

		//loop for to going through every singles lines of the different files
		for(int i=0; i<nbligne; i++){
			int h=0;
			
			//Same thing as before
			fscanf(fichier, "%[^\n]\n", c);
			fscanf(fichier2, "%d", &d);
			fscanf(fichier3, "%d", &d2);
			
			//printf("%s\n", c);
			
			//Asme thing
			camion cam;
			cam.v = d;
			cam.v2 = d2;
			cam.v3 = strdup(c);
			
			//printf("%d\n", i);
			
			//To insert element in the AVL
			a=insertionAVL(a, cam, &h);
		}
		//we r going through the tree by the reverse infix method
		camion tab[10];
		
		int p=0;
		parcoursInfixeInverse(a, &p, tab);
		
		pAvl b=creerArbre(tab[0]);
		
		for(int i=1; i<10; i++){
			int h = 0;
			b=insertionAVL3(b, tab[i], &h);
		}
		
		parcoursInfixe(b);
		//free the pointers' memory
		free(cam.v3);
		freeAvl(a);
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
		//we r going through the tree by the reverse infix method
		parcoursInfixeInverse2(a);*/
	}
	
	return 0;
}

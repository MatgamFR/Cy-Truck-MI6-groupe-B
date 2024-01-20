#include "truck.h"

void traitement_s(int nbligne, int a){
	FILE * fichier = fopen("temp/tempt.data", "r");
	//FILE * fichier2 = fopen("temp/tempt2.data", "w+");
	//Securite fopen
	if(fichier == NULL){
		printf("the file temp/tempt.data cannot be opened\n");
		exit(1);
	}
	int d;
	float f;
	
	truc * tab = malloc(sizeof(truc)*a);
	//Securite malloc
	if(tab == NULL){
	 	printf("Error of memory allocation\n");
	 	exit(2);
	 }
	for(int i=0; i<a; i++){
		truc t;
		t.max = 0;
		t.moy = 0;
		t.min = 0;
		t.compt = 0;
		tab[i] = t;
	}
	
	for(int i=0; i<nbligne; i++){
		fscanf(fichier, "%d;%f", &d, &f);
		
		if(f >= (tab[d-1]).max){
			(tab[d-1]).max = f;
		}
		if(f <= (tab[d-1]).min || (tab[d-1]).min == 0){
			(tab[d-1]).min = f;
		}
		((tab[d-1]).moy)+=f;
		((tab[d-1]).compt)++;
	}
	
	camion cam;
	
	cam.v7 = (tab[0]).max - (tab[0]).min;
	cam.v2 = 1;
	cam.v4 = (tab[0]).min;
	cam.v5 = (tab[0]).moy / (tab[0]).compt;
	cam.v6 = (tab[0]).max;
	
	pAvl ab=creerArbre(cam);
	
	for(int i=1; i<a; i++){
		int h=0;
	
		camion cam;
		
		cam.v7 = (tab[i]).max - (tab[i]).min;
		cam.v2 = i+1;
		cam.v4 = (tab[i]).min;
		cam.v5 = (tab[i]).moy / (tab[i]).compt;
		cam.v6 = (tab[i]).max;
		
		ab=insertionAVL2(ab, cam, &h);
	
		//fprintf(fichier2, "%d;%.3f;%.3f;%.3f,%.3f\n", i+1, (tab[i]).min, (tab[i]).moy / (tab[i]).compt, (tab[i]).max, (tab[i]).max - (tab[i]).min);
	}
	
	parcoursInfixeInverse2(ab);
	
	fclose(fichier);
	//fclose(fichier2);
}

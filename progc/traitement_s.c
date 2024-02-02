#include "truck.h"

void traitement_s(int nbline, int a){
	FILE * file = fopen("temp/temps.data", "r");
	
	int d;
	float f;
	
	//Creating a dynamic table
	town * tab = malloc(sizeof(town)*a);
	
	//Fill the table with town struct with all element 0
	for(int i=0; i<a; i++){
		town t;
		t.max = 0;
		t.moy = 0;
		t.min = 0;
		t.compt = 0;
		tab[i] = t;
	}
	
	//loop for to going through every singles lines of the different files
	for(int i=0; i<nbline; i++){
		fscanf(file, "%d;%f", &d, &f);
		
		if(f >= (tab[d-1]).max){
			(tab[d-1]).max = f;
		}
		if(f <= (tab[d-1]).min || (tab[d-1]).min == 0){
			(tab[d-1]).min = f;
		}
		((tab[d-1]).moy)+=f;
		((tab[d-1]).compt)++;
	}
	
	//Insert into cam the value
	truck cam;
	
	cam.v7 = (tab[0]).max - (tab[0]).min;
	cam.v2 = 1;
	cam.v4 = (tab[0]).min;
	cam.v5 = (tab[0]).moy / (tab[0]).compt;
	cam.v6 = (tab[0]).max;
	
	pAvl ab=createAVL(cam);
	
	//loop which will insert all the cams into the tree
	for(int i=1; i<a; i++){
		int h=0;
	
		truck cam;
		
		cam.v7 = (tab[i]).max - (tab[i]).min;
		cam.v2 = i+1;
		cam.v4 = (tab[i]).min;
		cam.v5 = (tab[i]).moy / (tab[i]).compt;
		cam.v6 = (tab[i]).max;
		
		insertionAVL2(ab, cam, &h);
	}
	
	//we are going through the tree by the reverse infix method
	InfixeReverse2(ab);
	
	fclose(file);
	//fclose(file2);
}

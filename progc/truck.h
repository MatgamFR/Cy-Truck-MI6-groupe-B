#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

typedef struct Camion{
	int v;
	int v2;
	char * v3;
	float v4;
	float v5;
	float v6;
	float v7;
} camion;

typedef struct Avl{
    camion val;
    int equilibre;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;

typedef struct Truc{
	float max;
	float min;
	float moy;
	int compt;
} truc;

pAvl creerArbre(camion num);
pAvl rotationGauche(pAvl myAvl);
pAvl rotationDroite(pAvl myAvl);
pAvl doubleRotationGauche(pAvl myAvl);
pAvl doubleRotationDroite(pAvl myAvl);
pAvl equilibrerAVL(pAvl myAvl);
pAvl insertionAVL(pAvl myAvl, camion e, int* h);
void parcoursInfixeInverse(pAvl a, int* compt, camion tab[]);

pAvl insertionAVL2(pAvl myAvl, camion e, int* h);
void parcoursInfixeInverse2(pAvl a);

pAvl insertionAVL3(pAvl myAvl, camion e, int* h);
void parcoursInfixeInverse3(pAvl a);

void traitement_s(int nbligne, int a);

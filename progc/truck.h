#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

typedef struct Camion{
	int v;
	int v2;
	char * v3;
} camion;

typedef struct Avl{
    camion val;
    int equilibre;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;

pAvl creerArbre(camion num);
pAvl rotationGauche(pAvl myAvl);
pAvl rotationDroite(pAvl myAvl);
pAvl doubleRotationGauche(pAvl myAvl);
pAvl doubleRotationDroite(pAvl myAvl);
pAvl equilibrerAVL(pAvl myAvl);
pAvl insertionAVL(pAvl myAvl, camion e, int* h);
void parcoursInfixeInverse(pAvl a);
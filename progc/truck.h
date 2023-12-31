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

typedef struct Camion2{
	float v;
	float v3;
	float v4;
	float v5;
	int v2;
} camion2;

typedef struct Avl{
    camion val;
    int equilibre;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;

typedef struct Avl2{
    camion2 val;
    int equilibre;
    struct Avl2* fg;
    struct Avl2* fd;
}Avl2,*pAvl2;

pAvl creerArbre(camion num);
pAvl rotationGauche(pAvl myAvl);
pAvl rotationDroite(pAvl myAvl);
pAvl doubleRotationGauche(pAvl myAvl);
pAvl doubleRotationDroite(pAvl myAvl);
pAvl equilibrerAVL(pAvl myAvl);
pAvl insertionAVL(pAvl myAvl, camion e, int* h);
void parcoursInfixeInverse(pAvl a);

pAvl2 creerArbre2(camion2 num);
pAvl2 rotationGauche2(pAvl2 myAvl);
pAvl2 rotationDroite2(pAvl2 myAvl);
pAvl2 doubleRotationGauche2(pAvl2 myAvl);
pAvl2 doubleRotationDroite2(pAvl2 myAvl);
pAvl2 equilibrerAVL2(pAvl2 myAvl);
pAvl2 insertionAVL2(pAvl2 myAvl, camion2 e, int* h);
void parcoursInfixeInverse2(pAvl2 a);

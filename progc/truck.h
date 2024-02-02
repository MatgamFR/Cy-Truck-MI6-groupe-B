#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

typedef struct Truck{
	int v;
	int v2;
	char * v3;
	float v4;
	float v5;
	float v6;
	float v7;
} truck;

typedef struct Avl{
    truck val;
    int balance;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;

typedef struct Town{
	float max;
	float min;
	float moy;
	int compt;
} town;

pAvl createAVL(truck num);
pAvl rotationLeft(pAvl myAvl);
pAvl rotationRight(pAvl myAvl);
pAvl doubleRotationLeft(pAvl myAvl);
pAvl doubleRotationRight(pAvl myAvl);
pAvl balanceAVL(pAvl myAvl);
pAvl insertionAVL(pAvl myAvl, truck e, int* h);
void InfixeReverse(pAvl a, int* compt, truck tab[]);

pAvl insertionAVL2(pAvl myAvl, truck e, int* h);
void InfixeReverse2(pAvl a);

pAvl insertionAVL3(pAvl myAvl, truck e, int* h);
void Infixe(pAvl a);

void traitement_s(int nbligne, int a);

int compareString(char *string1, char *string2);

void freeAvl(pAvl a);

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


pAvl creerArbre(camion num){
    pAvl monAvl=(pAvl)malloc(sizeof(Avl));

    if(monAvl==NULL){
        printf("Error of memory Allocation\n");
        exit(1);
    }

    monAvl->val=num;
    monAvl->equilibre=0;
    monAvl->fg=NULL;
    monAvl->fd=NULL;

    return monAvl;
}


pAvl rotationGauche(pAvl myAvl){

    pAvl bivot;
    int eqA,eqB;

    bivot=myAvl->fd;
    myAvl->fd=bivot->fg;
    bivot->fg=myAvl;

    eqA=myAvl->equilibre;
    eqB=bivot->equilibre;

    myAvl->equilibre=eqA-max(eqB,0)-1;
    bivot->equilibre= min(eqA-2,min(eqA+eqB-2,eqB-1));

    myAvl=bivot;

    return myAvl;
}

pAvl rotationDroite(pAvl myAvl){

    pAvl bivot;
    int eqA,eqB;

    bivot=myAvl->fg;
    myAvl->fg=bivot->fd;
    bivot->fd=myAvl;

    eqA=myAvl->equilibre;
    eqB=bivot->equilibre;

    myAvl->equilibre=eqA-min(eqB,0)+1;
    bivot->equilibre= max(eqA+2,max(eqA+eqB+2,eqB+1));

    myAvl=bivot;

    return myAvl;
}


pAvl doubleRotationGauche(pAvl myAvl){
    pAvl bivot;
    myAvl->fd=rotationDroite(myAvl->fd);
    
    return rotationGauche(myAvl);
}

pAvl doubleRotationDroite(pAvl myAvl){
    pAvl bivot;
    myAvl->fg=rotationGauche(myAvl->fg);
    
    return rotationDroite(myAvl);
}


pAvl equilibrerAVL(pAvl myAvl){
    if(myAvl->equilibre >=2 ){
        if(myAvl->fd->equilibre >= 0){
            return rotationGauche(myAvl);
        }
        else{
            return doubleRotationGauche(myAvl);
        }
    }
    else if(myAvl->equilibre <= -2){
        if(myAvl->fg->equilibre <=0){
            return rotationDroite(myAvl);
        }
        else{
            return doubleRotationDroite(myAvl);
        }
    }
    return myAvl;
}


pAvl insertionAVL(pAvl myAvl, camion e, int* h){
	if(myAvl == NULL){
		*h=1;
		return creerArbre(e);
	}
	else if(e.v < (myAvl->val).v){
		myAvl->fg = insertionAVL(myAvl->fg, e, h);
		*h = -*h;
	}
	else if(e.v >= (myAvl->val).v){
		myAvl->fd = insertionAVL(myAvl->fd, e, h);
	}
	else{
		*h = 0;
		return myAvl;
	}
	if(*h != 0){
		myAvl->equilibre += *h;
		myAvl = equilibrerAVL(myAvl);
		if(myAvl->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}


pAvl suppMinAVL(pAvl myAvl, int* h, camion* pe){
	if(myAvl->fg == NULL){
		*pe = myAvl->val;
		*h = -1;
		pAvl tmp = myAvl;
		myAvl = myAvl->fd;
		free(tmp);
		return myAvl;
	}
	else{
		myAvl->fg = suppMinAVL(myAvl->fg, h, pe);
		*h = -*h;
	}
	if(*h != 0){
		myAvl->equilibre += *h;
		myAvl = equilibrerAVL(myAvl);
		if(myAvl->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}


pAvl suppressionAVL(pAvl myAvl, camion e, int* h){
	if(myAvl == NULL){
		*h=1;
		return myAvl;
	}
	else if(e.v > (myAvl->val).v){
		myAvl->fd = suppressionAVL(myAvl->fd, e, h);
	}
	else if(e.v < (myAvl->val).v){
		myAvl->fg = suppressionAVL(myAvl->fg, e, h);
		*h = -*h;
	}
	else if(myAvl->fd != NULL){
		myAvl->fg = suppMinAVL(myAvl->fd, h, &(myAvl->val));
	}
	else{
		pAvl tmp = myAvl;
		myAvl = myAvl->fg;
		free(tmp);
		*h = -1;
	}
	if(myAvl == NULL){
		*h = 0;
	}
	if(*h != 0){
		myAvl->equilibre += *h;
		myAvl = equilibrerAVL(myAvl);
		if(myAvl->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}


void parcoursInfixeInverse(pAvl a){
	if(a!=NULL){
		parcoursInfixeInverse(a->fd);
		//La ça va print nom_de_la_ville;distance
		printf("%s;%d;%d\n", (a->val).v3, (a->val).v, (a->val).v2);
		parcoursInfixeInverse(a->fg);
	}
}


int main(int arg, char** argv){
	//Va prendre les fichiers temp/temps2.data et temp/temps2.data en mode lecture et les stocker dans fichier et fichier2
	FILE * fichier = fopen("temp/temps2.data", "r");
	FILE * fichier2 = fopen("temp/temps3.data", "r");
	FILE * fichier3 = fopen("temp/temps4.data", "r");
	
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
	
	//Y'a 2 problemes, c'est que ça n'affiche pas toutes les villes/distances et que ça ne prend pas en compte quand 2 distances ont les memes valeurs. Bonne chance pour regler ces bugs
	
	return 0;
}

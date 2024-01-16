#include "truck.h"

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


void parcoursInfixeInverse(pAvl a, int* compt, camion tab[]){
	if(a!=NULL && *compt < 10){
		parcoursInfixeInverse(a->fd, compt, tab);
		if(*compt < 10){
			int b = *compt;
			tab[b] = a->val;
			(*compt)++;
		}
		parcoursInfixeInverse(a->fg, compt, tab);
	}
}


pAvl insertionAVL3(pAvl myAvl, camion e, int* h){
	
	
	if(myAvl == NULL){
		*h=1;
		return creerArbre(e);
	}
	else{
		int comparison = strcmp(e.v3, (myAvl->val).v3);
		if(comparison < 0){
		
			myAvl->fg = insertionAVL3(myAvl->fg, e, h);
			*h = -*h;
		}
		else if(comparison >= 0){
			myAvl->fd = insertionAVL3(myAvl->fd, e, h);
		}
		else{
			*h = 0;
			return myAvl;
		}
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

void parcoursInfixe(pAvl a){
	if(a!=NULL){
		parcoursInfixe(a->fg);
		//La ça va print nom_de_la_ville;distance
		printf("%s;%d;%d\n", (a->val).v3, (a->val).v, (a->val).v2);
		parcoursInfixe(a->fd);
	}
}

void parcoursInfixeInverse2(pAvl a){
	if(a!=NULL){
		parcoursInfixeInverse2(a->fd);
		printf("%d;%.3f;%.3f;%.3f,%.3f\n", (a->val).v2, (a->val).v4, (a->val).v5, (a->val).v6, (a->val).v7);
		parcoursInfixeInverse2(a->fg);
	}
}

pAvl insertionAVL2(pAvl myAvl, camion e, int* h){
	if(myAvl == NULL){
		*h=1;
		return creerArbre(e);
	}
	else if(e.v7 < (myAvl->val).v7){
		myAvl->fg = insertionAVL2(myAvl->fg, e, h);
		*h = -*h;
	}
	else if(e.v7 >= (myAvl->val).v7){
		myAvl->fd = insertionAVL2(myAvl->fd, e, h);
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

#include "truck.h"

pAvl createAVL(truck num){
    pAvl myAvl=(pAvl)malloc(sizeof(Avl));

    if(myAvl==NULL){
        printf("Error of memory Allocation\n");
        exit(1);
    }

    myAvl->val=num;
    myAvl->balance=0;
    myAvl->fg=NULL;
    myAvl->fd=NULL;

    return myAvl;
}


pAvl rotationLeft(pAvl myAvl){

    pAvl bivot;
    int eqA,eqB;

    bivot=myAvl->fd;
    myAvl->fd=bivot->fg;
    bivot->fg=myAvl;

    eqA=myAvl->balance;
    eqB=bivot->balance;

    myAvl->balance=eqA-max(eqB,0)-1;
    bivot->balance= min(eqA-2,min(eqA+eqB-2,eqB-1));

    myAvl=bivot;

    return myAvl;
}

pAvl rotationRight(pAvl myAvl){

    pAvl bivot;
    int eqA,eqB;

    bivot=myAvl->fg;
    myAvl->fg=bivot->fd;
    bivot->fd=myAvl;

    eqA=myAvl->balance;
    eqB=bivot->balance;

    myAvl->balance=eqA-min(eqB,0)+1;
    bivot->balance= max(eqA+2,max(eqA+eqB+2,eqB+1));

    myAvl=bivot;

    return myAvl;
}


pAvl doubleRotationLeft(pAvl myAvl){
    pAvl bivot;
    myAvl->fd=rotationRight(myAvl->fd);
    
    return rotationLeft(myAvl);
}

pAvl doubleRotationRight(pAvl myAvl){
    pAvl bivot;
    myAvl->fg=rotationLeft(myAvl->fg);
    
    return rotationRight(myAvl);
}


pAvl balanceAVL(pAvl myAvl){
    if(myAvl->balance >=2 ){
        if(myAvl->fd->balance >= 0){
            return rotationLeft(myAvl);
        }
        else{
            return doubleRotationLeft(myAvl);
        }
    }
    else if(myAvl->balance <= -2){
        if(myAvl->fg->balance <=0){
            return rotationRight(myAvl);
        }
        else{
            return doubleRotationRight(myAvl);
        }
    }
    return myAvl;
}


pAvl insertionAVL(pAvl myAvl, truck e, int* h){
	if(myAvl == NULL){
		*h=1;
		return createAVL(e);
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
		myAvl->balance += *h;
		myAvl = balanceAVL(myAvl);
		if(myAvl->balance == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}


int compareString(char *chaine1, char *chaine2){
    while (*chaine1 != '\0' || *chaine2 != '\0'){
        // Si l'un des caractères est ' ', on le traite comme le plus grand
        char c1 = (*chaine1 == ' ') ? 127 : *chaine1;
        char c2 = (*chaine2 == ' ') ? 127 : *chaine2;

        if (c1 < c2) {
            return -1; // Chaine1 est devant
        } else if (c1 > c2) {
            return 1; // Chaine2 est devant
        }

        // Passer au caractère suivant dans les deux chaînes
        chaine1++;
        chaine2++;
    }
    
     // Les chaînes sont identiques jusqu'à présent, mais une peut être plus courte
    if (*chaine1 == '\0' && *chaine2 != '\0') {
        return -1; // Chaine1 est devant
    } else if (*chaine1 != '\0' && *chaine2 == '\0') {
        return 1; // Chaine2 est devant
    }

    // Les chaînes sont identiques
    return 0;
}


void InfixeReverse(pAvl a, int* compt, truck tab[]){
	if(a!=NULL && *compt < 10){
		InfixeReverse(a->fd, compt, tab);
		if(*compt < 10){
			int b = *compt;
			tab[b] = a->val;
			(*compt)++;
		}
		InfixeReverse(a->fg, compt, tab);
	}
}


pAvl insertionAVL3(pAvl myAvl, truck e, int* h){
	if(myAvl == NULL){
		*h=1;
		return createAVL(e);
	}
	else{
		int comparison = compareString(e.v3, (myAvl->val).v3);
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
		myAvl->balance += *h;
		myAvl = balanceAVL(myAvl);
		if(myAvl->balance == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}

void Infixe(pAvl a){
	if(a!=NULL){
		Infixe(a->fg);
		//La ça va print nom_de_la_ville;distance
		printf("%s;%d;%d\n", (a->val).v3, (a->val).v, (a->val).v2);
		Infixe(a->fd);
	}
}

void InfixeReverse2(pAvl a){
	if(a!=NULL){
		InfixeReverse2(a->fd);
		printf("%d;%.3f;%.3f;%.3f,%.3f\n", (a->val).v2, (a->val).v4, (a->val).v5, (a->val).v6, (a->val).v7);
		InfixeReverse2(a->fg);
	}
}

pAvl insertionAVL2(pAvl myAvl, truck e, int* h){
	if(myAvl == NULL){
		*h=1;
		return createAVL(e);
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
		myAvl->balance += *h;
		myAvl = balanceAVL(myAvl);
		if(myAvl->balance == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}


//function to free the AVL allocation's memory
void freeAvl(pAvl a){
	if(a != NULL){
		freeAvl(a->fg);
		freeAvl(a->fd);
		//free(a->cam.v3);
		
		free(a);
	}
}

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


void parcoursInfixeInverse(pAvl a){
	if(a!=NULL){
		parcoursInfixeInverse(a->fd);
		//La ça va print nom_de_la_ville;distance
		printf("%s;%d;%d\n", (a->val).v3, (a->val).v, (a->val).v2);
		parcoursInfixeInverse(a->fg);
	}
}


pAvl2 creerArbre2(camion2 num){
    pAvl2 monAvl=(pAvl2)malloc(sizeof(Avl2));

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


pAvl2 rotationGauche2(pAvl2 myAvl){

    pAvl2 bivot;
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

pAvl2 rotationDroite2(pAvl2 myAvl){

    pAvl2 bivot;
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


pAvl2 doubleRotationGauche2(pAvl2 myAvl){
    pAvl2 bivot;
    myAvl->fd=rotationDroite2(myAvl->fd);
    
    return rotationGauche2(myAvl);
}

pAvl2 doubleRotationDroite2(pAvl2 myAvl){
    pAvl2 bivot;
    myAvl->fg=rotationGauche2(myAvl->fg);
    
    return rotationDroite2(myAvl);
}


pAvl2 equilibrerAVL2(pAvl2 myAvl){
    if(myAvl->equilibre >=2 ){
        if(myAvl->fd->equilibre >= 0){
            return rotationGauche2(myAvl);
        }
        else{
            return doubleRotationGauche2(myAvl);
        }
    }
    else if(myAvl->equilibre <= -2){
        if(myAvl->fg->equilibre <=0){
            return rotationDroite2(myAvl);
        }
        else{
            return doubleRotationDroite2(myAvl);
        }
    }
    return myAvl;
}


pAvl2 insertionAVL2(pAvl2 myAvl, camion2 e, int* h){
	if(myAvl == NULL){
		*h=1;
		return creerArbre2(e);
	}
	else if(e.v < (myAvl->val).v){
		myAvl->fg = insertionAVL2(myAvl->fg, e, h);
		*h = -*h;
	}
	else if(e.v >= (myAvl->val).v){
		myAvl->fd = insertionAVL2(myAvl->fd, e, h);
	}
	else{
		*h = 0;
		return myAvl;
	}
	if(*h != 0){
		myAvl->equilibre += *h;
		myAvl = equilibrerAVL2(myAvl);
		if(myAvl->equilibre == 0){
			*h = 0;
		}
		else{
			*h = 1;
		}
	}
	return myAvl;
}

void parcoursInfixeInverse2(pAvl2 a){
	if(a!=NULL){
		parcoursInfixeInverse2(a->fd);
		printf("%d;%.3f;%.3f;%.3f,%.3f\n", (a->val).v2, (a->val).v3, (a->val).v4, (a->val).v5, (a->val).v);
		parcoursInfixeInverse2(a->fg);
	}
}

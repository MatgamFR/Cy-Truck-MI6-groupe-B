#include <stdio.h>
#include <stdlib.h>
#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))


typedef struct Avl{
    int val;
    int equilibre;
    struct Avl* fg;
    struct Avl* fd;
}Avl,*pAvl;


pAvl creerArbre(int num){
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


pAvl insertionAVL(pAvl myAvl, int e, int* h){
	if(myAvl == NULL){
		*h=1;
		return creerArbre(e);
	}
	else if(e < myAvl->val){
		myAvl->fg = insertionAVL(myAvl->fg, e, h);
		*h = -*h;
	}
	else if(e > myAvl->val){
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


pAvl suppMinAVL(pAvl myAvl, int* h, int* pe){
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


pAvl suppressionAVL(pAvl myAvl, int e, int* h){
	if(myAvl == NULL){
		*h=1;
		return myAvl;
	}
	else if(e > myAvl->val){
		myAvl->fd = suppressionAVL(myAvl->fd, e, h);
	}
	else if(e < myAvl->val){
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

int main(){
	
	return 0;
}

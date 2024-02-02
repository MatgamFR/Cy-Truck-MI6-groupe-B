#include "truck.h"

//Function to create an avl
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

//Function to do a rotation left
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

//Function to do a rotation right
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

//Function to do a double rotation left
pAvl doubleRotationLeft(pAvl myAvl){
    pAvl bivot;
    myAvl->fd=rotationRight(myAvl->fd);
    
    return rotationLeft(myAvl);
}

//Function to do a double rotation right
pAvl doubleRotationRight(pAvl myAvl){
    pAvl bivot;
    myAvl->fg=rotationLeft(myAvl->fg);
    
    return rotationRight(myAvl);
}

//function to balance the AVL
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

//Function to insert into the AVL
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

//Function to compare 2 string, return 1 if c1 > c2 and -1 if c1 < c2
int compareString(char *string1, char *string2){
    while (*chaine1 != '\0' || *chaine2 != '\0'){
        //If one of the characters is ' ', it is treated as the largest one
        char c1 = (*string1 == ' ') ? 127 : *string1;
        char c2 = (*string2 == ' ') ? 127 : *string2;

        if (c1 < c2) {
            return -1; //string1 is ahead
        } else if (c1 > c2) {
            return 1; //string2 is ahead
        }

        //Pass to the next character in both strings
        string1++;
        string2++;
    }
    
     //Chains are identical up to now, but one may be shorter
    if (*string1 == '\0' && *string2 != '\0') {
        return -1; //string1 is ahead
    } else if (*string1 != '\0' && *string2 == '\0') {
        return 1; //string2 is ahead
    }

    //Strings are identical
    return 0;
}

//Function for reversed infix path
void InfixeReverse(pAvl a, int* compt, truck tab[]){
	//End when compt is == 10
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

//Function to insert into the AVL
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

//Function for infix path
void Infixe(pAvl a){
	if(a!=NULL){
		Infixe(a->fg);
		printf("%s;%d;%d\n", (a->val).v3, (a->val).v, (a->val).v2);
		Infixe(a->fd);
	}
}


//Function for reversed infix path
void InfixeReverse2(pAvl a){
	if(a!=NULL){
		InfixeReverse2(a->fd);
		printf("%d;%.3f;%.3f;%.3f,%.3f\n", (a->val).v2, (a->val).v4, (a->val).v5, (a->val).v6, (a->val).v7);
		InfixeReverse2(a->fg);
	}
}

//Function to insert into the AVL
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

/**
 * \file variable.c
 * \brief Définitions des fonctions sur les variables.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variable.h"

#include "matrix.h"

 

Variable adjVariable(const char *n, E vF, Matrix vM, Variable v){
	Variable ret = (Variable) malloc(sizeof(struct variable));
	ret->nom = malloc(strlen(n)+1);
	ret->nom = strcpy(ret->nom, n);	
	ret->valM = vM;
	ret->valF = vF;
	ret->suiv = v;
	return ret;
}


void freeVariable(Variable v){
	if(v != NULL){
		freeVariable(v->suiv);
		free(v->nom);
		if(v->valM != NULL)
			deleteMatrix(v->valM);
		free(v);
	}
}


int existeDeja(const char *n, Variable v){
	if(v==NULL){
		return 0;
	}
	
	Variable tmp = v;
	while(tmp != NULL){
		if(strcmp(tmp->nom, n) == 0){
			return 1;
		}
		tmp = tmp->suiv;
	}
	return 0;
}

Variable delVariable(const char *n, Variable v){
	if(!existeDeja(n, v)){
		return v;
	}
	if(v == NULL){
		return NULL;
	}
	
	Variable tmp = v;
	if(strcmp(tmp->nom, n) == 0){ //on delete l'unique element de la liste
		tmp = tmp->suiv;
		free(v->nom);
		if(v->valM != NULL)
			deleteMatrix(v->valM);
		free(v);
		return(tmp);
	}
	while(strcmp(tmp->suiv->nom, n) != 0){
		tmp = tmp->suiv;
	}
	
	Variable tmp2 = tmp->suiv;
	tmp->suiv = tmp->suiv->suiv;
	free(tmp2->nom);
	if(tmp2->valM != NULL)
		deleteMatrix(tmp2->valM);
	free(tmp2);
	return v;
}



Matrix trouverMat(const char* n, Variable v){
	if(v == NULL){
		return NULL;
	}
	
	Variable tmp = v;
	while(tmp != NULL){
		if(strcmp(tmp->nom, n) == 0){
			return tmp->valM;
		}
		tmp = tmp->suiv;
	}
	
	return NULL;
}

E trouverFloat(const char *n, Variable v){
	if(v == NULL){
		return NaN;
	}
	
	Variable tmp = v;
	while(tmp != NULL){
		if(strcmp(tmp->nom, n) == 0){
			return tmp->valF;
		}
		tmp = tmp->suiv;
	}
	
	return NaN;

}



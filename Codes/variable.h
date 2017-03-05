/**
 * \file variable.h
 * \brief Définition du type Variable afin d'associer une valeur à un 
 * nom de variable, et déclarations des fonctions sur les variables.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
 
#ifndef __VARIABLE_H_
#define __VARIABLE_H_

#include "matrix.h"


/**
 * \struct variable
 * \brief Structure permettant d'associer une valeur à un nom de variable. C'est une chaîne. A chaque adjonction, une ajoute un objet "Variable" dans la chaîne
 */
typedef struct variable{
		    char* nom; 		// Le nom de la variable
		    E valF; 		// Valeur (float) si le type est 'f'. Vaux NULL sinon
		    Matrix valM; 	// Objet de type Matrix si le type est 'm'. Vaux NULL sinon    
		    struct variable *suiv; // variable suivante
} Svariable, *Variable;




Variable adjVariable(const char *n, E vF, Matrix vM, Variable v);
void freeVariable(Variable v);
int existeDeja(const char *n, Variable v);
Variable delVariable(const char *n, Variable v);

Matrix trouverMat(const char *n, Variable v);
E trouverFloat(const char *n, Variable v);


#endif

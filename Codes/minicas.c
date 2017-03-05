/**
 * \file minicas.c
 * \brief Code source pour l'exécutable minicas.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "variable.h"
#include "matrix.h"
#include "operations.h"
#include "speedtest.h"

#define TAILLE_MAX_INSTR 256
#define MAX_NOM 128

char *help = \
"Declarations :\n\
- [var] : [float]\n\
- [var] : matrix([values])\n\
Les instructions suivante peuvent être précédées de '[var] :' pour affecter le résultat à une variable :\n\
- addition([matrix1],[matrix2])\n\
- sub([matrix1],[matrix2])\n\
- mult([matrix1],[matrix2])\n\
- mult_scal([float], [matrix]) OU mult_scal([matrix], [float])\n\
- expo([matrix], [int]) OU expo([int], [matrix])\n\
- transpose([matrix])\n\
- determinant([matrix])\n\
- invert([matrix])\n\
- solve([matrix1], [matrix2])\n\
- rank([matrix])\n\
- least_estimate([matrix])\n\
- eigen_values([matrix])\n\
- speedtest [operation] [taille_min] [taille_max] [pas] ([nb_sec])\n\
- quit\n\
";


/** Fonction utilisée pour séparer une chaine de caractère en fonction de séparateurs
  * Cette fonction est utilisée pour séparer les éléments du getline()*/
char **separe( char *chaine, const char *separateurs )
{
	char **tab;
	int i, s, m, size=10;
	
	tab = malloc( size * sizeof(char*) );
	m = 0;
	i = 0;
	while( chaine[i] != 0 )
	{
		// saute un séparateur
		for( s=0 ; separateurs[s]!=0 ; s++ )
			if( chaine[i] == separateurs[s] )
				break;
		if( separateurs[s]!=0 )
		{
			chaine[i++] = 0;	// met un fin de chaine à la place du séparateur et avance
			continue;	// les séparateurs n'ont pas été épuisés
		}

		if( chaine[i] != 0 ){
			tab[m++] = chaine+i;
			tab[m-1][strlen(chaine+i)] = '\0';
		}
		if( m == size )
		{
			// si limite de la taille de mon tableau, je l'agrandis.
			size += 10;
			tab = realloc( tab, size * sizeof(char*) );
		}
		// saute les caractères non séparateurs
		for( ; chaine[i]!=0 ; i++ )
		{
			for( s=0 ; separateurs[s]!=0 ; s++ )
				if( chaine[i] == separateurs[s] )
					
					break;
			if( separateurs[s]!=0 )
				break;	// trouvé un caractère séparateur, j'arrête d'avancer et je passe au mot suivant
		}
	}
	tab[m] = NULL;
	return( tab );
}


/** Fonction permettant de compter le nombre de mots dans un char**
  * Cette fonction est utilisée pour connaitre le nombre de mots qu'a entré l'utilisateur*/
int cptArgs(char **tabl){
	int i = 0;
	while(tabl[i]!= NULL){
		i++;
	}
	return i;
}


/** Fonction permettant de connaitre la taille (sans le \0) d'une chaine de caractère */
int my_strlen(char* tabl){
	int i = 0;
	while(tabl[i] != '\0'){
		i++;
	}	
	return i;
}



/** Fonction premettant de savoir si une chaine de caractère représente un nombre */

int isNumber(char* tabl){
	int i = 0;
	int nbPoints = 0;
	for(i=0;i< my_strlen(tabl); i++){
		if(tabl[i] == '.'){
			nbPoints++;
			continue;
		}
		if(tabl[i] < '0' || tabl[i] > '9'){
			return 0;
		}
	}
	
	return(nbPoints <=1);
}


/** Fonction permettant de compter le nombre d'occurence d'un caractère dans un char**
  * Cette fonction est utilisée pour connaitre la taille de la matrice à créer*/
int nb_occur(char ** tabl, char c, int from, int taille){
	int i = 0;
	int res = 0;
	while(i<taille){
		if(tabl[from][i] == c)
			res++;
		i++;
	}
	
	return res;
}





/** Fonction permettant de traiter les opérations 
 *  soustraction, multiplication, multiplication par scalaire, exposant, solve_gauss
*/
  
Variable makeOperation(char* nom, int nbArgs, char** instrSep, char* separateurs, Variable varListe, char op){
	if(nbArgs != 1 && nbArgs !=2){
		printf("Erreur nombre d'arguments pour l'addition incorrects\n");
		return NULL;
	}
	char **sepMat = separe(instrSep[1], separateurs); //Séparation des éléments de l'instruction
	if(cptArgs(sepMat) != 2){
		printf("Mauvais usage\n");
		free(sepMat);
		return NULL;
	}
	
	Matrix m1 = trouverMat(sepMat[0], varListe);	//On chercher les matrices sur lesquelles il faut faire les opérations
	Matrix m2 = trouverMat(sepMat[1], varListe);
	Matrix tmp = NULL;
	
	E floatPourMult;				//Si on doit multiplier une matrice par un scalaire
	int intExpo;					//Entier pour expo matrix
	if((m1 == NULL || m2 == NULL) && (op != 't' && op !='e' && op !='p' && op!='v')){    //Si le résultat de trouverMat est NULL pour une des deux matrices, et qu'on ne cherche pas a multiplier par une scalaire ni a trouver la transposée
		printf("Arguments pour l'operation incorrects\n");
		return NULL;
	}
	if(m1 == NULL && m2 == NULL){			//Dans le cas où on veut multiplier par un scalaire, on vérifie qu'au moins un des deux arguments est une matrice
		printf("Erreur d'argument pour la multicplication par un scalaire\n");
		return NULL;
	}

	if(op == 't' && m1 == NULL){			// dans le cas de la multiplication par un scalaire, si m1 est null alors le premier argument doit etre un float
		if(isNumber(sepMat[0])){
			floatPourMult = strtof(sepMat[0],NULL);
		}
		else{
			floatPourMult = trouverFloat(sepMat[0], varListe);
			if(floatPourMult == NaN){
				printf("Erreur d'argument pour la multicplication par un scalaire\n");
				return NULL;
			}
		}
	}
	if(op == 't' && m2 == NULL){			// dans le cas de la multiplication par un scalaire, si m2 est null alors le second argument doit etre un float
		if(isNumber(sepMat[1])){
			floatPourMult = strtof(sepMat[1],NULL);
		}
		else{
			floatPourMult = trouverFloat(sepMat[1], varListe);
			if(floatPourMult == NaN){
				printf("Erreur d'argument pour la multicplication par un scalaire\n");
				return NULL;
			}
		}
	}
	

	if(op == 'e' && m1 == NULL){
		intExpo = atoi(sepMat[0]);
	}
	if(op == 'e' && m2 == NULL){
		intExpo = atoi(sepMat[1]);
	}

	free(sepMat);
	
	if(nbArgs == 1){				//de la forme instr()
		switch(op){
			case 'a' :
				tmp = addition(m1,m2);
				break;
			case 's' :
				tmp = soustraction(m1,m2);
				break;
			case 't' : 
				if(m1 != NULL){
					tmp = multScalaire(floatPourMult, m1);
				}
				else{
					tmp = multScalaire(floatPourMult,m2);
				}
				break;
			case 'm' :
				tmp = multiplication(m1,m2);
				break;
			case 'e' :
				if(m1 != NULL){
					tmp = expo(m1,intExpo);
				}
				else{
					tmp = expo(m2,intExpo);
				}
				break;
			case 'g' : 
				tmp = solve_gauss(m1,m2);
				break;
			default :
				printf("Very unexpected error, sorry (bad use of makeOperation)\n");
				return NULL;
		}
		if(tmp != NULL){
			displayMatrix(tmp);
			deleteMatrix(tmp);
		}
		return NULL;	
	}	
	switch(op){				//de la forme a : instr()
		case 'a' :
			varListe = adjVariable(nom,NaN,addition(m1,m2),varListe);
			return(varListe);
		case 's' :
			varListe = adjVariable(nom,NaN,soustraction(m1,m2), varListe);
			return(varListe);
		case 't' :
			if(m1 != NULL){
				varListe = adjVariable(nom, NaN, multScalaire(floatPourMult,m1), varListe);
				return(varListe);
			}
			else{
				varListe = adjVariable(nom, NaN, multScalaire(floatPourMult,m2), varListe);
				return(varListe);
			}
		case 'm' : 
			varListe = adjVariable(nom,NaN,multiplication(m1,m2),varListe);
			return(varListe);
		case 'e' :
			if(m1 != NULL){
				varListe = adjVariable(nom,NaN, expo(m1,intExpo), varListe);
				return(varListe);
			}
			else{
				varListe = adjVariable(nom,NaN,expo(m2,intExpo),varListe);
				return(varListe);
			}
		case 'g' : 
			varListe = adjVariable(nom,NaN,solve_gauss(m1,m2),varListe);
			return(varListe);

		default : 
			printf("Very unexpected error, sorry (bad use of makeOperation)\n");
			return NULL;
	}
}




/** Fonction premettant d'interpréter la ligne entrée par l'utilisateur
  */
int executeLine(char *line){
	char* lineCopy = malloc((strlen(line)+1)*sizeof(char));
	if(strcpy(lineCopy,line) == NULL){
		printf("Erreur de copie de l'entree\n");
		return 0;
	}
	char** lineSepSpeed;
	char** lineSep; 				// séparation des éléments de l'entrée
	static Variable varListe = NULL; 		// création d'un objet de type variable. (contiendra nom, valeur et pointeur sur un suivant)
	Variable varForOp = NULL; 		// Variable utilisée pour le retour des opérations
	
	char *nom = malloc(MAX_NOM); 	// le nom de la variable
	E valeurFloat; 					// si le 3e element est un float, on le stock la dedans
	char **instrSep; 				// séparation des éléments de l'instruction
	int nbArgs;						// Nombre d'arguments dans la ligne
	int i = 0 ; 					// compteurs (utilisé quand on crée une matrice)
	int j = 0;
	
	//for speedtest
	int taille_min;
	int taille_max;
	int pas;
	int nbSec;


	Matrix matLE = NULL; //matrice pour least_estimate et eigen_values
	
	//Variable pour création de matrice
	int nbl; //nombre de ligne de la matrice à créer
	int nbc; //nombre de colonnes de la matrice à créer
	char *separPourMatrice = "[], \n";
	char **sepMat;
	
		
	// -- Définition des séparateurs -- //
	char *separateursLine = ":\n";
	
	char *separateursInstr = "()\n";
	
	
	//Debut de l'interprétation
	
	//Cas spécial du speedtest et des commentaires
	
	lineSepSpeed = separe(lineCopy,separPourMatrice);
	if(strcmp(lineSepSpeed[0], "speedtest") == 0){
		nbArgs = cptArgs(lineSepSpeed);
		if(nbArgs < 4){
			printf("Nombre d'arguments pour speedtest incoherent\n");
			free(nom);
			free(lineSepSpeed);
			return 0;
		}
		
		taille_min = atoi(lineSepSpeed[2]);
		taille_max = atoi(lineSepSpeed[3]);
		pas = atoi(lineSepSpeed[4]);
		
		if(nbArgs == 4){
			nbSec = 1;
		}
		else{
			nbSec = atoi(lineSepSpeed[4]);
		}
		
		if(strcmp("addition",lineSepSpeed[1]) == 0){
			speedtest_add(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("sub",lineSepSpeed[1]) == 0){
			speedtest_sub(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("mult_scal",lineSepSpeed[1]) == 0){
			speedtest_mult_scal(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("mult",lineSepSpeed[1]) == 0){
			speedtest_mult(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("expo",lineSepSpeed[1]) == 0){
			speedtest_expo(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("transpose",lineSepSpeed[1]) == 0){
			speedtest_transpose(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("determinant",lineSepSpeed[1]) == 0){
			speedtest_det(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("invert",lineSepSpeed[1]) == 0){
			speedtest_inv(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("solve",lineSepSpeed[1]) == 0){
			speedtest_solve(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("rank",lineSepSpeed[1]) == 0){
			speedtest_rank(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("least_estimate",lineSepSpeed[1]) == 0){
			speedtest_least(taille_min, taille_max, pas, nbSec);
		}
		else if(strcmp("valeur_propre",lineSepSpeed[1]) == 0){
			speedtest_valp(taille_min, taille_max, pas, nbSec);
		}
		
		else{
			printf("Commande pour speedtest non reconnue\n");
		}
		free(lineSepSpeed);
		free(nom);
		free(lineCopy);
		return 0;
		
	}
	
	free(lineSepSpeed);
	free(lineCopy);
	
	//Cas standard
	

	lineSep = separe(line, separateursLine);
	
	if(strncmp("quit", lineSep[0], 4) == 0){
		free(lineSep);
		free(line);
		free(nom);

		if(varListe != NULL)
			freeVariable(varListe);
		printf("A bientot sur Minicas !\n");
		return 1;
	}
	
	nom = strncpy(nom, lineSep[0], strlen(lineSep[0])-1); //le nom de la variable est le premier mot de la ligne (-1 pour enlever l'espace)
	nom[strlen(lineSep[0])-1] = '\0';		      

	nbArgs = cptArgs(lineSep);
	
	if(nbArgs > 2){ //la ligne entrée est invalide (ne correspond pas à la syntaxe "<nom> : <instr>" ou "instr")
	    printf("Usage = <nom> : <instr> OU <instr>\n");
		free(lineSep);
		free(nom);
		return 0;        	
	}
	
	if(nbArgs == 1) // Si il n'y a qu'un instruction
	{
		instrSep = separe(lineSep[0], separateursInstr); //char** avec instructions séparés par '(', ')', ' ' et '\n'
	} // Fin if(nbArgs == 1)
	
	if(nbArgs == 2) // Si une déclaration/affectation est faite
	{
		//-- Vérification de la validité du nom --//
		
		if(!(*nom >= 'A' && *nom <= 'Z') && (!(*nom >= 'a' && *nom <= 'z'))){ //la variable est une minuscule ou une majuscule
			printf("le nom de la variable n'est pas valide, le premier caractère doit etre une lettre (minuscule ou majuscule\n");
			free(lineSep);
			free(nom);
			return 0;
		}
		else{
			if(existeDeja(nom, varListe)){ //une variable du même nom existe déjà
				delVariable(nom,varListe);
			}
			// le nom est valide (une seule lettre min ou maj) 			
			//ici, il faut regarder quelle est l'instruction à effectuer (matrice, float, mult, etc...)
							
			instrSep = separe(lineSep[1], separateursInstr); //char** avec instructions séparés par '(', ')', ' ' et '\n'
			
			if(instrSep[0][0] == ' ')
				instrSep[0] = instrSep[0]+1; // +1 pour enlever l'espace devant l'instruction
			if(isNumber(instrSep[0])){ //le troisieme element est un nombre
				valeurFloat = strtof(instrSep[0], NULL);
				varListe = adjVariable(nom, valeurFloat, NULL, varListe);
				printf("\t\t%f\n", (varListe->valF));
				free(instrSep);
				free(lineSep);
				free(nom);             //!
				return 0;	
			}
			// Si il faut créer une matrice
			if(strncmp("matrix", instrSep[0], 6) == 0){ 
				nbl = nb_occur(instrSep, ']', 1, strlen(instrSep[1])); //nb occurence de ] dans le contenu de matrix()
				if(nbl == 0){
					printf("Erreur, le nombre de ligne de la matrice est nul ! Operation annulee \n");
					free(instrSep);
					free(lineSep);
					free(nom);
					return 0;	
				}
				
				sepMat = separe(instrSep[1], separPourMatrice);
				nbc = cptArgs(sepMat)/nbl;
				varListe = adjVariable(nom,NaN,newMatrix(nbl,nbc),varListe);

				for(i=0;i<nbl;i++){
					for(j=0;j<nbc;j++){
						if((*sepMat[(nbc*i)+j] >= 97 && *sepMat[(nbc*i)+j] <= 122) || ((*sepMat[(nbc*i)+j]>=65 && *sepMat[(nbc*i)+j]<=90))){ //creation avec une var
							if(!existeDeja(sepMat[(nbc*i)+j],varListe)){    //on vérifie que la variable est dans varListe
								printf("On ne peut pas creer une matrice avec une variable non existante\n");
								free(sepMat);
								free(instrSep);
								free(lineSep);
								free(nom);
								return 0;
							}
							valeurFloat = trouverFloat(sepMat[(nbc*i)+j],varListe);
							setElt(varListe->valM,i,j,valeurFloat);
						}
						else{
							setElt(varListe->valM,i,j,strtof(sepMat[(nbc*i)+j],NULL));
						}
					}
				}
				
				displayMatrix(varListe->valM);
							
				free(sepMat);
				free(instrSep);
				free(lineSep);
				free(nom);  //!
				return 0;
			} // Fin if (création matrice)				
		} // Fin Else (nom correct)
 	}// Fin If args == 2 
		
		if(strncmp("addition", instrSep[0], 8) == 0){ //additionner matrice
			varForOp = makeOperation(nom,nbArgs, instrSep, separPourMatrice, varListe, 'a');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM, varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("sub", instrSep[0], 3) == 0){ //Il faut sub matrices
			varForOp = makeOperation(nom,nbArgs,instrSep,separPourMatrice,varListe,'s');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM, varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("mult_scal", instrSep[0], 9) == 0){ //mult matrix par scal
			varForOp = makeOperation(nom,nbArgs,instrSep,separPourMatrice,varListe,'t');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM,varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("mult", instrSep[0], 4) == 0){ //Il faut créer une matrice
			varForOp = makeOperation(nom,nbArgs,instrSep,separPourMatrice,varListe,'m');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM,varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		

		
		if(strncmp("expo", instrSep[0], 4) == 0){ //Elever puissance
			varForOp = makeOperation(nom,nbArgs, instrSep, separPourMatrice, varListe, 'e');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM,varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("transpose", instrSep[0], 9) == 0){ //Calcul de la transposée
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			if(nbArgs == 2){
				varListe = adjVariable(nom,NaN,transpose(trouverMat(instrSep[1],varListe)),varListe);
				displayMatrix(varListe->valM);
			}
			else{
				Matrix tmp = transpose(trouverMat(instrSep[1],varListe));
				displayMatrix(tmp);
				deleteMatrix(tmp);
			}
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("determinant", instrSep[0], 11) == 0){ //calcul det
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			if(nbArgs == 2){
				varListe = adjVariable(nom,(float)(determinant(trouverMat(instrSep[1],varListe))),NULL,varListe);
				printf("\t\t\t%f\n", (float)(varListe->valF));
			}
			else
				printf("\t\t\t%f\n",(float)(determinant(trouverMat(instrSep[1],varListe))));
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("invert", instrSep[0], 6) == 0){ //Il faut inv une matrice
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			if(nbArgs == 2){
				varListe = adjVariable(nom,NaN,inverse(trouverMat(instrSep[1],varListe)),varListe);
				displayMatrix(varListe->valM);
			}
			else{
				Matrix tmp = inverse(trouverMat(instrSep[1],varListe));
				displayMatrix(tmp);
				deleteMatrix(tmp);
			}
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("solve", instrSep[0], 6) == 0){ //reso equa line
			varForOp = makeOperation(nom,nbArgs, instrSep, separPourMatrice, varListe, 'g');
			if(varForOp == NULL){
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			varListe = adjVariable(varForOp->nom, varForOp->valF, varForOp->valM,varListe);
			displayMatrix(varListe->valM);
			free(varForOp->nom);
			free(varForOp);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("rank", instrSep[0], 6) == 0){ //calcul du rang d'une matrice
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			if(nbArgs == 2){
				varListe = adjVariable(nom,(float)(rank(trouverMat(instrSep[1],varListe))),NULL,varListe);
				printf("\t\t\t%f\n", (float)(varListe->valF));
			}
			else
				printf("\t\t\t%f\n",(float)(rank(trouverMat(instrSep[1],varListe))));
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("least_estimate", instrSep[0], 14) == 0){ // moindres carrés
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
			}
			matLE = newMatrix(trouverMat(instrSep[1],varListe)->nrows,1);
			if(nbArgs == 2){
				varListe = adjVariable(nom,NaN, least_estimation(trouverMat(instrSep[1],varListe),matLE),varListe);
				displayMatrix(varListe->valM);
			}
			else{
				Matrix tmp = least_estimation(trouverMat(instrSep[1],varListe),matLE);
				displayMatrix(tmp);
				deleteMatrix(tmp);
			}	
			deleteMatrix(matLE);	
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		if(strncmp("eigen_values", instrSep[0], 13) == 0){ //valeurs propres
			if(!existeDeja(instrSep[1],varListe)){
				printf("La matrice n'existe pas !\n");
				free(instrSep);
				free(lineSep);
				free(nom);
				return 0;
			}
			matLE = newMatrix(1,trouverMat(instrSep[1],varListe)->ncols);
			if(nbArgs == 2){
				varListe = adjVariable(nom,NaN,valeurs_propres(trouverMat(instrSep[1],varListe),matLE),varListe);
				printf("Vecteurs propres (en colonnes) : \n");
				displayMatrix(varListe->valM);
			}
			else{
				Matrix tmp = transpose(trouverMat(instrSep[1],varListe));
				printf("Vecteurs propres (en colonnes) : \n");
				displayMatrix(tmp);
				deleteMatrix(tmp);
			}
			printf("Liste des valeurs propres associées aux vecteurs propres :\n");
			displayMatrix(matLE);
			deleteMatrix(matLE);
			free(instrSep);
			free(lineSep);
			free(nom);
			return 0;
		}
		
		
		
		// Si l'instruction ne correspond à aucun cas connu
		
		printf("%s : instruction non reconnue !\n", instrSep[0]);
		free(instrSep);
		free(lineSep);
		free(nom);
		return 0;


}




int main(int argc, char **argv){

	if(argc == 2)	// Si un fichier est fourni en entrée
	{
		if(access(argv[1], F_OK) != 0){
			fprintf(stderr, "%s : fichier inexistant.\n", argv[1]);
			exit(1);
		}
		// Redirection d'entrée standard
		int fd = open(argv[1], O_RDONLY);
		if(fd == -1){
			fprintf(stderr, "Erreur d'ouverture.\n");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);	
	}
	
	struct stat buf; 
	FILE *f_in = fdopen(0, "r");
	char *line;
	size_t n=0; // initialisation sans importance
	
	int retExec;
	

	if (!fstat(0, &buf) && S_ISREG(buf.st_mode)) {        //file
		line=NULL;
		while (getline(&line, &n, f_in) != -1) {
			if(line[0] == '#'){
				printf("%s\n", line+1);
			}
			else if(line[0] != '\n'){
				retExec = executeLine(line);
				if(retExec == 1){
					break;
				}
			}
        	free(line);
        	line=NULL;
        }
    } 
    else {                                             //notfile
		char prompt[64];
		char login[32];
		if(getlogin_r(login, 32) != 0){
			sprintf(prompt, "%s> ", "minicas");
		}
		else{
			sprintf(prompt, "%s/%s> ", "minicas", login);
		}
    	line=NULL;
    	printf("%s", prompt);
        while (getline(&line, &n, f_in)!=-1) { 
			if(strncmp(line, "help", 4) == 0){
				printf("%s\n", help);
			}
			else if(line[0] != '\n'){
				retExec = executeLine(line);
				if(retExec == 1){
					break;
				}
			}
				
			free(line);
			line = NULL;
			printf("%s", prompt);
        } // Fin while

	} // Fin not file

	fclose(f_in);
    
	return 0;
}

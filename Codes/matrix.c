/**
 * \file matrix.c
 * \brief Définitions des fonctions de base sur les matrices.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"


/** Alloue l'espace mémoire nécessaire pour une matrice
 *  de taille nb_rows*nb_cols
 *  et retourne un pointeur sur l'espace alloué.
 *  Retourne NULL si les tailles entrées sont < 1 */
Matrix newMatrix(int nb_rows, int nb_cols)
{
	if(nb_rows < 1 || nb_cols < 1){
		fprintf(stderr, "Dimensions erronnées (<1) !\n");
		return NULL;
	}
	Matrix m = malloc(sizeof(struct matrix));
	m->nrows = nb_rows; m->ncols = nb_cols;
	m->mat = malloc(sizeof(E)*nb_cols*nb_rows);
	int i;
	for(i=0; i<nb_rows*nb_cols; i++)
		m->mat[i] = 0;
	
	return m;
}


/** Vérifie la validité des paramètres et renvoie
 *  l'élément rangée row colonne col.
 *  Retourne NaN si :
 *  - M n'est pas initialisée
 *  - les coordonnées données sont invalides */
E getElt(const Matrix M, int row, int col)
{
	if(M == NULL){
		fprintf(stderr, "getElt : matrice non initialisee\n");
		return NaN;
	}
	if(row < 0 || row >= M->nrows || col < 0 || col >= M->ncols){
		fprintf(stderr, "getElt : coordonnees invalides\n");
		return NaN;
	}
	// il y a M->ncols elmts par ligne
	return (M->mat[(M->ncols*row)+col]);
}

/** Vérifie la validité des paramètres
 *  puis affecte la valeur val à la rangée row colonne col */
void setElt(Matrix M, int row, int col, E val)
{
	if(M == NULL){
		fprintf(stderr, "setElt : matrice non initialisee\n");
		return;
	}
	if(row < 0 || row >= M->nrows || col < 0 || col >= M->ncols){
		fprintf(stderr, "getElt : coordonnees invalides\n");
		return;
	}
	
	M->mat[(M->ncols*row)+col] = val;
}


/** Libère l'espace mémoire du tableau mat et
 *  du pointeur M */
void deleteMatrix(Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "deleteMatrix : matrice non initialisee\n");
		return;
	}
	free(M->mat);
	free(M);
}


/** Affiche le contenu de la matrice si celle-ci est initialisée.
 *  Attention, fonction à modifier en fonction du type E ! */
void displayMatrix(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "displayMatrix : matrice non initialisee\n");
		return;
	}
	printf("\n");
	int i,j;
	for(i=0; i<M->nrows; i++){
		printf("[ ");
		for(j=0; j<M->ncols-1; j++){
			printf("%f   ", getElt(M, i, j));
		}
		printf("%f ]\n", getElt(M, i, M->ncols-1));
	}
	printf("\n");
}


/** Crée une nouvelle matrice (allocation mémoire)
 *  de même dimensions que la matrice M passée en argument
 *  et l'initialise avec le contenu de M.
 *  Retourne NULL si la matrice donnée en argument n'est 
 *  pas initialisée. */
Matrix copyMatrix(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "copyMatrix : matrice non initialisee\n");
		return NULL;
	}
	Matrix cpy = newMatrix(M->nrows, M->ncols);
	int i,j;
	for(i=0; i<M->nrows; i++){
		for(j=0; j<M->ncols; j++){
			setElt(cpy, i, j, getElt(M, i, j));
		}
	}
	return cpy;
}


/** Modifie par effet de bord la matrice B en y copiant
 *  le contenu de la matrice A, à condition que les deux
 *  matrices soient initialisées et de même dimensions. */
void copyFromAToB(const Matrix A, Matrix B)
{
	if(A == NULL || B == NULL){
		fprintf(stderr, "Matrice(s) non-initialisée(s).\n");
		return;
	}
	if(A->nrows!=B->nrows || A->ncols!=B->ncols){
		fprintf(stderr, "Matrices de dimensiosn différentes.\n");
		return;
	}
	int i,j;
	for(i=0; i<A->nrows; i++){
		for(j=0; j<A->ncols; j++){
			setElt(B, i, j, getElt(A, i, j));
		}
	}
}


/** Crée une nouvelle matrice carrée
 *  de dimension n*n et l'initialise
 *  comme une matrice identité.
 *  Retourne NULL si la taille passée 
 *  en paramètre est < 1 */
Matrix identite(int n)
{
	if(n < 1){
		fprintf(stderr, "identite : taille incorrecte (<1) !\n");
		return NULL;
	}
	Matrix M = newMatrix(n, n);
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==j){
				setElt(M, i, j, 1.);
			}
		}
	}
	
	return M;
}


/** Fonction auxiliaire : renvoie un flottant 
 *  aleatoire entre a et b exclu */
float frand_a_b(float a, float b)
{
	return (rand()/(float)RAND_MAX * (b-a) + a);
}


/** Crée une nouvelle patrice de taille nb_rows*nb_cols
 *  et l'initialise avec des flottants aléatoires entre
 *  min et max (exclu).
 *  Retourne NULL si les dimensions entrées sont < 1 */
Matrix aleatoire(int nb_rows, int nb_cols, E min, E max)
{
	if(nb_rows < 1 || nb_cols < 1){
		fprintf(stderr, "aleatoire : dimensions incorrectes (<1) !\n");
		return NULL;
	}
	srand(time(NULL));
	Matrix M = newMatrix(nb_rows, nb_cols);
	int i, j;
	for(i=0; i<nb_rows; i++){
		for(j=0; j<nb_cols; j++){
			setElt(M, i, j, frand_a_b(min, max));
		}
	}
	return M;
}

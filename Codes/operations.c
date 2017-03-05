/**
 * \file operations.c
 * \brief Définitions des opérations algébriques sur les matrices.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"

/** Crée une nouvelle matrice constituée de A+B
 *  Retourne NULL si :
 *  - A ou B n'est pas initialisée
 *  - A et B ne sont pas de même dimensions */
Matrix addition(const Matrix A, const Matrix B)
{
	if(A == NULL || B == NULL){
		fprintf(stderr, "addition : matrices non initialisées.\n");
		return NULL;
	}
	if(A->nrows != B->nrows || A->ncols != B->ncols){
		fprintf(stderr, "addition : matrices de dimensions différentes.\n");
		return NULL;
	}
	
	Matrix M = newMatrix(A->nrows, A->ncols);
	int i,j;
	for(i=0; i<M->nrows; i++){
		for(j=0; j<M->ncols; j++){
			E a = getElt(A, i, j);
			E b = getElt(B, i, j);
			setElt(M, i, j, a+b);
		}
	}
	
	return M;
}


/** Crée une nouvelle matrice allouée contenant A-B.
 *  Retourne NULL si :
 *  - A ou B n'est pas initialisée
 *  - A et B ont des dimensions différentes */
Matrix soustraction(const Matrix A, const Matrix B)
{
	if(A == NULL || B == NULL){
		fprintf(stderr, "soustraction : matrices non-initialisées.\n");
		return NULL;
	}
	if(A->nrows != B->nrows || A->ncols != B->ncols){
		fprintf(stderr, "soustraction : matrices de dimensions différentes.\n");
		return NULL;
	}
	
	Matrix M = newMatrix(A->nrows, A->ncols);
	int i,j;
	for(i=0; i<M->nrows; i++){
		for(j=0; j<M->ncols; j++){
			E a = getElt(A, i, j);
			E b = getElt(B, i, j);
			setElt(M, i, j, a-b);
		}
	}
	
	return M;
}


/** Crée une nouvelle matrice éale à la matrice M
 *  multipliée par le scalaire v.
 *  Retourne NULL si M n'est pas initialisée. */
Matrix multScalaire(E v, const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "multScalaire : matrice non initialisée.\n");
		return NULL;
	}
	
	Matrix C = newMatrix(M->nrows, M->ncols);
	int i, j;
	for(i=0; i<M->nrows; i++){
		for(j=0; j<M->ncols; j++){
			setElt(C, i, j, v*getElt(M, i, j));
		}
	}
	
	return C;
}


/** Crée une nouvelle matrice constitué du produit matriciel
 *  de A par B. 
 *  Retourne NULL si :
 *  - A ou B ne sont pas initialisées
 *  - le nombre de colonnes de A est différent du nombre de lignes de B */
Matrix multiplication(const Matrix A, const Matrix B)
{
	if(A == NULL || B == NULL){
		fprintf(stderr, "multiplication : matrices non initialisées.\n");
		return NULL;
	}
	if(A->ncols != B->nrows){
		fprintf(stderr, "multiplication : dimensions invalides.\n");
		return NULL;
	}
	E cij = 0;
	Matrix M = newMatrix(A->nrows, B->ncols);
	int i, j, k;
	for(i=0; i < A->nrows; i++){
		for(j=0; j < B->ncols; j++){
			cij = 0;
			for(k=0; k < A->ncols; k++){
				cij = cij + getElt(A, i, k)*getElt(B, k, j);
			}
			setElt(M, i, j, cij);
		}
	}
	
	return M;	
}


/** Crée une nouvelle matrice correspondant à A puissance n.
 *  Retourne NULL si :
 *  - A n'est pas initialisée
 *  - A n'est pas une matrice carrée
 *  - n < 0
 *  Note : expo(A, 0) crée la matrice identité de même dimension que A */
Matrix expo(const Matrix A, int n)
{
	if(A == NULL){
		fprintf(stderr, "expo : matrice non initialisée.\n");
		return NULL;
	}
	if(A->nrows != A->ncols){
		fprintf(stderr, "expo : matrice non carée.\n");
		return NULL;
	}
	if(n < 0){
		fprintf(stderr, "expo : puissance négative interdite.\n");
		return NULL;
	}
	
	if(n == 0){
		Matrix Idt = identite(A->nrows);
		return Idt;
	}
	
	int i, j, k;
	Matrix M = copyMatrix(A);
	Matrix tmp = copyMatrix(A);
	while(n > 1){
		for(i=0; i < M->nrows; i++){
			for(j=0; j < M->ncols; j++){
				E cij = 0;
				for(k=0; k < M->nrows; k++){
					cij = cij + getElt(tmp, i, k)*getElt(A, k, j);
				}
				setElt(M, i, j, cij);
			}
		}
		copyFromAToB(M, tmp);
		n--;
	}
	deleteMatrix(tmp);
	return M;
}


/** Retourne un type E correspondant à la norme de V.
 *  Retourne NaN si :
 *  - V n'est pas initialisé
 *  - V n'est pas un vecteur (plus d'une colonne/plus d'une ligne) */
E normeVector(const Matrix V)
{
	if(V == NULL){
		fprintf(stderr, "normeVector : vecteur non initialisé\n");
		return NaN;
	}
	
	if(V->nrows == 1){
		int j;
		E norme = 0;
		for(j=0; j<V->ncols; j++){
			norme += pow((double)getElt(V, 0, j), 2);
		}
		return sqrt((double)norme);
	}
	else if(V->ncols == 1){
		int i;
		E norme = 0;
		for(i=0; i<V->nrows; i++){
			norme += pow((double)getElt(V, i, 0), 2);
		}
		return sqrt((double)norme);
	}
	
	else{
		fprintf(stderr, "normeVector : la matrice n'est pas un vecteur.\n");
		return NaN;
	}
}


/** Crée une nouvelle matrice correspondant à la transposée de M.
 *  Retourne NULL si M n'est pas initialisée. */
Matrix transpose(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "transpose : matrice non initialisée.\n");
		return NULL;
	}
	Matrix T = newMatrix(M->ncols, M->nrows);
	int i,j;
	for(i=0; i < M->ncols; i++){
		for(j=0; j < M->nrows; j++){
			setElt(T, i, j, getElt(M, j, i));
		}
	}
	return T;
}


/** Fonction auxiliaire : retourne l'indice du meilleur pivot
 *  sur la colonne onCol à partir de la ligne fromRow (les lignes
 *  au dessus sont ignorées).
 *  Retourne -1 si :
 *  - M n'est pas initialisée
 *  - le numéro de rangée ou de colonne est invalide */
int getPivot(const Matrix M, int fromRow, int onCol)
{
	if(M == NULL){
		fprintf(stderr, "getPivot : matrice non initialisée.\n");
		return -1;
	}
	if(fromRow < 0 || fromRow >= M->nrows){
		fprintf(stderr, "getPivot : numéro de ligne invalide.\n");
		return -1;
	}
	if(onCol < 0 || onCol >= M->ncols){
		fprintf(stderr, "getPivot : numéro de colonne invalide.\n");
		return -1;
	}
	
	int i, indicePivot = fromRow;
	E pivot = getElt(M, fromRow, onCol);
	E elt;
	for(i=fromRow+1; i < M->nrows; i++){
		elt = getElt(M, i, onCol);
		if(fabs((double)elt) >fabs((double)pivot)){
			pivot = elt;
			indicePivot = i;
		}
	}
	return indicePivot;
}


/** Fonction auxiliaire modifiant la matrice M passée en paramètre.
 *  Echange la ligne row1 et la ligne row2 (utilisée pour le
 *  pivot partiel, pivot de Gauss).
 *  Les cas d'erreurs n'entrainent aucune modification. */
void swapRows(Matrix M, int row1, int row2)
{
	if(M == NULL){
		fprintf(stderr, "swapRows : matrice non initialisee.\n");
		return;
	}
	if(row1 < 0 || row1 >= M->nrows || row2 < 0 || row2 >= M->nrows){
		fprintf(stderr, "swapRows : numero de ligne invalide.\n");
		return;
	}
	
	E temp; int j;
	for(j=0; j < M->ncols; j++){
		temp = getElt(M, row1, j);
		setElt(M, row1, j, getElt(M, row2, j));
		setElt(M, row2, j, temp);
	}
}


/** Modifie la matrice M passée en paramètre en effectuant une combinaison
 *  linéaire sur la ligne onRow, avec la ligne withRow et le rapport rapport.
 *  Les cas d'erreurs n'entrainent aucune modification. */
void combiLin(Matrix M, int onRow, int withRow, double rapport)
{
	if(M == NULL){
		fprintf(stderr, "combiLin : matrice non initialisée.\n");
		return;
	}
	if(onRow < 0 || onRow >= M->nrows){
		fprintf(stderr, "combiLin : numéro de ligne cible invalide.\n");
		return;
	}
	if(withRow < 0 || withRow >= M->nrows){
		fprintf(stderr, "combiLin : numéro de ligne source invalide.\n");
		return;
	}
	
	int j;
	for(j=0; j < M->ncols; j++){
		setElt(M, onRow, j, (getElt(M, onRow, j) + rapport*getElt(M, withRow, j)));
	}
}


/** Fonction auxiliaire pour la triangularisation de matrice.
 *  Crée une nouvelle matrice correspondant à la triangularisation de M.
 *  L'argument modifier est modifié par effet de bord pour sauvegarder 
 *  les inversions de sens liées aux échanges de lignes dans le calcul
 *  du déterminant.
 *  Retourne NULL si M n'est pas initialisée. */
Matrix __triangle(const Matrix M, double *modifier)
{
	if(M == NULL){
		fprintf(stderr, "triangle : matrice non-initialisée.\n");
		return NULL;
	}
	
	// Copie de M
	Matrix T = copyMatrix(M);
	int pivot;
	double rapport;
	// Descente du pivot de Gauss
	int i,k;
	for(i=0; i < T->nrows-1; i++){
		// Choix du pivot partiel
		pivot = getPivot(T, i, i);
		if(getElt(T, pivot, i) != 0){
			if(pivot != i){ // echange de lignes
				swapRows(T, i, pivot);
				if(modifier != NULL){
					*modifier = -1*(*modifier);
				}
			}
			for(k=i+1; k < T->nrows; k++){
				rapport = -1*(getElt(T, k, i)/getElt(T, i, i));
				// Combinaisons lineaires
				combiLin(T, k, i, rapport);
			}
		}
	}
	return T;
}


/** Appelle la fonction auxiliaire __triangle et retourne la
 *  matrice ainsi crée.
 *  Retourne NULL si M n'est pas initialisée. */
Matrix triangle(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "triangle : matrice non initialisée.\n");
		return NULL;
	}
	return __triangle(M, NULL);
}


/** Calcule le déterminant de la matrice M en la triangularisant.
 *  Retourne NaN si M n'est pas initialisée. */
double determinant(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "determinant : matrice non initialisée.\n");
		return NaN;
	}
	int i;
	double modifier = 1;
	Matrix triangle = __triangle(M, &modifier);
	for(i=0; i < M->nrows; i++){
		modifier = modifier*getElt(triangle,i,i);
	}
	deleteMatrix(triangle);
	return modifier;
}


/** Crée une nouvelle matrice correspondant à l'inverse de M
 *  par triangularisation et remontée du pivot de Gauss.
 *  Retourne NULL si :
 *  - M n'est pas initialisée
 *  - M n'est pas carrée
 *  - M n'est pas inversible (det(M)==0) */
Matrix inverse(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "inverse : matrice non initialisée.\n");
		return NULL;
	}
	if(M->nrows != M->ncols){
		fprintf(stderr, "inverse : matrice non carrée.\n");
		return NULL;
	}
	
	Matrix idt = identite(M->nrows);
	Matrix cpy = copyMatrix(M);
	int pivot;
	double rapport;
	double det = 1;
	E div;
	// Descente du pivot de Gauss sur les deux matrices
	int i,j;
	for(i=0; i<cpy->nrows-1; i++){
		// Choix du pivot partiel et triangularisation de cpy
		pivot = getPivot(cpy, i, i);
		if(getElt(cpy, pivot, i) != 0){
			if(pivot != i){ // echange de lignes sur les deux matrices
				swapRows(cpy, i, pivot);
				swapRows(idt, i, pivot);
				det = -1*det;
			}
			rapport = -1*(getElt(cpy, i+1, i)/getElt(cpy, i, i));
			// Combinaison lineaire sur les deux matrices
			combiLin(cpy, i+1, i, rapport);
			combiLin(idt, i+1, i, rapport);
		}
	}
	// Verification du determinant
	for(i=0; i<cpy->nrows; i++){
		det = det*getElt(cpy,i,i);
	}
	
	if((int)det==0){
		printf("Matrice non inversible. \n");
		deleteMatrix(idt);
		deleteMatrix(cpy);
		return NULL;
	}
	
	// Diagonalisation de cpy
	for(j=cpy->ncols-1; j>=0; j--){
		for(i=j-1; i>=0; i--){
			rapport = -1*(getElt(cpy, i, j)/getElt(cpy,j,j));
			combiLin(cpy, i, j, rapport);
			combiLin(idt, i, j, rapport);
		}
	}
	// Normalisation de la diagonale (appliquee a idt, inutile sur cpy)
	for(i=0; i<cpy->nrows; i++){
		div = getElt(cpy, i, i);
		for(j=0; j<cpy->ncols; j++){
			setElt(idt, i, j, (getElt(idt, i, j)/div));
		}
	}
	deleteMatrix(cpy);
	return idt;
}


/** Résoud le système Ax=B par la méthode du pivot partiel
 *  et revoie le résultat x sous forme d'une matrice à 1 colonne.
 *  Retourne NULL si :
 *  - A ou B n'est pas initialisée
 *  - A n'est pas une matrice carrée
 *  - A et B n'ont pas le même nombre de lignes */
Matrix solve_gauss(const Matrix A, const Matrix B)
{
	if(A == NULL || B == NULL){
		fprintf(stderr, "solve_gauss : matrices non initialisées.\n");
		return NULL;
	}
	
	if(A->nrows != A->ncols){
		fprintf(stderr, "solve_gauss : matrice A non carrée.\n");
		return NULL;
	}
	
	if(A->nrows != B->nrows || B->ncols != 1){
		fprintf(stderr, "solve_gauss : données invalides (dimensions incohérentes).\n");
		return NULL;
	}
	
	int i,j,k;
	Matrix x = newMatrix(A->ncols, 1);
	for(i=0; i<x->nrows; i++)
		setElt(x, i, 0, 1);
	Matrix ta = copyMatrix(A);
	Matrix tb = copyMatrix(B);
	int pivot;
	double rapport;
	// Descente du pivot de Gauss
	for(i=0; i<ta->nrows-1; i++){
		// Choix du pivot partiel
		pivot = getPivot(ta, i, i);
		if(getElt(ta, pivot, i) != 0){
			if(pivot != i){ // echange de lignes
				swapRows(ta, i, pivot);
				swapRows(tb, i, pivot);
			}
			for(k=i+1; k<ta->nrows; k++){
				rapport = -1*(getElt(ta, k, i)/getElt(ta, i, i));
				// Combinaison lineaire
				combiLin(ta, k, i, rapport);
				combiLin(tb, k, i, rapport);
			}
		}
	}
	
	// Remontee pour calculer les xi
	E sum = 0;
	for(i=ta->nrows-1; i>=0; i--){
		for(j=0; j<ta->ncols; j++){
			if(i!=j)
				sum += getElt(ta, i, j);
		}
		sum = getElt(tb, i, 0) - sum;
		sum = sum / getElt(ta, i, i);
		setElt(x, i, 0, sum);

		// On remplace xi par sa valeur dans les lignes superieurs
		if(i!=0){
			for(k=i-1; k>=0; k--){
				setElt(ta, k, i, getElt(ta, k, i)*sum);
			}
		}
		sum = 0;
	}		
	
	deleteMatrix(ta);
	deleteMatrix(tb);
	return x;
}


/** Calcule le rang de la matrice M par pivot de Gauss.
 *  Retourne -1 si M n'est pas initialisée. */
int rank(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "rank : matrice non-initialisée.\n");
		return -1;
	}
	
	Matrix T = triangle(M);
	int i,j;
	int nbr_non_null = 0;
	int is_non_null;
	for(i=0; i < T->nrows; i++){
		is_non_null = 1;
		for(j=0; j < T->ncols; j++){
			if((int)getElt(T, i, j) != 0){
				is_non_null = 0;
				break;
			}
		}
		if(is_non_null)
			nbr_non_null++;
	}
	
	deleteMatrix(T);
	return nbr_non_null;
}


/** Renvoie la composante dominante (la plus grande
 *  en valeur absolue) de la matrice M.
 *  Retourne NaN si M n'est pas initialisée. */
E val_dominante(const Matrix M)
{
	if(M == NULL){
		fprintf(stderr, "val_dominante : matrice non-initialisée.\n");
		return NaN;
	}
	
	int i,j;
	E vdom = getElt(M, 0, 0);
	E vcur;
	for(i=0; i < M->nrows; i++){
		for(j=0; j < M->ncols; j++){
			vcur = getElt(M, i, j);
			if((E)fabs(vdom) > (E)fabs(vcur))
				vdom = vcur;
		}
	}
	
	return vdom;
}


/** Méthode de la puissance itérée :
 * 	Approxime le vecteur propre associé à la valeur
 *  propre dominante de la matrice M. L'argument mu
 *  modifie une variable E par effet de bord pour 
 *  donner la valeur propre, et la fonction renvoie
 *  le vecteur (nouvelle matrice initialisée).
 *  Retourne NULL si :
 *  - A ou mu sont NULL
 *  - A n'est pas carrée */
Matrix approx_val_propre_dominante(const Matrix M, E *mu)
{
	if(M == NULL || mu == NULL){
		fprintf(stderr, "approx_val_propre_dominante : la matrice et l'élément en argument doivent êtres initialisés.\n");
		return NULL;
	}
	if(M->nrows != M->ncols){
		fprintf(stderr, "approx_val_propre_dominante : la matrice doit être carrée.\n");
		return NULL;
	}
	
	Matrix v = newMatrix(M->nrows, 1);
	int i; 
	for(i=0; i < M->nrows; i++){
		setElt(v, i, 0, 1);
	}
	E seuil = 0.0001;
	E mu_t = 1;
	*mu = 0;
	Matrix tmp = NULL;
	// Tant que mu évolue de manière significative
	while((E)fabs((*mu)-mu_t) > seuil)
	{
		mu_t = *mu;
		tmp = v;
		v = multiplication(M, v);
		deleteMatrix(tmp);
		*mu = val_dominante(v);
		tmp = v;
		v = multScalaire((1/(*mu)), v);
		deleteMatrix(tmp);
	} 
	
	// Retour de l'approximation de l'élément propre mu par effet de bord
	return v;		// Retour direct du vecteur propre associé à cette valeur propre dominante		
}


/** Méthode de la déflation :
 *  Calcule toutes la valeurs propres approximées
 *  de la matrice M en utilisant la puissance itérée.
 *  Retourne les valeurs sous la formes d'une matrice
 *  dont les colonnes sont les vecteurs propres,
 *  et remplie la matrice donnée en argument par effet
 *  de bord avec les valeurs propres associées aux vecteurs
 *  en colonne correspondante.
 *  Retourne NULL si 
 *  - M n'est pas initialisée ou pas carrée.
 *  - Si vp n'est pas initialisé ou est fourni avec un nombre 
 *  de colonnes différent de M.
 * */
Matrix valeurs_propres(const Matrix M, Matrix vp)
{
	if(M == NULL || vp == NULL){
		fprintf(stderr, "valeurs_propres : matrices non-initialisées.\n");
		return NULL;
	}
	if(M->nrows != M->ncols){
		fprintf(stderr, "valeurs_propres : matrice non-carrée.\n");
		return NULL;
	}
	if(vp->ncols != M->ncols){
		fprintf(stderr, "valeurs_propres : vecteur pour les valeurs propres de taille incompatible.\n");
		return NULL;
	}
	
	int k = 0, n = M->nrows, i;
	E v;
	Matrix P = newMatrix(n, n);
	Matrix A = copyMatrix(M);

	Matrix tC = NULL;
	Matrix C = NULL;		// Colonne = k-ème vecteur propre
	Matrix CC = NULL;
	Matrix tmp = NULL;
	
	while(k < n){
		// Calcul du k-ème vecteur propre/valeur propre
		C = approx_val_propre_dominante(A, &v);
		
		// Mise a jour des Matrices
		setElt(vp, 0, k, v);
		for(i=0; i < n; i++){
			setElt(P, i, k, getElt(C, i, 0));
		}
		
		// Déflation : A = A - (v/||C||²).C.tC
		tC = transpose(C);
		CC = C;
		C = multiplication(C, tC);
		deleteMatrix(tC);
		tmp = C;
		C = multScalaire((v / pow(normeVector(CC), 2)), C);
		deleteMatrix(CC);
		deleteMatrix(tmp);
		tmp = A;
		A = soustraction(A, C);
		deleteMatrix(tmp);
		
		deleteMatrix(C);
		k++;
	}
	
	deleteMatrix(A);
	return P;
}


/** Estimation de la droite des moindres carrés.
 *  Prend en entrée la matrice nx2 des observations
 *  (colonne 0 : entrées // colonne 1 : sortie)
 *  et produit en sortie le vecteur [a b] des 
 *  coefficients de la droite (a.x + b).
 * 	Si un vecteur de taille n est donné passé en paramètre,
 *  il est rempli par effet de bord avec les résidus.
 *  Retourne NULL si :
 *  - Obs n'est pas initialisée
 *  - Obs a un nbr de colonne différent de 2
 *  - le vecteur passé en paramètre est de taille incompatible avec Obs */
Matrix least_estimation(const Matrix Obs, Matrix Residu)
{
	if(Obs == NULL){
		fprintf(stderr, "least_estimation : matrice non-initialisée.\n");
		return NULL;
	}
	if(Obs->ncols != 2){
		fprintf(stderr, "least_estimation : la matrice des observations doit avoir 2 colonnes (entrées/sorties).\n");
		return NULL;
	}
	if(Residu != NULL){
		if(Residu->ncols != 1){
			fprintf(stderr, "least_estimation : le vecteur des résidus doit avoir une seule colonne !\n");
			return NULL;
		}
		if(Residu->nrows != Obs->nrows){
			fprintf(stderr, "least_estimation : le vecteur des résidus doit avoir le même nombre de lignes que la matrice d'observations !\n");
			return NULL;
		}
	}
	
	// Création du systeme A.x = B
	int i;
	Matrix A = newMatrix(Obs->nrows, 2);
	for(i=0; i < Obs->nrows; i++){
		setElt(A, i, 0, getElt(Obs, i, 0));		// On copie les entrées
		setElt(A, i, 1, 1);
	}
	
	Matrix B = newMatrix(Obs->nrows, 1);
	for(i=0; i < Obs->nrows; i++){
		setElt(B, i, 0, getElt(Obs, i, 1));		// On copie les sorties
	}
	
	// Création du système AT.A.x = AT.B
	Matrix AT = transpose(A);
	Matrix ATA = multiplication(AT, A);
	Matrix ATB = multiplication(AT, B);
	
	deleteMatrix(A);
	deleteMatrix(B);
	deleteMatrix(AT);
	
	// Résolution
	E tmp = 1/getElt(ATA, 1, 1);
	setElt(ATA, 1, 0, getElt(ATA, 1, 0)*tmp);
	setElt(ATA, 1, 1, getElt(ATA, 1, 1)*tmp);
	setElt(ATB, 1, 0, getElt(ATB, 1, 0)*tmp);
	
	tmp = getElt(ATA, 0, 1);
	setElt(ATA, 0, 1, tmp*getElt(ATA, 1, 0)*-1);
	setElt(ATB, 0, 0, getElt(ATB, 0, 0)-(tmp*getElt(ATB, 1, 0)));
	
	setElt(ATA, 0, 1, getElt(ATA, 0, 0)+getElt(ATA, 0, 1));
	setElt(ATB, 0, 0, getElt(ATB, 0, 0)/getElt(ATA, 0, 1));							// a trouvé
	setElt(ATA, 1, 0, getElt(ATA, 1, 0)*getElt(ATB, 0, 0));
	setElt(ATB, 1, 0, (getElt(ATB, 1, 0)-getElt(ATA, 1, 0))/getElt(ATA, 1, 1));		// b trouvé
	
	deleteMatrix(ATA);
	
	// Calcul des résidus : ri = |yi - (a.xi + b)|
	if(Residu != NULL){
		E ri;
		for(i=0; i < Residu->nrows; i++){
			ri = (E) fabs(getElt(Obs, i, 1) - (getElt(ATB, 0, 0)*getElt(Obs, i, 0) + getElt(ATB, 1, 0)));
			setElt(Residu, i, 0, ri);
		}
	}
	
	return ATB;
}

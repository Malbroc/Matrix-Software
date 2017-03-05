/**
 * \file matrix.h
 * \brief Définition du type Matrix déclarations des opérations de base
 * sur les matrices.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
#ifndef __MATRIX_H
#define __MATRIX_H

/*-------------------------------------*
 *           STRUCT MATRIX             *
 *-------------------------------------*/

#define NaN 0.0/0.0
typedef float E;
typedef struct matrix {
	E *mat;
	int nrows, ncols;
} *Matrix;


/* OPERATIONS BASIQUES */

Matrix newMatrix(int nb_rows, int nb_cols);
E getElt(const Matrix M, int row, int col);
void setElt(Matrix M, int row, int col, E val);
void deleteMatrix(Matrix M);
void displayMatrix(const Matrix M);
Matrix copyMatrix(const Matrix M);
void copyFromAToB(const Matrix A, Matrix B);
Matrix identite(int n);
float frand_a_b(float a, float b);
Matrix aleatoire(int nb_rows, int nb_cols, E min, E max);

#endif


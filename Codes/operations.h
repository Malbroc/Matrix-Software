/**
 * \file operations.h
 * \brief Déclarations des opérations algébriques sur les matrices.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
#ifndef __OPERATIONS_H
#define __OPERATIONS_H
#include "matrix.h"

/*-------------------------------------*
 *    Opérations sur les matrices      *
 *-------------------------------------*/

Matrix addition(const Matrix A, const Matrix B);
Matrix soustraction(const Matrix A, const Matrix B);
Matrix multScalaire(E v, const Matrix M);
Matrix multiplication(const Matrix A, const Matrix B);
Matrix expo(const Matrix A, int n);
E normeVector(const Matrix V);
Matrix transpose(const Matrix M);
int getPivot(const Matrix M, int fromRow, int onCol);
void swapRows(Matrix M, int row1, int row2);
void combiLin(Matrix M, int onRow, int withRow, double rapport);
Matrix __triangle(const Matrix M, double *modifier);
Matrix triangle(const Matrix M);
double determinant(const Matrix M);
Matrix inverse(const Matrix M);
Matrix solve_gauss(const Matrix A, const Matrix B);
int rank(const Matrix M);
E val_dominante(const Matrix M);
Matrix approx_val_propre_dominante(const Matrix M, E *mu);
Matrix valeurs_propres(const Matrix M, Matrix vp);
Matrix least_estimation(const Matrix Obs, Matrix Residu);

#endif


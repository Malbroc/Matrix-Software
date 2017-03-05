#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "operations.h"
#include "speedtest.h"


int main()
{
	/**-------------- TEST identite addition --------------*/
	
	/*Matrix m = newMatrix(4, 4);
	setElt(m, 2, 3, 6.6);
	printf("Element en %d,%d : %f\n", 2, 3, getElt(m, 2, 3));
	displayMatrix(m);
	
	Matrix id = identite(4);
	displayMatrix(id);
	
	Matrix add = addition(m, id);
	displayMatrix(add);
	swapRows(add, 1, 3);
	displayMatrix(add);
	
	deleteMatrix(m);
	deleteMatrix(id);
	deleteMatrix(add);*/
	
	
	/**-------------- TEST multiplication --------------*/
	
	/*Matrix A = newMatrix(2,3);
	setElt(A,0,0,1);
	setElt(A,0,1,2);
	setElt(A,0,2,0);
	setElt(A,1,0,4);
	setElt(A,1,1,3);
	setElt(A,1,2,-1);
	displayMatrix(A);
	
	Matrix B = newMatrix(3,2);
	setElt(B,0,0,5);
	setElt(B,0,1,1);
	setElt(B,1,0,2);
	setElt(B,1,1,3);
	setElt(B,2,0,3);
	setElt(B,2,1,4);
	displayMatrix(B);
	
	Matrix M = multiplication(A, B);	// Res attendu [9 7] [23 9]
	displayMatrix(M);

	deleteMatrix(A);
	deleteMatrix(B);
	deleteMatrix(M);*/
	
	
	/**-------------- TEST exposant --------------*/
	
	/*Matrix A = newMatrix(2,2);
	setElt(A, 0, 0, 2);
	setElt(A, 0, 1, 4);
	setElt(A, 1, 0, 1);
	setElt(A, 1, 1, 1);
	
	Matrix A3 = expo(A, 3);
	displayMatrix(A3);		// Resultat attendu : (28, 44) (11, 17)
	deleteMatrix(A);
	deleteMatrix(A3);*/
	
	
	/**-------------- TEST matrice aléatoire --------------*/
	
	/*Matrix alea = aleatoire(4, 6, -10, 10);
	displayMatrix(alea);
	Matrix aleat = transpose(alea);
	displayMatrix(aleat);
	deleteMatrix(alea);
	deleteMatrix(aleat);*/
	
	
	/**--- TEST determinant, triangularisation, inversion, norme et multScalaire ---*/
	
	/*Matrix m = newMatrix(3,3);
	setElt(m,0,0,1);
	setElt(m,0,1,2);
	setElt(m,0,2,-3);
	
	setElt(m,1,0,4);
	setElt(m,1,1,3);
	setElt(m,1,2,-1);
	
	setElt(m,2,0,0);
	setElt(m,2,1,1);
	setElt(m,2,2,2);
	
	printf("Matrice initiale\n");
	displayMatrix(m);
	
	printf("determinant : %f\n", determinant(m));	// Résultat attendu : -21
	
	Matrix tr = triangle(m);
	printf("Matrice triangularisee\n");		// Résultat attendu : [4 3 -1][0 5/4 -11/4][0 0 21/5]
	displayMatrix(tr);
	deleteMatrix(tr);
	
	Matrix inv = inverse(m);
	printf("Matrice inversee\n");
	displayMatrix(inv);
	
	Matrix testinv = multiplication(m, inv); // devrait etre la matrice identite
	displayMatrix(testinv);
	
	deleteMatrix(m);
	deleteMatrix(inv);
	deleteMatrix(testinv);*/


	/**--- TEST resolution systeme par pivot de gauss (pivot partiel) ---*/
	
	/*Matrix A = newMatrix(3, 3);
	setElt(A, 0, 0, 3);
	setElt(A, 0, 1, 5);
	setElt(A, 0, 2, 7);
	setElt(A, 1, 0, 2);
	setElt(A, 1, 1, 10);
	setElt(A, 1, 2, 6);
	setElt(A, 2, 0, 1);
	setElt(A, 2, 1, 2);
	setElt(A, 2, 2, 3);
	Matrix B = newMatrix(3, 1);
	setElt(B, 0, 0, 101);
	setElt(B, 1, 0, 134);
	setElt(B, 2, 0, 40);
	Matrix X = solve_gauss(A, B);	// resultat attendu 7/9/5
	displayMatrix(X);
	
	deleteMatrix(A);
	deleteMatrix(B);
	deleteMatrix(X);
	*/
	
	/**-------------- TEST rang d'une matrice --------------*/
	
	/*Matrix M = newMatrix(4, 4);
	setElt(M, 0, 0, 1); setElt(M, 0, 1, 0); setElt(M, 0, 2, 2); setElt(M, 0, 3, 3);
	setElt(M, 1, 0, 2); setElt(M, 1, 1, 0); setElt(M, 1, 2, 4); setElt(M, 1, 3, 6);
	setElt(M, 2, 0, 0); setElt(M, 2, 1, 2); setElt(M, 2, 2, 2); setElt(M, 2, 3, 0);
	setElt(M, 3, 0, 1); setElt(M, 3, 1, 2); setElt(M, 3, 2, 4); setElt(M, 3, 3, 3);
	displayMatrix(M);
	printf("rang de la matrice : %d\n", rank(M));	// Résultat attendu : 2
	deleteMatrix(M);*/
	
	
	/**-------------- TEST Valeur propre dominante --------------*/
	
	/*Matrix M = newMatrix(2, 2);
	setElt(M, 0, 0, 1.36);
	setElt(M, 0, 1, 0.56);
	setElt(M, 1, 0, 0.14);
	setElt(M, 1, 1, 0.94);
	
	E l;
	Matrix v = approx_val_propre_dominante(M, &l);
	displayMatrix(v);			// Resultats attendu : [ 4 1 ]
	printf("associé à l'élément propre %f\n", l);	// ~ 1.5
	deleteMatrix(v);
	deleteMatrix(M);*/
	
	/**-------------- TEST toutes valeurs propres --------------*/
	
	/*Matrix M = newMatrix(2, 2);
	setElt(M, 0, 0, 11);
	setElt(M, 0, 1, -18);
	setElt(M, 1, 0, 6);
	setElt(M, 1, 1, -10);
	
	Matrix vp = newMatrix(1, 2);
	Matrix P = valeurs_propres(M, vp);
	
	printf("Valeurs propres : ");	// Resultat attendu : [ 2 -1 ]
	displayMatrix(vp);
	printf("associées aux vecteurs propres (en colonnes) :\n"); // Resultat attendu : 	[ 1 3 ]
	displayMatrix(P);											//	(ou equivalent)		[ 2 2 ]	
	
	deleteMatrix(M);
	deleteMatrix(vp);
	deleteMatrix(P);*/
	
	
	/**--- TEST Estimation de la droite des moindres carrés ---*/
	
	/*Matrix Obs = newMatrix(5, 2);
	setElt(Obs, 0, 0, 1); setElt(Obs, 1, 0, 2); setElt(Obs, 2, 0, 3); setElt(Obs, 3, 0, 4); setElt(Obs, 4, 0, 5);	// Entrées
	setElt(Obs, 0, 1, 2); setElt(Obs, 1, 1, 2); setElt(Obs, 2, 1, 3); setElt(Obs, 3, 1, 2);	setElt(Obs, 4, 1, 4); 	// Sorties
	displayMatrix(Obs);
	
	Matrix Residu = newMatrix(5, 1);
	
	Matrix x = least_estimation(Obs, Residu);
	displayMatrix(x);		// Résultat attendu [2/5 7/5]
	displayMatrix(Residu);	// Résultat attendu [1/5 1/5 2/5 1 3/5]
	
	deleteMatrix(Obs);
	deleteMatrix(Residu);
	deleteMatrix(x);*/
	
	
	/**--- TEST Speedtests ---*/
	
	/*speedtest_add(2, 128, 2, 1);
	speedtest_sub(2, 128, 2, 1);
	speedtest_mult(2, 128, 2, 1);
	speedtest_mult_scal(2, 128, 2, 1);
	speedtest_expo(2, 128, 2, 1);
	speedtest_transpose(2, 128, 2, 1);
	speedtest_det(2, 128, 2, 1);
	speedtest_inv(2, 128, 2, 1);
	speedtest_solve(2, 128, 2, 1);
	speedtest_rank(2, 128, 2, 1);
	speedtest_valp(2, 128, 2, 1);
	speedtest_least(2, 128, 2, 1);*/
	
	printf("\n");
	return 0;
}


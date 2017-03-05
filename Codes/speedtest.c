/**
 * \file speedtest.c
 * \brief Définitions des fonctions de speedtest.
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
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "matrix.h"
#include "operations.h"

#define clk_tck CLOCKS_PER_SEC
#define output "speedtest.dat"
#define nbrGnuplotCmds 5

char *gnuplotCommands[] = {
	"set terminal png enhanced size 512,384", 
	"set title 'Temps consommé selon la taille de matrice'",
	"set ylabel 'Temps (s)'",
	"set xlabel 'Taille de matrice (nxn)'",
	"set key top left"
};

void speedtest_add(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, B, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		B = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = addition(A, B);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(B);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_addition.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'addition'");
	
	fclose(plot);
}


void speedtest_sub(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, B, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		B = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = soustraction(A, B);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(B);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_sub.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'sub'");
	
	fclose(plot);
}


void speedtest_mult(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, B, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		B = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = multiplication(A, B);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(B);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_mult.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'mult'");
	
	fclose(plot);
}


void speedtest_mult_scal(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, R;
	E k;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		k = frand_a_b(0, 10);
		
		t1 = clock();
		R = multScalaire(k, A);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_mult_scal.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'mult_scal'");
	
	fclose(plot);
}


void speedtest_expo(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = expo(A, 3);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_expo.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'expo (n=3)'");
	
	fclose(plot);
}


void speedtest_transpose(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = transpose(A);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_transpose.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'transpose'");
	
	fclose(plot);
}


void speedtest_det(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		determinant(A);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_determinant.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'determinant'");
	
	fclose(plot);
}


void speedtest_inv(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = inverse(A);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_invert.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'invert'");
	
	fclose(plot);
}


void speedtest_solve(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, B, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		B = aleatoire(taille, 1, 0, 10);
		
		t1 = clock();
		R = solve_gauss(A, B);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(B);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_solve.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'solve'");
	
	fclose(plot);
}


void speedtest_rank(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		rank(A);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_rank.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'rank'");
	
	fclose(plot);
}


void speedtest_valp(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, R;
	E mu;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, taille, 0, 10);
		
		t1 = clock();
		R = approx_val_propre_dominante(A, &mu);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_valeur_propre.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'val_propre'");
	
	fclose(plot);
}


void speedtest_least(int taille_min, int taille_max, int pas, int nb_sec)
{	
	clock_t t1, t2;
	double tps;
	Matrix A, B, R;
	int taille = taille_min;
	FILE *plot = popen("gnuplot", "w");
	FILE *file = fopen(output, "w");
	
	while(taille <= taille_max){
		A = aleatoire(taille, 2, 0, 10);
		B = newMatrix(taille, 1);
		
		t1 = clock();
		R = least_estimation(A, B);
		t2 = clock();
		
		tps = (double)(t2-t1)/(double)clk_tck;
		
		deleteMatrix(A);
		deleteMatrix(B);
		deleteMatrix(R);

		fprintf(file, "%d %lf\n", taille, tps);
		
		if(tps > (double) nb_sec){
			break;
		}
		taille += pas;
	}
	
	fclose(file);
	
	int i;
	for(i=0; i<nbrGnuplotCmds; i++){
		if(i == 1)
			fprintf(plot, "set output 'speedtest_least_estimate.png'\n");
		fprintf(plot, "%s\n", gnuplotCommands[i]);
	}
	fprintf(plot, "plot 'speedtest.dat' title 'least_estimate'");
	
	fclose(plot);
}

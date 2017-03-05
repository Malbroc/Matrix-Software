/**
 * \file speedtest.h
 * \brief Déclarations des fonctions de speedtest associées aux 
 * opérations algébriques sur les matrices.
 * \author LAMBRECHT Louis, GENET Martin
 * \date 25 Avril 2016
 *
 * Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
 *
 */
 
#ifndef __SPEEDTEST_H_
#define __SPEEDTEST_H_

void speedtest_add(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_sub(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_mult(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_mult_scal(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_expo(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_transpose(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_det(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_inv(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_solve(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_rank(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_valp(int taille_min, int taille_max, int pas, int nb_sec);
void speedtest_least(int taille_min, int taille_max, int pas, int nb_sec);

#endif

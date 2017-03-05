##
# Projet d'Algèbre Linéaire Appliquée - CMI Informatique L2S4 2016
#
# GENET Martin & LAMBRECHT Louis
#
# Ce Makefile compile l'exécutable par défaut. La cible clean supprime
# l'exécutable et les fichiers objets. La variable CFLAGS définit les
# options de compilation (pour gcc -c) et la variable LFLAGS définit 
# les options d'édition des liens et de production de l'exécutable
# (pour gcc -o).
##

CFLAGS = -Wall
LFLAGS = -lm -g

all : testMatrix minicas


# Cibles exec

minicas : minicas.o matrix.o variable.o operations.o speedtest.o
	gcc -o $@ $^ $(LFLAGS)

testMatrix : testMatrix.o matrix.o operations.o speedtest.o
	gcc -o $@ $^ $(LFLAGS)


# Cibles tests

test : minicas
	./minicas EntryTest

test_mem : minicas
	valgrind ./minicas EntryTest


# Cibles obj

minicas.o : minicas.c
	gcc -c $< $(CFLAGS)

variable.o : variable.c variable.h
	gcc -c $< $(CFLAGS)
	
testMatrix.o : testMatrix.c
	gcc -c $< $(CFLAGS)
	
matrix.o : matrix.c matrix.h
	gcc -c $< $(CFLAGS)
	
operations.o : operations.c operations.h
	gcc -c $< $(CFLAGS)

speedtest.o : speedtest.c speedtest.h
	gcc -c $< $(CFLAGS)


# Cibles utilitaires

clean_speedtest :
	rm speedtest*.png speedtest.dat

clean :
	rm testMatrix minicas *.o 

archive : 
	tar -cvzf genet_martin_lambrecht_louis.tar.gz readme.txt matrix.h matrix.c operations.h operations.c variable.h variable.c speedtest.h speedtest.c minicas.c Makefile testMatrix.c EntryTest

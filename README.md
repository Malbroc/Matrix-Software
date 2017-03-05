# Matrix-Software

GENET Martin et LAMBRECHT Louis
Projet d'Algèbre Linéaire Appliquée, L2S4 Informatique

Vous trouverez dans ce dossier les fichiers de code source matrix.h,
matrix.c, operations.h, operations.c, speedtest.h, speedtest.c, 
variable.h, variable.c, et minicas.c qui servent à produire l'exécutable
minicas.
Une brève description de chaque fichier est disponible en en-tête.
Un fichier testMatrix.c permet de produire un exécutable contenant différents
tests d'opérations algébriques (commentés par défaut, dé-commenter une section
de code pour faire le test indiqué).

La commande './minicas' lance l'exécutable en mode intéractif. Tapez 'help' une
fois le programme lancé pour avoir une liste des commandes disponibles.
La commande './minicas [fichier]' permet d'exécuter minicas avec les commandes
contenues dans le fichier. Les lignes précédées d'un caractère '#' produisent un
affichage dans la console. Un exemple de fichier 'EntryTest' est fourni.

Le makefile fourni, par défaut, compile tous les exécutables. Des commandes supplémentaires sont disponibles permettant notamment de lancer un test 
('make test') en mode fichier (avec 'EntryTest') ainsi que le même test
 avec un test de mémoire ('make test_mem').

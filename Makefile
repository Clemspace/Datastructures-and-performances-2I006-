all: Game_SortingRobot Checker_SortingRobot main

main.o : main.c exo.h
	gcc -c main.c

exo.o: exo.c exo.h Grille.h Solution.h API_AffGrille.h
	gcc -c -lm exo.c	

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c

API_AffGrille.o: API_AffGrille.c API_AffGrille.h Grille.h
	gcc -c API_AffGrille.c

Game_SortingRobot.o: Game_SortingRobot.c Grille.h API_AffGrille.h Solution.h 
	gcc -c Game_SortingRobot.c 

main : main.o exo.o Grille.o API_AffGrille.o Solution.o entree_sortie.o
	gcc -o  main main.o exo.o Solution.o Grille.o API_AffGrille.o entree_sortie.o -lSDL -lm
	
Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Game_SortingRobot Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

Checker_SortingRobot.o: Checker_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Checker_SortingRobot.c

Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

clean:
	rm -f *.o *.sol Game_SortingRobot Checker_SortingRobot main
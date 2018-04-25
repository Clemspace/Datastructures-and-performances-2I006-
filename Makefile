

CC = gcc
CFLAGS = -W -ggdb -g
LDFLAGS= -lSDL -lm
EXEC= Game_SortingRobot Checker_SortingRobot main main2 main3 main4 main_console Graphe
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)




all: $(EXEC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

Graphe : mainGraphe.o Circuit.o Graphe.o ListeDC.o API_AffGrille.o exo.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)
main_console : main_console.o exo.o LDC.o exo4.o API_AffGrille.o Grille.o Solution.o entree_sortie.o 
	$(CC) -o $@ $^ $(LDFLAGS)

main4: main4.o exo4.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o 
	$(CC) -o $@ $^ $(LDFLAGS)

main3: main3.o LDC.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o 
	$(CC) -o $@ $^ $(LDFLAGS)

main2 : main2.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)

main : main.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)


	
Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)


Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *.sol $(EXEC)

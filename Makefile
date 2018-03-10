

CC = gcc
CFLAGS = -W -ggdb
LDFLAGS= -lSDL -lm
EXEC= Game_SortingRobot Checker_SortingRobot main main3
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)




all: $(EXEC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

main3: main3.o LDC.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o 
	$(CC) -o $@ $^ $(LDFLAGS)


main : main.o exo.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)


Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o  $(EXEC)
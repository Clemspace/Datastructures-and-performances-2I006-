#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"

void algorithme_naif(Grille *G, Solution *S);

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l);

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

int Case_est_Noire(Grille * G, int i, int j);


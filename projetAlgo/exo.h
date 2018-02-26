#ifndef __EXO__
#define __EXO__

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"



void PlusCourtChemin(Solution *S, int i, int j, int k,int l);

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l);

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

int Case_est_Noire(Grille * G, int i, int j);

void algorithme_naif(Grille *G, Solution *S);



#endif

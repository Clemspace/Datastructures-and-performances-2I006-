#ifndef __EXO__
#define __EXO__

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include<math.h>



void PlusCourtChemin(Solution *S, int  i, int j, int k,int l);

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l);

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l);

int Case_est_Noire(Grille * G, int i, int j);//retourne 1 si la case est noire, 0 sinon;

void algorithme_naif(Grille *G, Solution *S);



#endif

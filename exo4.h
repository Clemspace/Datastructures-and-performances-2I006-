#ifndef _EXO4_
#define _EXO4_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "exo.h"


typedef struct s_avlEqui{
  int entier;
  int hauteur;

  struct s_avlEqui * fd;
  struct s_avlEqui * fg;
}AVL;



AVL*** initTab(Grille *G);

int* trouverJALV(Grille* G, int c);

AVL *** tableauCI(Grille * G);

int j_plus_proche(Grille * G,AVL *arb, int j);

void case_plus_proche_c(Grille * G, AVL *** M, int c, int i, int j , int *k, int *l); //cherche la case la plus proche de (i,j) qui possede une piece de couleur c et on met dans (k,l)


void algorithme_AVL(Grille *G, Solution *S);





/*fonctions utiles pour manipuler les AVL*/

AVL* creeN(int val,AVL* fd,AVL*fg);//creer un noeud 

int hauteur(AVL * a);//return hauteur

void majHauteur(AVL* a);//mise a jour du hauteur

void rotDroite(AVL ** ab);//rotation droite

void rotGauche(AVL ** ab);//rotation gauche

AVL* inserer_sans_equi(AVL * b, int val);//inserer element sans equilibre

AVL* inserer_avec_equi(AVL* ab, int val);//inserer element avec equilibre

#endif


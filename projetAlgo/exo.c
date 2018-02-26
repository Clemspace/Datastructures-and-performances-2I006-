#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "exo_1.h"

void algorithme_naif(Grille *G, Solution *S){/*pour chaque case, on recherche ,si elleCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
       											return RechercheCeCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
      												 return RechercheCe n'est pas noire, 
												la pièce de la même couleur la plus proche,  */

	if(G->cptr_noire == G->n*G->m){//si toutes les cases sont noires, le problème est résolu
		
		return;
	}
	for (int i = 0; i < G->m; ++i) //parcours du Tableau de cases
	{
		for (int j = 0; i < G->n; ++j)
		{
			if(G->cptr_noire == G->n*G->m){//si toutes les cases sont noires, le problème est résolu
		
				return;
			}
			else if(Case_est_Noire(G, i, j)==0){ //Si la case n'est pas noire, et contient une pièce, place le robot qui prend la pièce
				int k = i;
				int l = j;

				PlusCourtChemin(S, G->i->jr, k, l);//met le robot sur la case qui nous intéresse et cherche la case 
				changement_Case(G, i, j);
				swap_case(G); //prend la pièce sur la case
				int c = G->T[i][j].;
				Case * cible = RechercheCeCaseNaif_c(G, c, i, j, &k, &l);

				PlusCourtChemin(S, i, j, k, l);
				changement_Case(G, cible->i, cible->j);
				swap_case(G);
				G->cptr_noire++;
				
			}

		}
		
	}
}

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l){
  
  if( *k<0 || *k>G->n || *l<0 || *l>G->m ) exit(0);//on a dépassé la matrice

  else if( c==G->T[*k][*l].fond && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) est de la même couleur que c, et n'est pas noire
    return;
  } 
  else{return RechercheCaseNaif_c(G, c, i, j, k-1, l);//récursion à gauche
       return RechercheCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
       return RechercheCaseNaif_c(G, c, i, j, k+1, l);//récursion à droite
       return RechercheCaseNaif_c(G, c, i, j, k, l+1);//récursion en bas
            }
}

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){

  if( *k<0 || *k>G->n || *l<0 || *l>G->m ) exit(0);//on a dépassé la matrice

  else if( G->T[*k][*l].piece >=0 && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) contient une pièce et n'est pas noire
    
    return;
  } 
  else{return RechercheCaseNaif_nn(G, i, j, k-1, l);//récursion à gauche
       return RechercheCaseNaif_nn(G, i, j, k, l-1);//récursion en haut
       return RechercheCaseNaif_nn(G, i, j, k+1, l);//récursion à droite
       return RechercheCaseNaif_nn(G, i, j, k, l+1);//récursion en bas
            }

}

int Case_est_Noire(Grille * G, int i, int j){
  if(G->T[i][j].fond ==G->T[i][j].piece){
    return 1;
  }
  else return 0;
}


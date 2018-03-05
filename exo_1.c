#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"

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


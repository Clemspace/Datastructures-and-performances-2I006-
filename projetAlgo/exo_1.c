#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"

void algorithme_naif(Grille *G, Solution *S){/*pour chaque case, on recherche ,si elle n'est pas noire, 
												la pièce de la même couleur la plus proche,  */

	if{G->cptr_noire == G->n*G->m}{//si toutes les cases sont noires, le problème est résolu
		return;
	}
	for (int i = 0; i < G->m; ++i) //parcours du Tableau de cases
	{
		for (int j = 0; i < G->n; ++j)
		{
			if(Case_est_Noire(G, i, j)==0){ //Si la case n'est pas noire
				
			}
		}
		/* code */
	}
}

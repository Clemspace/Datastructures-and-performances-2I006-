#include<stdlib.h>
#include<stdio.h>
#include "Circuit.h"


void Graphe_Rech_Circuit(Graphe *H){
	int parcours = 0;
	int i,j,k,l,cpt;
	Lcircuit * liste;
	
	//boucle utile pour qu'on initialise parcouru aux nombres de cases noires de la grille

	for(i = 0;i<H->m;i++){
		for (j = 0; j < H->n;j++){

			if (H->Tsom[i][j]->Lsucc==NULL){

				parcouru++;
				H->Tsom[i][j]->parcouru = -2;

			}

		}
	}
	Lcircuit_init(liste);


	while (parcours<H->m*H->n){ // tant que les cases n'ont pas été toutes visitées
	
		Cell_circuit * circuit = CC_Init(NULL, NULL,NULL);

		int cpt = 0;


		Find_unvisited(H, &k, &l); //trouve une case non visitée

		Find_Circuit_rec(&H,circuit,H->Tsom[k][l],k,l,&cpt); //trouve un circuit a partir de la case trouvée précedemment 

		parcours+= cpt;

		Lcircuit_tail_insert(liste, circuit);

	}
}


void Find_unvisited(Graphe *H, int* k, int* l){
 	
 	int i,j;
	for(i = 0;i<H->m;i++){ //parcours la matrice de sommets et donne les coordonnes de la premiere case non visite et non noire
		for (j = 0; j < H->n;j++){

			if (H->Tsom[i][j]->visit==-1){
				*k = i;
				*l = j;
				return;
			}

		}
	}
	return;
}

void Find_Circuit_rec(Graphe * H,Cell_circuit * cell, Sommet* sommrec, int k, int l, int  * cpt){
	int i, j;
	cible->visit = 0;

	LDCInsererEnTete(cell->LDC, somrec->i, somrec->j);


	if(somrec->i!=k && somrec->j!= l){//on est alors retourné a l'origine, on termine
		return;
	}


	Sommet * cible = H->Tsom[i][j]->Lsucc->succ; //cible devient le premier sommet du premier arc
	Find_Circuit_rec(H, cible, k,l, cpt+1);
	
}


Cell_circuit *  CC_Init(LDC * L, int jmin, int jmax){

	Cell_circuit * cell = malloc(sizeof(Cell_circuit));
	cell-> L = L;
	cell->jmin = jmin;
	cell->jmax = jmax;
	cell->suiv = NULL;

	return cell;
}


void LCircuit_Init(Lcircuit * circuit){

	circuit->premier = NULL;
	circuit->dernier = NULL;
	circuit->nb_circuit = 0;
	return;
}

void Lcircuit_head_insert(Lcircuit * circuit, Cell_circuit * cell){
	
  	cell->prec=NULL;
  	if (LDCVide(ldc)) 
    	ldc->dernier=nouv;
  	else 
    	ldc->premier->prec=nouv;
  	nouv->suiv=ldc->premier;
  	ldc->premier=nouv;

}

void Lcircuit_tail_insert(Lcircuit * circuit, Cell_circuit * cell);

void Lcircuit_display(Lcircuit * circuit);

void Lcircuit_free(Lcircuit * circuit);

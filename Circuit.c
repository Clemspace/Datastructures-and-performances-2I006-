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

				parcours++;
				H->Tsom[i][j]->visit = -2;

			}

		}
	}
	LCircuit_Init(liste);


	while (parcours < H->m*H->n){ // tant que les cases n'ont pas été toutes visitées
	
		Cell_circuit * circuit = CC_Init(NULL, 0, 0);

		int cpt = 0;


		Find_unvisited(H, &k, &l); //trouve une case non visitée

		Find_Circuit_rec(H,circuit,H->Tsom[k][l],k,l,&cpt); //trouve un circuit a partir de la case trouvée précedemment 

		parcours+= cpt;

		Lcircuit_tail_insert(liste, circuit);

	}
	Lcircuit_display(liste);
	return;
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
	int i = sommrec->i; 
	int j = sommrec->j;
	sommrec->visit = 0;

	LDCInsererEnTete(cell->L, i,j);


	if(i==k && j==l){//on est alors retourné a l'origine, on termine
		return;
	}


	Sommet * cible = H->Tsom[i][j]->Lsucc->succ; //cible devient le premier sommet du premier arc
	Find_Circuit_rec(H,cell, cible, k,l, cpt+1);
	
}


Cell_circuit *  CC_Init(LDC * L, int jmin, int jmax){

	Cell_circuit * cell = malloc(sizeof(Cell_circuit));
	cell-> L = L;
	cell->jmin = jmin;
	cell->jmax = jmax;
	cell->suiv = NULL;
	cell->prec = NULL;

	return cell;
}


void LCircuit_Init(Lcircuit * circuit){

	circuit->premier = NULL;
	circuit->dernier = NULL;
	circuit->nb_circuit = 0;
	return;
}

int LCVide(Lcircuit * circuit){

	return (circuit->premier==NULL);
}

void Lcircuit_head_insert(Lcircuit * circuit, Cell_circuit * nouv){
	
  	nouv->prec=NULL;
  	if (LCVide(circuit)) 
    	circuit->dernier=nouv;
  	else 
    	circuit->premier->prec=nouv;
  	nouv->suiv=circuit->premier;
  	circuit->premier=nouv;

}

void Lcircuit_tail_insert(Lcircuit * circuit, Cell_circuit * nouv){

  nouv->prec=circuit->dernier;
  if (LCVide(circuit)) 
    circuit->premier=nouv;
  else 
    circuit->dernier->suiv=nouv;
  nouv->suiv=NULL;
  circuit->dernier=nouv;

}

void Lcircuit_display(Lcircuit * circuit){
	printf("Liste des circuits : ");
  Cell_circuit* cour= circuit->premier;
  while(cour != NULL) {
    printf("Circuit: %d %d ", cour->jmin, cour->jmax);
    LDCafficher(cour->L);
    cour=cour->suiv;
  }
  printf("\n");
}

void Lcircuit_free(Lcircuit * circuit);

void Cell_circuit_free(Lcircuit * circuit, Cell_circuit * c){

	Cell_circuit * precC=c->prec;
	Cell_circuit * suivC=c->suiv;

	if (precC==NULL) 
	    circuit->premier=suivC;
	else 
	    precC->suiv=suivC;
	if (suivC==NULL) 
	    circuit->dernier=precC;
	else 
		suivC->prec=precC;
	Cell_free(c);
}

void Cell_free(Cell_circuit * c){
	LDCdesalloue(c->L);
	free(c);
}


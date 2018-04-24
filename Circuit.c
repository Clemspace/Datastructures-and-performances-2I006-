#include<stdlib.h>
#include<stdio.h>
#include "Circuit.h"


Lcircuit * Graphe_Rech_Circuit(Graphe *H){
	
	int parcours = 0;
	int i,j;
	int cpt;
	int k,l;
	Lcircuit * liste = 	LCircuit_Init();

	//boucle utile pour qu'on initialise parcouru aux nombres de cases noires de la grille
	for(i = 0;i<H->m;i++){
		for (j = 0; j < H->n;j++){

			if (H->Tsom[i][j]->Lsucc==NULL){

				parcours++;
				H->Tsom[i][j]->visit=-2;

			}

		}
	}



	while(parcours != H->m*H->n){ // tant que les cases n'ont pas été toutes visitées

		cpt = 0;

		Cell_circuit * circuit = CC_Init(0,0);

		Find_unvisited(H, &k, &l); //trouve une case non visitée
		Sommet * sommet = H->Tsom[k][l];//on se place sur une case non noire non visitée

		//Find_Circuit_rec(H,circuit,H->Tsom[k][l],k,l,&cpt); //trouve un circuit a partir de la case trouvée précedemment 
		circuit = Find_Circuit_ite(H,sommet, &cpt);


		Lcircuit_tail_insert(liste, circuit);

		parcours+= cpt;

	}
	Lcircuit_display(liste);
	return liste;
}


void Find_unvisited(Graphe *H, int* k, int* l){ //fonction a améliorer eventuellement pour le nombre de pas
 	
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

	Sommet * cible = H->Tsom[i][j]->Lsucc->succ;
	
	if(cible->visit ==0){//on est alors retourné a l'origine, on termine
		return;
	} //cible devient le premier sommet du premier arc
	*cpt+1;
	Find_Circuit_rec(H,cell, cible, k,l, cpt);
	
}

Cell_circuit * Find_Circuit_ite(Graphe * H,  Sommet * sommet, int * cpt){

	Sommet * psom = sommet;

	Cell_circuit * circuit = CC_Init(0,0);

	while (psom->visit!= 0){


		LDCInsererEnFin(circuit->L, psom->i, psom->j);
		psom->visit = 0;


		psom = psom->Lsucc->succ;


		*cpt = *(cpt)+1;

	}

	LDCafficher(circuit->L);
	fprintf(stderr, "fin de circuit\n" );

	return circuit;

}
Cell_circuit *  CC_Init( int jmin, int jmax){

	Cell_circuit * cell = malloc(sizeof(Cell_circuit));
	
	cell->L = malloc(sizeof(LDC));
	cell->L->premier = NULL;
	cell->L->dernier = NULL;

	//LDCInitialise(cell->L); //le malloc fait marcher mais n'est pas propre, a corriger (voir 3 lignes au dessus)
	cell->jmin = jmin;
	cell->jmax = jmax;
	cell->suiv = NULL;
	cell->prec = NULL;
	return cell;
}


Lcircuit* LCircuit_Init(){
	
	Lcircuit* circuit = malloc(sizeof(Lcircuit));
	circuit->premier = NULL;
	circuit->dernier = NULL;
	circuit->nb_circuit = 0;

	return circuit;
}

int LCVide(Lcircuit * circuit){

	return (circuit->premier==NULL ||circuit->premier==NULL);
}

void Lcircuit_head_insert(Lcircuit * circuit, Cell_circuit * nouv){
	
  	nouv->prec=NULL;
  	if (LCVide(circuit)) 
    	circuit->dernier=nouv;
  	else 
    	circuit->premier->prec=nouv;
  	nouv->suiv=circuit->premier;
  	circuit->premier=nouv;
  	circuit->nb_circuit++;

}

void Lcircuit_tail_insert(Lcircuit * circuit, Cell_circuit * nouv){

	fprintf(stderr, "etat des pointeurs insertion queue LC (%p, %p), (%p,%p)\n",circuit->premier, circuit->dernier, nouv->L->premier, nouv->L->dernier);
  nouv->prec=circuit->dernier;
  if (LCVide(circuit)) 
    circuit->premier=nouv;
  else 
    circuit->dernier->suiv=nouv;
  nouv->suiv=NULL;
  circuit->dernier=nouv;
  circuit->nb_circuit++;
  return;


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


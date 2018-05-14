#include<stdlib.h>
#include<stdio.h>
#include "Circuit.h"


//void Graphe_Rech_Circuit(Graphe *H, Lcircuit * LC){}

Lcircuit * Graphe_Rech_Circuit(Graphe *H){ //retourne une liste de circuits couvrants de la grille et du graphe
	
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

	Cell_circuit * circuit = CC_Init(H->n,0);

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

void Write_Lcircuit(Lcircuit * circuit, Solution * S){

	//D'abord, on parcourt la distance entre (0,0) et le premier sommet du premier circuit.
	int i=0,j=0;
	Cell_circuit * pc = circuit->premier;
	
	if(circuit->premier->L->premier->i!=0||circuit->premier->L->premier->j!=0){
		PlusCourtChemin(S,i,j,circuit->premier->L->premier->i,circuit->premier->L->premier->j);
	}


	//Puis on parcourt la liste, en n'oubliant pas d'écrire les changements pour passer d'un circuit à l'autre.
	
	while(pc!=circuit->dernier){

		fprintf(stderr, "WhileLC\n" );
		Ajout_action(S,'S');

		Write_LDC(pc->L, S);
		PlusCourtChemin(S,pc->L->premier->i,pc->L->premier->j,pc->suiv->L->premier->i,pc->suiv->L->premier->j); //passe d'un circuit a l'autre

		pc = pc->suiv;

	}

	Ajout_action(S,'S');
	Write_LDC(circuit->dernier->L, S);

	return;

}

void Write_LDC(LDC * L, Solution * S){

	//On parcourt toute la liste et on écrit les déplacements entre deux cellules de la première a la dernière
	int i,j,k,l;
	CelluleLDC * pl = L->premier;
	
	while(pl->suiv){
		
		fprintf(stderr, "whileWLDC\n" );
		i = pl->i;
		j = pl->j;
		k = pl->suiv->i;
		l = pl->suiv->j;

		PlusCourtChemin(S, i,j,k,l);
		Ajout_action(S,'S');
		pl = pl->suiv;
	} 

	PlusCourtChemin(S, L->dernier->i, L->dernier->j, L->premier->i, L->premier->j);//Pour retourner sur la case d'origine
	Ajout_action(S,'S');

	return;
}

void CalculJminJmax(Lcircuit *LC){ //cette fonction va parcourir les circuits, initialiser les bonnes valeurs de jmax et jmin pour chaque circuit, et les trier dans l'ordre croissant des jmin dans LC


	Cell_circuit * pc = LC->premier;

	while(pc!=LC->dernier){

		SetJminmax(pc);

		pc = pc->suiv;
	}

	//maintenant, on trie les circuits et on les mets dans l'ordre dans LC

	int jmin = pc->L->jmin;
	return;



}
void SetJminmax(Cell_circuit * pc){ //on parcourt le circuit, et on actualise les valeurs de jmin et jmax au fur et a mesure du parcours

	Cell_circuit * pl = pc->L->premier;


	while(pl->suiv){

		if(pl->j > pc->jmax){
			pc->jmax = pl->j;
		}

		if(pl->j< pc->jmin){
			pc->jmin = pl->j;
		}
		
		pl = pl->suiv;

	}

	return;





}

void algorithme_circuit_CasLigne1x1(Grille *G, Solution *S){

	if(G.m !=1){
		printf("Poblème sur le format de la Grille: ce n'est pas un vecteur!\n");
		return;
	}
	int i, jDroite, flag, jDroiteSav;
	Graphe *H;
	Graphe_init(H,G.m, G.n);
	Graphe_creation(G, H); //crée le graphe associé a la grille

	Lcircuit * Lcirc = Graphe_Rech_Circuit(H); //crée la liste des circuits du graphe


	CalculJminJmax(Lcirc); //met a jour les jmin et jmax de chaque circuit

	Solution_init(S); //Initialise la solution

	Cell_Char * Tref = G.n* malloc(sizeof(Cell_Char)); //tableau de pointeurs vers soluton Tref avec cases initialisées a NULL
	for (i = 0; i < G.n; i++)
	{
		Tref[i] = NULL;
	}

	jDroite = 0;
	flag = 0;
	Circuit  * pcirc = Lcirc->premier;

	for (i = 0; i < Lcirc->nb_circuit; i++){ //pour chaque circuit dans l'ordre des jmin croissants

		if(Tref[pcirc->jmin]==NULL){
			flag = 1;
			jDroiteSav = jDroite;

		}

	}
	





}





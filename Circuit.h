#ifndef _CIRCUIT_H_
#define _CIRCUIT_H_

#include "ListeDC.h"
#include "Graphe.h"
#include "Solution.h"
#include "Grille.h"
#include "exo.h"


typedef struct cell_circuit{
	LDC * L; //pointeur sur la liste des sommets du circuit considéré
	
	int jmin , jmax;
	struct cell_circuit *prec;
	struct cell_circuit *suiv;
}Cell_circuit;

typedef struct{
	int nb_circuit;
	Cell_circuit *premier;
	Cell_circuit *dernier;
}Lcircuit;

//void Graphe_Rech_Circuit(Graphe *H, Lcircuit * LC);


Lcircuit *  Graphe_Rech_Circuit(Graphe *H);

void Find_unvisited(Graphe *H, int* k, int* l);

void Find_Circuit_rec(Graphe * H,Cell_circuit * cell, Sommet * sommet,int k, int l, int  * cpt); //trouve un circuit a partir de la case de cordonnees (k,l), et change les champs visité des sommets visites
														 //on commencera par visiter le premier arc jusqu'a retourner sur la case d'origine.

Cell_circuit * Find_Circuit_ite(Graphe * H, Sommet * sommet, int * cpt);


Cell_circuit *  CC_Init(int jmin, int jmax);


Lcircuit * LCircuit_Init();

void Lcircuit_head_insert(Lcircuit * circuit, Cell_circuit * cell);

void Lcircuit_tail_insert(Lcircuit * circuit, Cell_circuit * cell);

void Lcircuit_display(Lcircuit * circuit);

void Lcircuit_free(Lcircuit * circuit);

int LCVide(Lcircuit * circuit);

void Cell_circuit_free(Lcircuit * circuit, Cell_circuit * nouv);

void Cell_free(Cell_circuit * c);

void Write_Lcircuit(Lcircuit * circuit, Solution * S); //fonction qui prend une Lcircuit, et qui retourne le chemin pour la parcourir dans l'ordre.

void Write_LDC(LDC * l, Solution * S);

#endif
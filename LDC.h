#ifndef _LDC_
#define _LDC_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Grille.h"
#include "exo.h"



typedef struct celluleLDC{

int i,j;
struct celluleLDC* prec;	/* pointeur sur l’element precedent de la liste */
struct celluleLDC* suiv;	/* pointeur sur l’element suivant de la liste */

}CelluleLDC;


typedef struct{

CelluleLDC * premier;	/* Pointeur sur element en tete */
CelluleLDC * dernier;	/* Pointeur sur element en fin */

}LDC;

typedef struct {
	
	LDC * TC; 			//Tableau de Listes cirulaires
	int nbcoul;		// nb de couleurs dans la grille et de cases de la table de hachage;

}HashTable;

CelluleLDC* creerCellule(int i, int j);	// qui alloue et retourne une cellule

void LDCInitialise(LDC * ldc);	// qui initialise une liste

int LDCVide(LDC * ldc);	// qui teste si la liste est vide, retourne 1 si vide 0 sinon

void LDCInsererEnFin(LDC * ldc , int i,int j);	//qui insere une nouvelle cellule en fin

void LDCenleverCellule(LDC * ldc , CelluleLDC * cel);	// qui supprime une cellule a partir d un pointeur sur la cellule

void LDCafficher(LDC * ldc);		// un affichage en cas de besoin pour debugage

void LDCdesalloue(LDC * ldc);	// qui desalloue toute la liste (si elle n est pas vide a la fin)

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j);

int FHachage(Grille *G, int i, int j);

HashTable * HashTableInitialise(Grille * G);

void algorithme_parcouleur(Grille *G, Solution *S);

/*remarque d'optimisation :
						   	-On peut essayer de supprimer les cases noires au fur et a mesure du traitement de la résolution
						   	de la grille, en n'ajoutant que les cases non noires dans la table de hachage initialement(FAIT), et 
						   	en supprimant les cases devenues noires(A FAIRE)

						   	-Penser a la gestion, libération de mémoire,minimiser les fuites au maximum
						   */




#endif

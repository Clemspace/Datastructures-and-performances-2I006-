#include "LDC.h"



CelluleLDC* creerCellule(int i, int j){	// qui alloue et retourne une cellule
	CelluleLDC * Cell = malloc(sizeof(CelluleLDC));
	Cell->i = i;
	Cell->j = j;
	Cell->prec = NULL;
	Cell->suiv = NULL;
	return Cell;
}

void LDCInitialise(LDC *ldc){// qui initialise une liste
	ldc->premier = NULL;
	ldc->dernier = NULL;
	return;
}
int LDCVide(LDC* ldc){	// qui teste si la liste est vide, retourne 1 si vide, 0 sinon
	return ldc->premier == NULL ?  0 : 1;
}


void LDCInsererEnFin(LDC* ldc , int i,int j){	//qui insere une nouvelle cellule en fin
	if(LDCVide(ldc)){ //on aura alors une liste circulaire d'un élément
		CelluleLDC * Cell = creerCellule(i,j);
		ldc->premier = Cell;
		ldc->dernier = Cell;
		return;
	}
	else{ //on change le dernier élément et tous les pointeurs associés
		CelluleLDC * Cell = creerCellule(i,j);
		ldc->dernier->suiv = Cell;
		ldc->dernier = Cell;
		return;
	}

}

void LDCenleverCellule(LDC* ldc , CelluleLDC * cel){// qui supprime une cellule a partir d un pointeur sur la cellule
	
	if(cel->prec==NULL){
		
		cel->prec->suiv = NULL;
		ldc->premier->prec =ldc->dernier; 
		ldc->dernier = cel->prec;
		free(cel);
	}
	else if(cel->suiv ==NULL){
		
		cel->suiv->prec = NULL;
		ldc->dernier->suiv =ldc->premier; 
		ldc->premier = cel->suiv;
		free(cel);

	}
	else{

		cel->suiv->prec = cel->prec;
		cel->prec->suiv =cel->suiv; 
		free(cel);


	}
}

void LDCafficher(LDC* ldc){// un affichage en cas de besoin pour debugage
	if (LDCVide(ldc)) return;
	CelluleLDC* pldc = ldc->premier;
	do
	{
		printf("coordonnees:(%d, %d)\n",pldc->i, pldc->j);

		pldc = pldc->suiv;
	}while(pldc);
	return;
}

void LDCdesalloue(LDC *ldc){// qui desalloue toute la liste (si elle n est pas vide a la fin)
	if (LDCVide(ldc)){ 

		free(ldc);
		return;
	}
	CelluleLDC* pldc = ldc->premier;
	do
	{
		LDCenleverCellule(ldc,pldc);

		pldc = pldc->suiv;
	}while(pldc);
		free(ldc->premier);
		free(ldc);
	return;

}

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j){

	CelluleLDC* pldc = ldc->premier;
	CelluleLDC* plusproche = ldc->premier;
	int min =(int) fabs(plusproche->i-i)+fabs(plusproche->j-j); // a traiter: cas où la premiere cas est celle des coordonnées données

	do{//on doit nécessairement parcourir toute la liste ici, sauf si on a trouvé un voisin direct (distance = 1)
		int distance = fabs(pldc->i-i)+fabs(pldc->j-j);
		if (distance < min && distance >0)
		{
			min = distance;
			plusproche = pldc;
		}
		if(min==1) return plusproche;
		
		pldc = pldc->suiv;

	}while(pldc);

	return plusproche;
}

int FHachage(Grille *G, int i, int j){
	return G->T[i][j].fond;
}

HashTable * HashTableInitialise(Grille * G){


	HashTable * T = malloc(sizeof(HashTable));
	T->nbcoul = G->nbcoul;
	T->TC = calloc(T->nbcoul, sizeof(LDC*));



	for (int i = 0; i < T->nbcoul; i++)
	{
		LDC * ldc = malloc(sizeof(LDC));
		fprintf(stderr, "dbg1\n"); 

		LDCInitialise(ldc);
		T->TC[i] = *ldc;

	}
		
	return T;



}


void algorithme_parcouleur(Grille *G, Solution *S){
	
	//on ajoute d'abord toutes les cases non noires dans la table de hachage
	HashTable * H=HashTableInitialise(G);

	int taille= G->m*G->n;
	int k,l;

	for (int j = 0; j < G->n; j++)//on parcourt le tableau de cases et on met dans la table de hachage les coordonnées en fonction de la couleur de leur fond
	{
		for (int i = 0; i < G->m; i++)
		{
			if (!Case_est_Noire(G,i,j))//on met les coordonnées dans la table dans la liste correspondant a sa couleur
			{
				int n = FHachage(G,i,j);
				LDCInsererEnFin(&H->TC[n],i,j);
				
			}

		}
	}

	for (int i = 0; i < H->nbcoul; i++)//on parcourt le tableau de cases et on met dans la table de hachage les coordonnées en fonction de la couleur de leur fond
	{
		LDCafficher(&H->TC[i]);
	}


	//on adapte la résolution vue précédemment pour la table de hachage
	while(G->cptr_noire<G->m*G->n){   

		if(G->T[G->ir][G->jr].robot==-1){//si le robot n'a pas de pièce


			RechercheCaseNaif_nn(G, G->ir,G->jr, &k, &l);//(k,l) a les coordonnées de la case la plus proche avec une piece
	    	PlusCourtChemin(S, G->ir, G->jr, k, l);

	    	changement_case(G, k, l);
	    	swap_case(G);Ajout_action(S,'S');
 
		}
		else{//si le robot a une pièce

	        int c = G->T[G->ir][G->jr].robot; 
	        CelluleLDC* cell = LDCrechercherPlusProcheCase(&H->TC[c], G->ir, G->jr);
	        k = cell->i;
	        l = cell->j;

	        PlusCourtChemin(S, G->ir, G->jr, k, l);
	        changement_case(G, k, l);

	        swap_case(G);Ajout_action(S,'S');
    	}
	
	}
	return;



}




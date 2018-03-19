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
	return ldc->premier == NULL;
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
		Cell->prec= ldc->dernier;
		ldc->dernier = Cell;
		return;
	}

}

void LDCenleverCellule(LDC* ldc , CelluleLDC * cel){// qui supprime une cellule a partir d un pointeur sur la cellule
	

	fprintf(stderr, "On enleve la cellule de coordonnees (%d,%d)\n",cel->i,cel->j);
	if (ldc->premier ==ldc->dernier){//si on supprime le dernier élément de la ldc
		free(cel);
		ldc->premier = NULL;
		ldc->dernier = NULL;

	}
	else if(cel->prec == NULL){// si premier elem de LDC
		
		cel->suiv->prec = NULL;
		ldc->premier = cel->suiv; 
		free(cel);
	}
	else if(cel->suiv ==NULL){ //si dernier elem de LDC
		
		cel->prec->suiv = NULL;
		ldc->dernier = cel->prec; 
		free(cel);

	}
	else{ // si ni premier ni dernier

		cel->suiv->prec = cel->prec;
		cel->prec->suiv =cel->suiv; 
		free(cel);


	}
}

void LDCafficher(LDC* ldc){// un affichage en cas de besoin pour debugage
	if (LDCVide(ldc)) return;
	CelluleLDC* pldc = ldc->premier;
	printf("|||LDC|||\n");
	do
	{ 
		
		printf("\nCoordonnees:(%d, %d)\n",pldc->i, pldc->j);

		pldc = pldc->suiv;
	}while(pldc);
	return;
}


void AfficherTable(HashTable * H){

	int i;
			printf("||||||Affichage de la Table||||||\n");

	for (i = 0; i < H->nbcoul; i++)//on parcourt le tableau de cases et on met dans la table de hachage les coordonnées en fonction de la couleur de leur fond
	{
		printf("%d ème case de la Table:\n",i);
		LDCafficher(H->TC[i]);
	}
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
 int cpt = 0;
	CelluleLDC* pldc = ldc->premier;
	CelluleLDC* plusproche =ldc->premier;
	int min =(int) fabs(plusproche->i-i)+fabs(plusproche->j-j);
	CelluleLDC * fin = ldc->dernier; 

	// a traiter: cas où la premiere cas est celle des coordonnées données
	//for ( pldc = ldc->premier; pldc != ldc->dernier; pldc = pldc->suiv ){

	do{//on doit nécessairement parcourir toute la liste ici, sauf si on a trouvé un voisin direct (distance = 1)
		
		fprintf(stderr, "%d ème case de la liste, adresse: %p, adresse dernier: %p \n",cpt, pldc, ldc->dernier);
		int distance = fabs(pldc->i-i)+fabs(pldc->j-j);
		
		if (distance >0 && distance < min )
		{
			min = distance;
			plusproche = pldc;
		}
		if(min==1) return plusproche;	
		
		pldc = pldc->suiv;
		cpt++;
	//}
	}while(pldc);
	fprintf(stderr, "fin Rppc\n");
	LDCafficher(ldc);

	return plusproche;
}

int FHachage(Grille *G, int i, int j){
	return G->T[i][j].fond;
}

HashTable * HashTableInitialise(Grille * G){
	int i;

	HashTable * T = malloc(sizeof(HashTable));
	T->nbcoul = G->nbcoul;
	T->TC = calloc(T->nbcoul, sizeof(LDC*));



	for (i = 0; i < T->nbcoul; i++)
	{
		LDC * ldc = malloc(sizeof(LDC));

		LDCInitialise(ldc);
		T->TC[i] = ldc;

	}
		
	return T;



}


void algorithme_parcouleur(Grille *G, Solution *S){
	
	//on ajoute d'abord toutes les cases non noires dans la table de hachage
	HashTable * H = HashTableInitialise(G);

	int taille= G->m*G->n;
	int i,j;
	int k = 0;
	int l = 0;

	for ( j = 0; j < G->n; j++)//on parcourt le tableau de cases et on met dans la table de hachage les coordonnées en fonction de la couleur de leur fond
	{
		for ( i = 0; i < G->m; i++)
		{
			if (!Case_est_Noire(G,i,j))//on met les coordonnées dans la table dans la liste correspondant a sa couleur
			{
				fprintf(stderr, "(%d,%d)\n",i,j);

				int n = FHachage(G,i,j);
				LDCInsererEnFin(H->TC[n],i,j);
				
			}

		}
	}
	AfficherTable(H);



	//on adapte la résolution vue précédemment pour la table de hachage
	while(G->cptr_noire<G->m*G->n){   

		if(G->T[G->ir][G->jr].robot==-1){//si le robot n'a pas de pièce
			fprintf(stderr, "DébutIF\n" );


			RechercheCaseNaif_nn(G, G->ir,G->jr, &k, &l);//(k,l) a les coordonnées de la case la plus proche avec une piece
	    	PlusCourtChemin(S, G->ir, G->jr, k, l);

	    	changement_case(G, k, l);
	    	swap_case(G);Ajout_action(S,'S');
			fprintf(stderr, "FinIF\n" );
 
		}
		else{//si le robot a une pièce
			fprintf(stderr, "DébutELSE\n" );

	        int c = G->T[G->ir][G->jr].robot; 
	        fprintf(stderr, "%d,%d\n", k,l);

	        CelluleLDC* cell = LDCrechercherPlusProcheCase(H->TC[c], G->ir, G->jr);
	        k = cell->i;
	        l = cell->j;
	        printf("(%d,%d)\n",k,l);

	        PlusCourtChemin(S, G->ir, G->jr, k, l);
	        changement_case(G, k, l);

	        swap_case(G);Ajout_action(S,'S');
	        
	        LDCenleverCellule(H->TC[c], cell);
	        LDCafficher(H->TC[c]);
	        fprintf(stderr, "FinELSE\n" );


    	}
	
	}
	return;



}




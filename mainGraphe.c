#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "exo.h"
#include "Graphe.h"
#include "ListeDC.h"
#include "Circuit.h"



int main(int argc,char**argv){

  Graphe H; 
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i,j;

  if(argc!=5){
    printf("usage: %s <nb_lignes nb_colonnes nb_couleur graine>\n",argv[0]);
    return 1;
  }

  G.m=atoi(argv[1]);
  G.n=atoi(argv[2]);
 
  if (G.m>G.n){
    printf("Il doit y avoir plus de colonnes que de lignes.\n");
    exit(1);
  }
  G.nbcoul=atoi(argv[3]);
  if (G.nbcoul>G.m*G.n){
    printf("Il ne doit pas y avoir plus de couleurs que de cases.\n");
    exit(1);
  }
  graine=atoi(argv[4]);

  /* Generation de l'instance */
  Grille_allocation(&G);
  Gene_Grille(&G,graine);
  Solution_init(&S);

/* Génération du graphe et Affichage*/

   Graphe_init(&H, G.m,G.n);
   Graphe_creation(&G, &H);
   Graphe_affiche(&H);
   
   int cas = 0; 
 
   Lcircuit* slce; 
 
   if(G.m==1){ //résolution pour un vecteur 
    cas++; 
   } 
   if (G.m*G.n==G.nbcoul){//cas une case par couleur 
    cas+=2; 
   } 
 
   switch(cas){ 
    case 3://mettre ici l'algo pour vecteur 1case/couleur 
    case 2://mettre ici l'algo pour cas 1case/couleur  
    case 1://mettre ici l'algo pour vecteur  
    case 0: slce = Graphe_Rech_Circuit(&H);//cas par défaut 
            break; 
   } 

   Write_Lcircuit(slce, &S);
   Ecriture_DisqueG(G.m, G.n, G.nbcoul, graine, &S);
   Affiche(&S);



return 0;
}

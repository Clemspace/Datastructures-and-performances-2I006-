#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"
#include "exo.h"

#include <time.h>
#include <string.h>

int main(int argc,char**argv){

 
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


  clock_t temps_init;
  clock_t temps_fin;
  double temps_cpu;
  temps_init=clock();
  temps_fin=clock();


  temps_init =clock();//temps
  algorithme_circulaire(&G, &S);//ecrit la solution dans S
  temps_fin=clock();//temps

  Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);//ficher .sol
  Affiche(&S);

   temps_cpu=( (double) (temps_fin - temps_init ) / CLOCKS_PER_SEC );

 printf ("circulaire temps = %f \n\n",temps_cpu);



return 0;}


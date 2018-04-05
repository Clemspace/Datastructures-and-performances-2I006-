#include"exo.h"
#include"LDC.h"
#include"exo4.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"


#define liste() puts("Veuillez choisir : \n \n ");	\
  puts("1. Algorithme naif \n");			\
  puts("2. Algorithme circulaire \n");			\
  puts("3. Algotithme par couleurs \n");		\
  puts("4. Algorithme par AVL \n");			\
  puts("5. Sortir du programme \n");			\



/* #define menu(choix) if(choix==1){puts( "1.Lancer l algorithme naif");\ */
/*   puts( "2.Returner");} else if (choix==2){puts( "1.Lancer l algorithme circulaire");\ */
/*     puts( "2.Returner");}else if (choix==3){puts( "1.Lancer l algorithme par couleur");\ */
/*     puts( "2.Returner");}else if (choix==4){puts( "1.Lancer l algorithme par AVL");\ */
/*     puts( "2.Returner");} */



 int main(int argc,char**argv) {

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



   
  int choix;

  do{
    liste();
    scanf("%d",&choix);

    switch(choix){


    case 1:{//algo naif
      algorithme_naif(&G, &S);//ecrit la solution dans S
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);//ficher .sol
      Affiche(&S);
      puts(" Fin algo naif\n\n");
      break;
	}

      
    case 2:{//algo circulaire
      algorithme_circulaire(&G, &S);//ecrit la solution dans S
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);//ficher .sol
      Affiche(&S);
      puts(" Fin algo circulaire\n\n");
      break;
    }


    case 3:{//algo par couleur
      algorithme_parcouleur(&G, &S);//ecrit la solution dans S
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);//ficher .sol
      Affiche(&S);
      puts(" Fin algo par couleur\n\n");
      break;
    }


    case 4:{//algo par AVL
      algorithme_AVL(&G, &S);//ecrit la solution dans S
      Ecriture_Disque(G.m, G.n, G.nbcoul, graine, &S);//ficher .sol
      Affiche(&S);
      puts(" Fin algo par AVL\n\n");
      break;
    }

    case 5:{//fin du prog
      puts(" FIN DU PROGRAMME \n\n");
      break;
    }

    default :{
      puts(" COMMANDE INCONNUE \n\n");
      break;
    }
      
    }

  }while(choix!=5);

  return 0;
 }

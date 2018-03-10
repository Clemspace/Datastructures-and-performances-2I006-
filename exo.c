#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

#include "exo.h"
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"

#define max(a,b) (a>=b?a:b)

//contient EXO 1 et 2

void algorithme_naif(Grille *G, Solution *S){/*pour chaque case, on recherche ,si elleCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
       											                  return RechercheCeCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
      												                return RechercheCe n'est pas noire, 
												                      la pièce de la même couleur la plus proche,  */
  int k = 0;
  int l = 0;
  fprintf(stderr, "dbg0\n");


  //cordonnées du robot dans (i,j)

   
  while(G->cptr_noire<G->m*G->n){   
    fprintf(stderr, "\ndebut while  %d\n", G->cptr_noire);
    int c = G->T[G->ir][G->jr].robot; 


    if(G->T[G->ir][G->jr].robot==-1){//si le robot n'a pas de pièce
      
      fprintf(stderr, "va chercher case avec piece %d COULEUR robot: %d\n", G->cptr_noire, G->T[G->ir][G->jr].robot);

      fprintf(stderr, "dbg cases_correctes %d\n", G->cptr_noire);
      fprintf(stderr, "cordonnees_robot (%d,%d)\n", G->ir,G->jr);

      RechercheCaseNaif_nn(G, G->ir,G->jr, &k, &l);//(k,l) a les coordonnées de la case la plus proche avec une piece
      PlusCourtChemin(S, G->ir, G->jr, k, l);

      changement_case(G, k, l);
     
      fprintf(stderr, "cordonnees_robotIJ (%d,%d)\n",G->ir,G->jr);

      /*if (Case_est_Noire(G,G->ir,G->jr)){
          RechercheCaseNaif_nn(G, G->ir, G->jr, &k, &l);//(k,l) a les coordonnées de la case la plus proche avec une piece
        
          changement_case(G, k, l);
          PlusCourtChemin(S, i, j, k, l);
      }*/
      swap_case(G);Ajout_action(S,'S');

      

    }
    else{//si le robot a une pièce
        
        fprintf(stderr, "VA POSER la piece\n");     
        fprintf(stderr, "dbg cases_correctes %d\n", G->cptr_noire);
        fprintf(stderr, "cordonnees_robot (%d,%d)\n", G->ir,G->jr); 
        

      
        //int c = G->T[G->ir][G->jr].robot; 
        RechercheCaseNaif_c(G, c, G->ir, G->jr, &k, &l);//recherche la case cbile, cordonnées en(k,l)
        fprintf(stderr, "main %d %d %d %d\n", G->ir,G->jr,k,l);

        PlusCourtChemin(S, G->ir, G->jr, k, l);
        changement_case(G, k, l);
        fprintf(stderr, "cordonnees_robotElse (%d,%d)\n", G->ir,G->jr); 


        swap_case(G);Ajout_action(S,'S');
      }


  }

  return;
  
} 
  

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l){
   int  x = 0;
   int y = 0;
   int distance = 0;
  int min = G->m+G->n+1;

  fprintf(stderr, "RCNC %d %d %d %d couleur a trouver %d\n", i,j,*k,*l, c);
  for (y = 0; y  < (G->n); y++) //parcours du Tableau de cases
  {
    for (x = 0; x < (G->m); x++)
    {
        fprintf(stderr, "RCNC %d %d couleur:%d \n",y,x,G->T[x][y].fond);

      distance =(int)fabs(i-x)+fabs(j-y);
 
      if ( c==G->T[x][y].fond && Case_est_Noire(G,x,y)==0 && distance < min && distance >0){
      fprintf(stderr, "RCNC_trouvé! (%d, %d) %d\n",x,y, distance);

        min =distance;
        *k= x;
        *l =y;
      } 

    }
    
  }
fprintf(stderr, "RCNC %d %d %d %d\n", i,j,*k,*l);
fprintf(stderr, "RCNCfinal %d %d \n",*k,*l);

  return; 

}

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
   int x = 0;
   int y = 0;
   int distance = 0;
   int min = G->m+G->n+1;
  fprintf(stderr, "RCNN %d %d %d %d\n", i,j,*k,*l);

  


  for (y = 0; y < (G->n); y++) //parcours du Tableau de cases
  {
    for (x = 0; x < (G->m); x++)
    {
        fprintf(stderr, "RCNN  %d %d\n",x,y );

      distance = (int)fabs(i-x)+fabs(j-y);

      if ((Case_est_Noire(G, x, y)==0)&& distance < min){
      fprintf(stderr, "RCNN_trouvé! (%d, %d) %d\n",x,y, distance);

        min = distance;
        *k=x;
        *l=y;
      } 


    }
    
  }
  return; 
}
  


int Case_est_Noire(Grille * G, int i, int j){
  if((G->T[i][j].fond ==G->T[i][j].piece)){
    return 1;
  }
  return 0;
}


void PlusCourtChemin(Solution *S, int  i, int  j, int k,int l){
  int x = (int)sqrt((k-i)*(k-i));
  int y = (int)sqrt((l-j)*(l-j));

  if(j==l && i==k ){//on est déja sur la bonne case
    return;
  }
 
  if(i!=k){
    int cpt = 0;
    if(i>k){//on doit aller a gauche 
      for(cpt = 0; cpt<x;cpt++){
        fprintf(stderr, "PCCGauche %d %d %d %d %d\n",i,j, k,l, cpt );

        Ajout_action(S,'U');
      }
    }
    if(i<k){//on doit aller a droite
      for(cpt = 0; cpt<x;cpt++){
        fprintf(stderr, "PCCDroite %d %d %d %d %d\n",i,j, k,l, cpt );


        Ajout_action(S,'D');

      }
    }

    }
    
    if(j!=l){
    int cpt2 = 0;
    
    if(j>l){//on doit aller en bas 
      for(cpt2 = 0; cpt2<y;cpt2++){
        fprintf(stderr, "PCCBas %d %d %d %d %d\n",i,j, k,l, cpt2 );


        Ajout_action(S,'L');
      }
    }

    if(j<l){//on doit aller en haut
      for(cpt2 = 0; cpt2<y;cpt2++){
        fprintf(stderr, "PCCHaut %d %d %d %d %d\n",i,j, k,l, cpt2 );


        Ajout_action(S,'R');

      }
    }

    }
  return;
}



/*EXO 2 recherche circulaire*/




void RechercheCirculaire_c(Grille * G, int c, int i, int j, int * k, int * l){

  int i2,lg,ld,r;
  int L=max( fabs( (G->n)-i ) , fabs( (G->m)-j ) );

 

  for ( r=1 ; r<=L ; r++){ //tous les valeurs possible de la case a trouver et (i,j)
  
    i2=i-r;
    lg=j;
    ld=j;

    while(i2<=i){//case a distance r de (i,j) qui sont gauche de (i,j)

      if(i2>=0 && lg>=0 && i2<(G->n) && lg<(G->m) ){//si case dans le tableau on verifie si il y a c
        if( c==G->T[i2][lg].fond && Case_est_Noire(G, i2, lg)==0){ //Si la case (i2,lg) est de la même couleur que c, et n'est pas noire
	  *k=i2;*l=lg;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }

      if(i2>=0 && ld>=0 && i2<(G->n) && ld<(G->m) ){//idem
        if( c==G->T[i2][ld].fond && Case_est_Noire(G, i2, ld)==0){
	  *k=i2;*l=ld;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }
  
      i2++;
      lg=lg-1;
      ld=ld+1;

    
    }//fin While



    
    i2=i+1;
    lg=j-L+1;
    ld=j+L-1;

    while(i2<=i+r){ //case a distance r de (i,j) qui sont droite de (i,j)
      
      if(i2>=0 && lg>=0 && i2<(G->n) && lg<(G->m) ){//si case dans le tableau on verifie si il y a c
        if( c==G->T[i2][lg].fond && Case_est_Noire(G, i2, lg)==0){ //Si la case (i2,lg) est de la même couleur que c, et n'est pas noire
	  *k=i2;*l=lg;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }

      if(i2>=0 && ld>=0 && i2<(G->n) && ld<(G->m) ){//idem
        if( c==G->T[i2][ld].fond && Case_est_Noire(G, i2, ld)==0){
	  *k=i2;*l=ld;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }
    
      i2++;
      lg=lg+1;
      ld=ld-1;

    }//Fin While
  

  }//Fin For

  //si pas trouver
  return;

}




void RechercheCirculaire_nn(Grille * G,  int i, int j, int * k, int * l){

  int i2,lg,ld,r;
  int L=max( fabs( (G->n)-i ) , fabs( (G->m)-j ) ); //plus grand valeur 

 

  for ( r=1 ; r<=L ; r++){ //tous les valeurs possible de la case a trouver et (i,j)
  
    i2=i-r;
    lg=j;
    ld=j;

    while(i2<=i){//case a distance r de (i,j) qui sont gauche de (i,j)

      if(i2>=0 && lg>=0 && i2<(G->n) && lg<(G->m) ){//si case est dans le tableau
	if( G->T[i2][lg].piece >=0 && Case_est_Noire(G, i2, lg)==0){ //Si la case (k,l) contient une pièce et n'est pas noire 
	  *k=i2;*l=lg;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }

      if(i2>=0 && ld>=0 && i2<(G->n) && ld<(G->m) ){//idem
        if(  G->T[i2][ld].piece >=0 && Case_est_Noire(G, i2, ld)==0

	    ){ 
	  *k=i2;*l=ld;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }
  
      i2++;
      lg=lg-1;
      ld=ld+1;

    
    }//fin While



    
    i2=i+1;
    lg=j-L+1;
    ld=j+L-1;

    while(i2<=i+r){ //case a distance r de (i,j) qui sont droite de (i,j)
      

      if(i2>=0 && lg>=0 && i2<(G->n) && lg<(G->m) ){//si case est dans le tableau
	if( G->T[i2][lg].piece >=0 && Case_est_Noire(G, i2, lg)==0){ //Si la case (k,l) contient une pièce et n'est pas noire 
	  *k=i2;*l=lg;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }

      if(i2>=0 && ld>=0 && i2<(G->n) && ld<(G->m) ){//idem
        if(  G->T[i2][ld].piece >=0 && Case_est_Noire(G, i2, ld)==0 ){ 
	  *k=i2;*l=ld;

	  fprintf(stderr, "trouve!\n");
	  return ;
	}
      }
    
      i2++;
      lg=lg+1;
      ld=ld-1;

    }//Fin While
  

  }//Fin For

  //si pas trouver
  return;

}


/* void RechercheCirculaire_c(Grille * G, int c, int i, int j, int * k, int * l) */
/* { */
/*   if( (*k)<0 || (*k)>(G->n) || (*l)<0 || (*l)>(G->m) ){ */

/*     return;//on a dépassé la matrice */
/*   }else if( c==G->T[*k][*l].fond && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) est de la même couleur que c, et n'est pas noire */

/*     fprintf(stderr, "trouve!\n"); */
/*     return ; */
/*   } else{ */

/*     int k2=(*k)-1; */
/*     int l2=(*l)-1; */
/*     int k3=(*k)+1; */
/*     int l3=(*l)+1; */
/*     if(k2>=0)  RechercheCirculaire_c(G, c, i, j, &k2, l);//récursion à gauche */
/*     printf("gauche k=%d , l=%d\n",k2,*l); */
/*     RechercheCirculaire_c(G, c, i, j, k, &l2);//récursion en haut */
/*     printf("haut k=%d , l=%d\n",*k,l2); */
/*     RechercheCirculaire_c(G, c, i, j, &k3, l);//récursion à droite */
/*     printf("droite k=%d , l=%d\n",k3,*l); */
/*     RechercheCirculaire_c(G, c, i, j, k, &l3);//récursion en bas */
/*     printf("bas k=%d , l=%d\n",*k,l3); */
/*   } */
/*   printf("fin!!!"); */
/*   return; */
/* } */

/* void RechercheCirculaire_nn(Grille *G, int i, int j, int *k, int *l){ */
  
/*  if( (*k)< 0  || (*k)> (G->n) || (*l) < 0  ||  (*l) > (G->m) ){ */
/*     return;//on a dépassé la matrice */
/*   } else if( G->T[*k][*l].piece >=0 && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) contient une pièce et n'est pas noire */
/*     return; */
/*   } else{ */
/*    int k2=(*k)-1; */
/*    int l2=(*l)-1; */
/*    int k3=(*k)+1; */
/*    int l3=(*l)+1; */
/*     RechercheCirculaire_nn(G, i, j, &k2, l);//récursion à gauche */
/*     RechercheCirculaire_nn(G, i, j, k, &l2 );//récursion en haut */
/*     RechercheCirculaire_nn(G, i, j, &k3, l);//récursion à droite */
/*     RechercheCirculaire_nn(G, i, j, k, &l3 );//récursion en bas */
/*   } */

/* } */







void algorithme_circulaire(Grille *G, Solution *S){
  
  int i = 0;
  int j = 0;
  int * k = malloc(sizeof(int));
  int * l = malloc(sizeof(int));
  int c;
  
  while(G->cptr_noire< G->m*G->n){

    if(G->T[G->ir][G->jr].robot == -1){//robot n'a pas de piece
      RechercheCirculaire_nn(G, G->ir, G->jr, k, l);//cherche case non noire
      changement_case(G,*k,*l);//robot bouge a (k,l)
      PlusCourtChemin(S, i,j, *k, *l);//ecrit dans solution le chemin le plus pris par le robot pour aller a (k,l)

      //robot est sur une case non noire donc on peut recuperer la piece
      swap_case(G);
    }
    //robot possede une piece
    else{
    
      c=G-> T[G->ir][G->jr].robot;
    RechercheCirculaire_c(G, c, i, j, k, l);//recherche la case de couleur c
    changement_case(G, *k, *l);
    PlusCourtChemin(S, i, j, *k, *l);
    swap_case(G);

    
   G-> cptr_noire++;//compteur noire +1
    }//finelse
  }//fin while
  free(k);
  free(l);


}





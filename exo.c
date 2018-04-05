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

int EstDansGrille(Grille* G, int i,int j){//si (i,j) est dans G
	if( (i<(G->m)) && i>=0 && (j<(G->n)) && j>=0){
		return 1;
	}else{ 
		return 0;
	}
}

int PieceEgaleFond(Grille * G , int i,int j,int c){
	if(G->T[i][j].fond == c){
		return 1;
	}else{
		return 0;
	}

}


int ExistePiece(Grille *G, int i,int j){
	if(G->T[i][j].piece != (-1) ){
		return 1;	
	}else{
		return 0;
	}
}



void RechercheCirculaire_c(Grille * G, int c, int i, int j, int * k, int * l){

  int i2,lg,ld;
  int L=1;
  int max = G->m + G->n ;

  printf("Debut robot se trouve : (%d, %d)\n",i,j);
	


  while(L< max){
    lg=j;
    ld=j;

    for(i2=i-L; i2<=i ; i2++){
      
      if( EstDansGrille(G, i2, lg) && PieceEgaleFond(G, i2, lg, c) && (!Case_est_Noire(G, i2, lg))  ){
	  *k=i2;
	  *l=lg;
	  printf("Piece trouvé gauche lg: (%d, %d)\n",*k,*l);
	  return ;
	}
     
	    
      if( EstDansGrille(G, i2, ld) && PieceEgaleFond(G, i2, ld, c) && (!Case_est_Noire(G, i2, ld) )  ){
	  *k=i2;
	  *l=ld;
	  printf("Piece trouvé gauche ld: (%d, %d)\n",*k,*l);
	  return ;
      }

      lg = lg - 1;
      ld = ld + 1;
      
    }//fin for



    lg = j-L+1;
    ld = j+L-1;

    for (i2=i+1;i2<=i+L;i++){

      if(EstDansGrille(G, i2, lg) && PieceEgaleFond(G, i2, lg, c) && (!Case_est_Noire(G, i2, lg)) ){ 
	  *k=i2;
	  *l=lg;
	  printf("Piece trouvé droite lg: (%d, %d)\n",*k,*l);
	  return ;
      }

      if(EstDansGrille(G, i2, ld) && PieceEgaleFond(G, i2, ld, c) && (!Case_est_Noire(G, i2, ld))){
	  *k=i2;
	  *l=ld;
	  printf("Piece trouvé droite ld: (%d, %d)\n",*k,*l);
	  return ;
      }

      lg = lg + 1;
      ld = ld - 1;
    }//fin for

    L++;

    
  }//fin while


  printf("Pas trouver de piece.\n\n");
}










void RechercheCirculaire_nn(Grille * G,  int i, int j, int * k, int * l){


  int i2,lg,ld;
  int L=0;
  int max = G->m + G->n ;

  printf("Debut robot se trouve : (%d, %d)\n",i,j);
    

  while(L<max){
    lg=j;
    ld=j;

    for(i2=i-L; i2<=i ; i2++){
      
      if( EstDansGrille(G, i2, lg) && ExistePiece(G, i2, lg) && (!Case_est_Noire(G, i2, lg))){ //Si la case (i2,lg) est de la même couleur que c, et n'est pas noire
	  *k=i2;*l=lg;
	  printf("Piece trouvé gauche lg: (%d, %d)\n",*k,*l);
	  return ;
	}
	    
      if(EstDansGrille(G, i2, ld) && ExistePiece(G, i2, ld) && (!Case_est_Noire(G, i2, ld)) ){
	  *k=i2;*l=ld;
	  printf("Piece trouvé gauche ld: (%d, %d)\n",*k,*l);
	  return ;
	}
   

      lg = lg - 1;
      ld = ld + 1;
      
    }//fin for



    lg = j-L+1;
    ld = j+L-1;
    for (i2=i+1;i2<=i+L;i++){
      if( EstDansGrille(G, i2, lg) && ExistePiece(G, i2, lg) && (!Case_est_Noire(G, i2, lg))){ //Si la case (i2,lg) est de la même couleur que c, et n'est pas noire
	  *k=i2;*l=lg;
	  printf("Piece trouvé droite lg: (%d, %d)\n",*k,*l);
	  return ;
	}
      

      if( EstDansGrille(G, i2, ld) && ExistePiece(G, i2, ld) && (!Case_est_Noire(G, i2, ld))){
	  *k=i2;*l=ld;
	  printf("Piece trouvé droite ld: (%d, %d)\n",*k,*l);
	  return ;
	}
      
      lg = lg + 1;
      ld = ld - 1;
    }//fin for

    L++;

    
  }//fin while

  
  printf("Pas trouver de case non noire.\n\n");
}




void algorithme_circulaire(Grille *G, Solution *S){
  
  int  k ;
  int  l ;
  int nb_total_noir = G->m * G->n;

  printf("CPT au depart %d___\n\n",G-> cptr_noire);
  
  while(G->cptr_noire < nb_total_noir){
    int c=G-> T[G->ir][G->jr].robot;

    if(G->T[G->ir][G->jr].robot == -1){//robot n'a pas de piece
      RechercheCirculaire_nn(G, G->ir, G->jr, &k, &l);//cherche case non noire
      
    }else{  //robot possede une piece
      RechercheCirculaire_c(G, c, G->ir, G->jr,&k,&l);//recherche la case de couleur c
    }



    PlusCourtChemin(S, G->ir, G->jr, k, l);
    changement_case(G,k,l);
    swap_case(G);Ajout_action(S,'S');

      printf("CPT %d___\n\n",G-> cptr_noire);
  }//fin while

  

}

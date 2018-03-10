#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

#include "exo.h"
#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"



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



/*
void PlusCourtChemin(Solution *S, int * i, int * j, int k,int l){

fprintf(stderr, "PCC1 %d %d %d %d\n",*i,*j, k,l );
 int x = (int)fabs(*i-k);
 int y = (int)fabs(*j-l);
 int tmp;



  if(*i==k && *j==l)return;

  
  if(k>*i){ //si la destination est a droite


    Ajout_action(S, 'R');
        tmp = *i+1;
        i = &tmp;
    return PlusCourtChemin(S,i,j,k,l);


  }
  else if(k<*i){//si la destination est à gauche
        fprintf(stderr, "PCCGauche %d %d %d %d\n",*i,*j, k,l );


    Ajout_action(S,'L');
        tmp = *i-1;
        i = &tmp;

    return PlusCourtChemin(S,i,j,k,l);

  
  }
  else if(l>*j){// si la destination est en bas
        fprintf(stderr, "PCCBas %d %d %d %d\n",*i,*j, k,l );

       
        Ajout_action(S,'D');
        tmp = *j+1;
        j = &tmp;        
        return PlusCourtChemin(S,i,j,k,l);
  }


  
  else if(l<*j){ //si la destination est en haut
        fprintf(stderr, "PCCHaut %d %d %d %d\n",*i,*j, k,l );

      Ajout_action(S,'U');
        tmp = *j-1;
        j  = &tmp;
      return PlusCourtChemin(S,i,j,k,l);


  }
  return;
}
*/





void RechercheCirculaire_c(Grille * G, int c, int i, int j, int * k, int * l){
  
  if( *k<0 || *k>G->n || *l<0 || *l>G->m ) return ;//on a dépassé la matrice

  else if( c==G->T[*k][*l].fond && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) est de la même couleur que c, et n'est pas noire
    fprintf(stderr, "trouve!\n");

    return ;
  } 
  else{RechercheCaseNaif_c(G, c, i, j, k-1, l);//récursion à gauche
       RechercheCaseNaif_c(G, c, i, j, k, l-1);//récursion en haut
       RechercheCaseNaif_c(G, c, i, j, k+1, l);//récursion à droite
       RechercheCaseNaif_c(G, c, i, j, k, l+1);//récursion en bas
            }
}

void RechercheCirculaire_nn(Grille *G, int i, int j, int *k, int *l){

  if( *k<0 || *k>G->n || *l<0 || *l>G->m ) exit(1);//on a dépassé la matrice

  else if( G->T[*k][*l].piece >=0 && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) contient une pièce et n'est pas noire
    
    return;
  } 
  else{ RechercheCaseNaif_nn(G, i, j, k-1, l);//récursion à gauche
        RechercheCaseNaif_nn(G, i, j, k, l-1);//récursion en haut
        RechercheCaseNaif_nn(G, i, j, k+1, l);//récursion à droite
        RechercheCaseNaif_nn(G, i, j, k, l+1);//récursion en bas
            }

}





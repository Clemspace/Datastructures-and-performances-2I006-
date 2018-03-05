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
  int c;
  int i = 0;
  int j = 0;
  int * k = malloc(sizeof(int));
  int * l = malloc(sizeof(int));
  fprintf(stderr, "dbg0\n");


  //cordonnées du robot dans (i,j)

   
  while(G->cptr_noire< G->m*G->n){   
    fprintf(stderr, "debut while  %d\n", G->cptr_noire);


    if(G->T[G->ir][G->jr].robot==-1){//si le robot n'a pas de pièce
      fprintf(stderr, "va chercher case avec piece %d COULEUR robot: %d\n", G->cptr_noire, G->T[G->ir][G->jr].robot);

      fprintf(stderr, "dbg cases_correctes %d\n", G->cptr_noire);
      fprintf(stderr, "cordonnees_robot (%d,%d)\n", G->ir,G->jr);

      RechercheCaseNaif_nn(G, G->ir, G->jr, k, l);//(k,l) a les coordonnées de la case la plus proche avec une piece
    
      changement_case(G, *k, *l);//change coodonnées 
     
      fprintf(stderr, "cordonnees_robotIJ (%d,%d)\n",i,j);

      PlusCourtChemin(S, &i, &j, *k, *l);
      fprintf(stderr, "cordonnees_robot (%d,%d)\n", G->ir,G->jr);

      if (Case_est_Noire(G,G->ir,G->jr)){//si case noire on trouve les coor case non noire
	RechercheCaseNaif_nn(G, G->ir, G->jr, k, l);//(k,l) a les coordonnées de la case la plus proche avec une piece
        
	changement_case(G, *k, *l);
	PlusCourtChemin(S, &i, &j, *k, *l);
      }

      swap_case(G);Ajout_action(S,'S');

      

    }
    else{//si le robot a une pièce
      fprintf(stderr, "VA POSER la piece\n");     
      fprintf(stderr, "dbg cases_correctes %d\n", G->cptr_noire);
      fprintf(stderr, "cordonnees_robot (%d,%d)\n", G->ir,G->jr); 
    

  
      int c = G->T[G->ir][G->jr].robot; 
      RechercheCaseNaif_c(G, c, G->ir, G->jr, k, l);//recherche la case cbile, cordonnées en(k,l)
      fprintf(stderr, "main %d %d %d %d\n", i,j,*k,*l);

      PlusCourtChemin(S, &i, &j, *k, *l);
      changement_case(G, *k, *l);
      swap_case(G);Ajout_action(S,'S');

    }
    G->cptr_noire++;

  }
  free(k);
  free(l);
  return;
  
}
  

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l){
  int x,y;
  int distance;
  int min = G->m+G->n+1;

  fprintf(stderr, "RCNC %d %d %d %d couleur a trouver %d\n", i,j,*k,*l, c);
  for (y = 0; y  < G->m; y++) //parcours du Tableau de cases
    {
      for (x = 0; x < G->n; x++)
	{
	  fprintf(stderr, "RCNC %d %d couleur:%d \n",x,y,G->T[x][y].fond);

	  distance = (int)sqrt((x - i) * (x - i) + (y - j) * (y - j));
	  if ( c==G->T[x][y].fond && distance < min){
	    fprintf(stderr, "RCNC_trouvé! (%d, %d) %d\n",x,y, distance);

	    min =distance;
	    *k= y;
	    *l = x;
	  } 

	}
    
    }
  fprintf(stderr, "RCNC %d %d %d %d\n", i,j,*k,*l);
  return; 

}

void RechercheCaseNaif_nn(Grille *G, int i, int j, int *k, int *l){
  int  x,y, distance;
  int min = G->m+G->n+1;
  fprintf(stderr, "RCNN %d %d %d %d\n", i,j,*k,*l);

  


  for (y = 0; y < G->m; y++) //parcours du Tableau de cases
    {
      for (x = 0; x < G->n; x++)
	{
	  fprintf(stderr, "RCNN  %d %d\n",x,y );

	  distance = (int)sqrt((x - i) * (x - i) + (y - j) * (y - j));

	  if ((Case_est_Noire(G, x, y)==0)&& distance < min){
	    fprintf(stderr, "RCNN_trouvé! (%d, %d) %d\n",x,y, distance);

	    min = distance;
	    *k= x;
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

/*
  void PlusCourtChemin(Solution *S, int  i, int  j, int k,int l){
  int x,y;



  }
*/




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




void RechercheCirculaire_c(Grille * G, int c, int i, int j, int * k, int * l)
{
  if( (*k)<0 || (*k)>(G->n) || (*l)<0 || (*l)>(G->m) ){

    return;//on a dépassé la matrice
  }else if( c==G->T[*k][*l].fond && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) est de la même couleur que c, et n'est pas noire

    fprintf(stderr, "trouve!\n");
    return ;
  } else{

    int k2=(*k)-1;
    int l2=(*l)-1;
    int k3=(*k)+1;
    int l3=(*l)+1;
    if(k2>=0)  RechercheCirculaire_c(G, c, i, j, &k2, l);//récursion à gauche
    printf("gauche k=%d , l=%d\n",k2,*l);
    RechercheCirculaire_c(G, c, i, j, k, &l2);//récursion en haut
    printf("haut k=%d , l=%d\n",*k,l2);
    RechercheCirculaire_c(G, c, i, j, &k3, l);//récursion à droite
    printf("droite k=%d , l=%d\n",k3,*l);
    RechercheCirculaire_c(G, c, i, j, k, &l3);//récursion en bas
    printf("bas k=%d , l=%d\n",*k,l3);
  }
  printf("fin!!!");
  return;
}

void RechercheCirculaire_nn(Grille *G, int i, int j, int *k, int *l){
  
 if( (*k)< 0  || (*k)> (G->n) || (*l) < 0  ||  (*l) > (G->m) ){
    return;//on a dépassé la matrice
  } else if( G->T[*k][*l].piece >=0 && Case_est_Noire(G, *k, *l)==0){ //Si la case (k,l) contient une pièce et n'est pas noire
    return;
  } else{
   int k2=(*k)-1;
   int l2=(*l)-1;
   int k3=(*k)+1;
   int l3=(*l)+1;
    RechercheCirculaire_nn(G, i, j, &k2, l);//récursion à gauche
    RechercheCirculaire_nn(G, i, j, k, &l2 );//récursion en haut
    RechercheCirculaire_nn(G, i, j, &k3, l);//récursion à droite
    RechercheCirculaire_nn(G, i, j, k, &l3 );//récursion en bas
  }

}



void cherche_case_distance_L(Grille *G,int i,int j,int L){//??
  return;
}





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
      PlusCourtChemin(S, &i,&j, *k, *l);//ecrit dans solution le chemin le plus pris par le robot pour aller a (k,l)

      //robot est sur une case non noire donc on peut recuperer la piece
      swap_case(G);
    }
    //robot possede une piece
    else{
    
      c=G-> T[G->ir][G->jr].robot; 
    RechercheCirculaire_c(G, c, i, j, k, l);//recherche la case de couleur c
             printf("21421\n");
    changement_case(G, *k, *l);
    PlusCourtChemin(S, &i, &j, *k, *l);
    swap_case(G);

    
   G-> cptr_noire++;//compteur noire +1
    }//finelse
  }//fin while
  free(k);
  free(l);


}

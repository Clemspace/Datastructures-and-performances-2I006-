#include "exo4.h"
#define max(a,b) (a>=b?a:b)

/*EXO4*/


//inicialiser un tableau de tableau(matrice) d'AVL de taille nbre couleurs *nbre lignes



AVL*** initTab(Grille *G){
  int k,j;
  
  int c = G->nbcoul; //nbre couleurs
  int i= G->m ;//nombre de lignes 

  AVL*** tab=(AVL***)malloc(c*sizeof(AVL**));


  for(j=0;j<i;j++){
    (tab)[j]=(AVL**)malloc (sizeof(AVL*));
  }
 
    
  return tab;
}





//trouver tous les j tq la case(i,j) contient la couleur c ( et les on stoque dans un AVL)

AVL* trouverJAVL(Grille* G,int c,int i){
  AVL * res = NULL;
  int b;


    for(b=0 ; b<(G->n) ; b++){ //parcours la grille

      if(G->T[b][i].piece == c){//si sur la case (a,b) contient une piece de couleur c
	inserer_avec_equi(res, b);//inserer j dans l'AVL
    }

      
  }
			   
  return res;

}

//Q4.3 : utilise la fonction precedente pour construire le tableau M[c][i]
AVL *** tableauCI(Grille * G){
  
  int c = G->nbcoul; //nbre couleurs
  int i= G->m ;//nombre de lignes

  int k,h;
  
  AVL *** M =initTab(G);// M[c][i]= un pointeur vers un AVL contenant tout les j tq (i,j) contient une piece de couleur c

  for(k=0;k<c;k++){//k=c
    for(h=0;h<i;h++){//h=i    parcour le tableau
      M[k][h]=trouverJAVL(G,k,h); //k est la couleur
    }
  }
  
  
  return M;
}



//Q4.4 : methode indiquant dans M[c][i] la case la plus proche d'une case (k,l) donnée 


int j_plus_proche(Grille * G,AVL *arb, int j ){

  
  int distance = abs(j-arb->entier);
  int minJ=G->n;
  int min=0;

  if(!arb)return minJ;
  
  if(abs(distance) < min){
      min = abs(j-arb->entier);
      minJ = arb->entier;
  }

  if(arb->entier == j){
      return j;
  }

  if(arb->entier < j){
    j_plus_proche(G,arb->fd,j);
  }
  if(arb->entier > j){
    j_plus_proche(G,arb->fg,j);
  }

  printf("ERREUr");
  return;

}


void case_plus_proche_c(Grille * G, AVL *** M, int c, int i, int j , int *k, int *l){//cherche la case la plus proche de (i,j) qui possede une piece de couleur c et on met dans (k,l)
  int ligne;
  int minJ=G->n;
  int tmp;
  for(ligne=0;ligne<(G->n) ;ligne++){

    tmp= j_plus_proche(G, M[c][i], j );
    if(tmp<minJ){
      minJ=tmp;
    }
  }

  k=&ligne;
  l=&minJ;
  

} 




void algorithme_AVL(Grille *G, Solution *S){
  
  AVL *** M =initTab(G);

  int taille= G->m*G->n;
  int i,j;
  int k = 0;
  int l = 0;


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

      //on utilise AVL pour chercher la case la plus proche avec une piece de couleur c
      case_plus_proche_c(G, M, c, G->ir,G->jr, &k, &l);
      //(k,l) a les coordonnées de la case la plus proche avec une piece

      PlusCourtChemin(S, G->ir, G->jr, k, l);
      changement_case(G, k, l);

      swap_case(G);Ajout_action(S,'S');
	        
      fprintf(stderr, "FinELSE\n" );


    }

  }

}














/*fonctions utilse pour manipuler les AVL*/

//creer un noeud 
AVL* creeN(int val,AVL* fd,AVL*fg) {
  AVL * n=(AVL*) malloc(sizeof(AVL));

  n->entier=val;
  n->hauteur=1+max(hauteur(fd),hauteur(fg));
  n->fd=fd;
  n->fg=fg;

  return n;
}

//return hauteur
int hauteur(AVL * a){
  if(a) return a->hauteur;
  return 0;
}

//mise a jour du hauteur
void majHauteur(AVL* a){
  if(a) a->hauteur=1+max( hauteur(a->fg),hauteur(a->fd) );
}

//rotation droite
void rotDroite(AVL ** ab){
  AVL* tmp=(*ab)->fg;

  (*ab)->fg=tmp->fd;
  tmp->fd=(*ab);
  (*ab)=tmp;
  
  majHauteur((*ab)->fd);
  majHauteur((*ab)->fg);
  majHauteur(*ab);
}

//rotation gauche
void rotGauche(AVL ** ab){
  AVL* tmp=(*ab)->fd;

  (*ab)->fd=tmp->fg;
  tmp->fg=(*ab);
  (*ab)=tmp;
  
  majHauteur((*ab)->fd);
  majHauteur((*ab)->fg);
  majHauteur(*ab);

}

//inserer element sans equilibre
AVL* inserer_sans_equi(AVL * b, int val){
  if(b==NULL){//si l'AVL vide alors val est noeud
    return creeN(val,NULL,NULL);
  }
  
  if( val<(b->entier) ){//dans fg
    if( (b->fg)==NULL){//premier fils a gauche
      b->fg=creeN(val,NULL,NULL);
    }else{
      b->fg=inserer_sans_equi(b->fg,val);
    }
  }else{
    if(b->fd==NULL){ //premier fils a droite
      b->fd=creeN(val,NULL,NULL);
    }else{
      b->fd=inserer_sans_equi(b->fd,val);
    }
  }
  return b;

}

//inserer element avec equilibre
AVL* inserer_avec_equi(AVL* ab, int val){
  ab=inserer_sans_equi(ab,val);

  if( fabs( hauteur(ab->fg)-hauteur(ab->fd))  <2 )//deja equilibrer
    return;

  if( fabs( hauteur(ab->fg)-hauteur(ab->fd)) == 2 ){
    if(hauteur(ab->fg->fg)<hauteur(ab->fg->fd) ){
      rotGauche(&(ab->fg));
    }
    rotDroite(&ab);
  }
 

  if( fabs( hauteur(ab->fg)-hauteur(ab->fd)) == -2){
    if(hauteur(ab->fd->fd)<hauteur(ab->fd->fg) ){
      rotDroite(&(ab->fd) );
    }
    rotGauche(&ab);
  }


  return ab;
}

#include "exo4.h"

/*EXO4*/
typedef struct s_avlEqui{
  int entier;
  int hauteur;

  struct s_avlEqui * fd;
  struct s_avlEqui * fg;
}AVL;


//inicialiser un tableau de taille c*i
AVL** initTab(Grille *G){
  int j;
  
  int c = G->nbcoul; //nbre couleurs
  int i= G->m ;//nombre de lignes 

  AVL** tab=(AVL**)malloc(i*sizeof(AVL*));
  for(j=0;j<i;j++){
    tab[i]=(AVL*)malloc(c*sizeof(AVL));
  } 
  
  return tab;
}


//trouver tous les j tq la case(i,j) contient la couleur c et les stoque dans un tableau 
int* trouverJ(Grille* G, int c){
  int *tabj=(int *) malloc(sizeof(int)* (G->m)*(G->n));
  int a,b,cpt=0;

  for(a=0 ; a<(G->m) ; a++){
    for(b=0 ; b<(G->n) ; b++){
      if(G->T[a][b].piece == c){//si sur case (a,b)contient une piece de couleur c
	tabj[cpt]=b;//contient j qu'on cherche
	cpt++;
      }
    }
  }
			   
  return tabj;
}



//trouver tous les j tq la case(i,j) contient la couleur c ( et les on stoque dans un AVL)



//utilise la fonction precedente pour construire le tableau M[c][i]









/*fonction utile pour manipuler les AVL*/

//creer un noeud 
AVL* creeN(int val,AVL* fd,AVL*fg){
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

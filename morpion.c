#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB 3
#define COUP 9

int t = 0;

void initialiseGrille(char ** grille) {
  int i, j;
  for (i=0; i<NB; i++) {
    for (j=0; j<NB; j++) {
      grille[i][j] = '-';
    }
  }
}

int nbCaseVide(char ** grille)
{
  int i, j,indice = 0;

  for (i=0; i<NB; i++) 
  {
    for (j=0; j<NB; j++) 
    {
      if(grille[i][j] == '-')
      {
        indice++;
      }
    }
  }
  return indice;
}
void afficheGrille(char ** grille) {
  int i, j;
  for (i=0; i<NB; i++) {
    printf(" | "); 
    for (j=0; j<NB; j++) {      
      printf("%c",grille[i][j]);
      printf(" | ");   
    }
    printf("\n"); /* fin de la ligne */
  }
}

int libre(char ** grille,int x, int y)
{
  if(grille[x][y] == '-')
    return 0;
  else
    return 1;
}
void errorInput(int * x, int  * y)
{
  printf("Rechoisir position x : ");
  scanf("%d", x);
  printf("Rechoisir position y : ");
  scanf("%d", y);
}
void player(char ** grille)
{
    int x ,y;
    printf("Choisir position x : ");
    scanf("%d", &x);
    printf("Choisir position y : ");
    scanf("%d", &y);
    if(x > 2 || y > 2){
      printf("Erreur: input invalide \n");
      errorInput(&x, &y);
    }
    while(libre(grille,x,y) == 1)
    {
      printf("Erreur : case deja remplie \n");
      errorInput(&x,&y);
    }
    grille[x][y] = 'X';
}

void coupPossible(char ** grille, int ** coupP)
{
  int nbCaseV = nbCaseVide(grille);
  int i, j,indice = 0;

  for (i=0; i<nbCaseV; i++)
      coupP[i]=(int *) malloc(2*sizeof(int));
  

  for (i=0; i<NB; i++) 
  {
    for (j=0; j<NB; j++) 
    {
      if(grille[i][j] == '-')
      {
        coupP[indice][0] = i;
        coupP[indice][1] = j;
        indice++;
      }
    }
  }
}



char lignePleine(char a, char b, char c)
{
    if(a==b && b == c)
    {
      if(a == 'X')
      {
        return 'X';
      }
      else if (a=='O')
      {
        return 'O';
      }
    }
    return 'v';
}

//si vide = 0 -> grille rempli
//sinon non
int grillePlein(char ** grille)
{
  int i, j;
  int vide = 0;
  for (i=0; i<NB; i++) {
    for (j=0; j<NB; j++) {
      if(grille[i][j] == '-')
      {
        vide = 1;
      }
    }
  }
  return vide;
}

char resultat(char ** grille)
{
  char c1 = grille[0][0];
  char c2 = grille[0][1];
  char c3 = grille[0][2];
  char c4 = grille[1][0];
  char c5 = grille[1][1];
  char c6 = grille[1][2];
  char c7 = grille[2][0];
  char c8 = grille[2][1];
  char c9 = grille[2][2];

  char lp1 = lignePleine(c1,c2,c3);
  char lp2 =lignePleine(c4,c5,c6);
  char lp3 =lignePleine(c7,c8,c9);
  char lp4 =lignePleine(c1,c4,c7);
  char lp5 =lignePleine(c2,c5,c8);
  char lp6 =lignePleine(c3,c6,c9);
  char lp7 =lignePleine(c1,c5,c9);
  char lp8 =lignePleine(c3,c5,c7);

  if(lp1 == 'X' || lp2 == 'X' || lp3 == 'X' || lp4 == 'X' 
  || lp5 == 'X' || lp6 == 'X' || lp7 == 'X' || lp8 == 'X')
  {
    return 'X';
  }
  else if(lp1 == 'O' || lp2 == 'O' || lp3 == 'O' || lp4 == 'O' 
  || lp5 == 'O' || lp6 == 'O' || lp7 == 'O' || lp8 == 'O')
  {
    return 'O';
  }
  else if(grillePlein(grille) == 0)
  {
    return 'P';
  }
  else
  {
    return 'V';
  }
}







int MinMax(char **grille, int niveaux ,int * a, int * b, int profondeur)
{
  //printf("Profondeur = %d\n",profondeur);
  int i,y,j,bestScore,score;
  int coutMin = 0;
  int ** coupP;
  //MATRICE
  int nbCaseV = nbCaseVide(grille);
  coupP=(int**) malloc(nbCaseV * sizeof(int*));
  for (i=0; i<nbCaseV; i++)
      coupP[i]= malloc(2 * sizeof(int));
    
  //OBTENIR TOUT LES COUPS POSSIBLES
  coupPossible(grille, coupP);

  if(resultat(grille) == 'O')
  {
    return 1;
  }
  else if(resultat(grille) == 'X')
  {
    return -1;
  }
  else if(resultat(grille) == 'P')
  {
    return 0;
  } 
  else if(niveaux == 0)
  {
    bestScore = -1000000;
    for(i=0;i<nbCaseV;i++)
    {
      grille[coupP[i][0]][coupP[i][1]] = 'O';
      score = MinMax(grille,1,a,b, profondeur+1);
      grille[coupP[i][0]][coupP[i][1]] = '-';
      if(score > bestScore)
      {
        bestScore = score;
        *a = coupP[i][0];
        *b = coupP[i][1];
      }
    }
    return score;
  }
  else
  {
    bestScore = 1000000;
    for(i=0;i<nbCaseV;i++)
    {
      grille[coupP[i][0]][coupP[i][1]] = 'X';
      score = MinMax(grille,0,a,b, profondeur+1);
      grille[coupP[i][0]][coupP[i][1]] = '-';
      if(score <bestScore)
      {
        bestScore = score;
        *a = coupP[i][0];
        *b = coupP[i][1];  
      }
    }
    return score;
  }
}

void ia(char **grille)
{
  printf("IA joue\n");
  int x,y;
  //MATRICE
  int * scores;
  scores= malloc(3 * sizeof(int));
  MinMax(grille, 0,&x,&y,0);
  grille[x][y] = 'O';
}

void jouer(char ** grille)
{
  //player
  if(t==0)
  {
    player(grille);
    t = 1;
  }
  //IA
  else
  {
    ia(grille);
    t = 0;
  }
}

int main()
{
  int num;
  char nom[20] = {0};
  char **grille;
  int i,y;
  // Allocation de l'espace pour stocker 100 pointeurs
  grille=(char**) malloc(3 * sizeof(char*));

  for (i=0; i<3; i++)
      grille[i]=(char *) malloc(3*sizeof(char));
      
  initialiseGrille(grille);
  afficheGrille(grille);
  printf("Nom joueur : ");
  scanf("%s", nom);
  printf("Bienvenue %s !\n\n", nom);

  while(1)
  {
    jouer(grille);
    afficheGrille(grille);
    resultat(grille);
    if(resultat(grille) == 'X')
    {
      printf("Joueur a gagné");
      exit(0);
    }
    if(resultat(grille) == 'O')
    {
      printf("IA a gagné");
      exit(0);
    }
    if(resultat(grille) == 'P')
    {
      printf("Macth nul");
      exit(0);
    }
  }
  return 0;
}

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int tab[20],nbEchiquier;
 
int position(int x,int y)
{
 int i;
 for(i=1;i<=x-1;++i)
 {

  if(tab[i]==y)
  {
   return 0;
  }
  else
  {
   if(abs(tab[i]-y)==abs(i-x))
   {
    return 0;
   }
  }
 }
 
 return 1; 
}

void afficheGrille()
{
  int i,j,nb=8;
  printf("\n\n----------------------------------\n");
  printf("| Echiquier %d:\n",nbEchiquier++);
  printf("----------------------------------\n\n");
  for(i=1;i<=8;++i)
  {
      printf("\t%d",i);
  }
  
  for(i=1;i<=nb;++i)
  {
    printf("\n\n%d  ",i);
    for(j=1;j<=nb;++j) 
    {
    if(tab[i]==j)
      printf("\tR  "); 
    else
      printf(" -  "); 
    }
  }
}

void ajoutReine(int row)
{
  int y;
  int total = 8;
  for(y=1;y<=total;++y)
  {
    if(position(row,y))
    {
      tab[row]=y; 
      if(row==total)
      {
        afficheGrille(); 
      }
      else 
      {
        ajoutReine(row+1);
      }
    }
  }
}

int main()
{
  ajoutReine(1);
  return 0;
}
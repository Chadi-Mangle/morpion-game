#include <stdlib.h>
#include <stdio.h>

/* 18éme cours : Création d'un module, partie 1 */
/*
   fonction intarray_display (tab : tableau d'entiers)
   VAR i : entier 
   début
	pour i allant de 0 à tab.taille faire :
		début 
			afficher (tab[i])
		fin
   fin

*/


  void intarray_display (int* tab, int len)
  {
  	int i;
  	for (i = 0; i < len; i++)
  		printf("%d ", tab[i]);
  }

int main(int argc, char** argv)
{
	int toto[] = {-8, 46, 22, -1, 10, -100};
	intarray_display (toto, 6);
}
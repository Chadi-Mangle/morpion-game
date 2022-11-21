#ifndef __INTARRAY_H__
#define __INTARRAY_H__

#include "tools.h"

/* "sémantique par référence uniforme" */
typedef struct intarray* intarray;

typedef struct intarray s_intarray;

struct intarray {
  int* data;
  int alloc; /* taille actuellement allouée du champ data */
  int len; /*nombre d'éléments de data qu'on prend en compte */
};

#define INTARRAY_DEFAUT_ALLOC 8

/* int intarray_get_index_of_min_from  (intarray tab, int n); */



/* 28éme cours : conversion d'une chaîne en entier 
    Programmation modulaire. Makfile  */



/* prototypes des fonctions de manipulation des intarrays */
intarray intarray_create (int len);
intarray empty_intarray_create (int alloc);
intarray standard_empty_intarray_create (void);
void intarray_destroy (intarray tab);
int intarray_get (intarray tab, int index);
/* pour les tabeaux de taille max fixe seulement */
void intarray_set (intarray tab, int index, int value);
/*commeintarray_set, mais modifie alloc si nécessaire */
void ext_intarray_set (intarray tab, int index, int value);
void intarray_add (intarray tab, int value);

/*
Déplace un seul élément (trés rapide).
Atention : modifie l'ordre des éléments de tab
Si on souhaite que l'ordre reste inchangé,
il faut appeler la fonction intarry_delete.

*/
void UNSORTED_intarray_delete (intarray tab, int index);
/*
Déplace jusqu'à N éléments (dans le pire des car),
N étant la taille du tableau.
*/
void intarray_delete (intarray tab, int index);

int intarray_length (intarray tab); 
void intarray_debug (intarray tab);
void ext_intarray_debug (intarray tab);
void intarray_print_positive_values (intarray tab);
int intarray_search (intarray tab, int n);
int intarray_nb_occurences (intarray tab, int n);
void intarray_sort1 (intarray tab);
intarray intarray_clone ( intarray tab);

int intarray_sum (intarray tab);
float intarray_average (intarray tab);
float intarray_median (intarray tab);

/* retoure le résultat de la concaténation de T1 et T2 */
intarray intarray_contat (intarray T1, intarray T2);

/* retoune le plus petite valeur contenue dans tab*/
int intarray_get_min (intarray tab);
/* */
/* int mini = tab.data[0]/
/* 25 26 8 12 13 */
/*retourne l'index de la plus petite valeur contenue dans tab */
int intarray_get_index_of_min (intarray tab);

/*
  retourne l'index de la plus petite valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int intarray_get_index_of_min_from  (intarray tab, int n);
/**/
/* retoune le plus grande valeur contenue dans tab*/
int intarray_get_max (intarray tab);

/*retourne l'index de la plus grande valeur contenue dans tab */
int intarray_get_index_of_max (intarray tab);

/*
  retourne l'index de la plus grande valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int intarray_get_index_of_max_from  (intarray tab, int index);

/* tirage aléatoire d'entiers entre et a et b pour créer un tableau de
taille n */
intarray intarray_create_random (int n, int a, int b);

#endif 
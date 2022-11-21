#ifndef __JSTR_H__
#define __JSTR_H__

#include "tools.h"
#include "intarray.h"
/* jstr = string */
/* "sémantique par référence uniforme" */
typedef struct jstr* jstr;
typedef struct jstr s_jstr;

struct jstr{
  char* data;
  int alloc; /* taille actuellement allouée du champ data */
  int len; /*nombre d'éléments de data qu'on prend en compte */
};

#define jstr_DEFAUT_ALLOC 8


int jstr_equal_substr (jstr ji, int s1, int e1, jstr j2, int s2);
int jstr_equal (jstr j1, jstr j2);
intarray jstr_find_substr_indices (jstr j, jstr sub);
intarray jstr_find_proper_substr_indices (jstr j, jstr sub);
intarray jstr_find_substr_indices_aux (jstr j, jstr sub, int incr_when_occurence_found);
int jstr_compare (jstr j1, jstr j2); /*-1, 0 ou +1 */

/* int jstr_get_index_of_min_from  (jstr tab, int n); */

/* 28éme cours : conversion d'une chaîne en entier 
    Programmation modulaire. Makfile  */


/* prototypes des fonctions de manipulation des jstrs */
jstr jstr_create (int len);
jstr empty_jstr_create (int alloc);
jstr standard_empty_jstr_create (void);
void jstr_destroy (jstr tab);
void regular_jstr_destroy (jstr* tab);

/* regstr = regular str = string with a terminal '\0' */
jstr regstr_to_jstr (char* str);
char* jstr_to_regstr (jstr tab);


char jstr_get (jstr tab, int index);
/* pour les tabeaux de taille max fixe seulement */
void jstr_set (jstr tab, int index, char value);
/*commejstr_set, mais modifie alloc si nécessaire */
void ext_jstr_set (jstr tab, int index, char value);
void jstr_add (jstr tab, char value);

/*
Déplace un seul élément (trés rapide).
Atention : modifie l'ordre des éléments de tab
Si on souhaite que l'ordre reste inchangé,
il faut appeler la fonction intarry_delete.

*/
void UNSORTED_jstr_delete (jstr tab, int index);
/*
Déplace jusqu'à N éléments (dans le pire des car),
N étant la taille du tableau.
*/
void jstr_delete (jstr tab, int index);

int jstr_length (jstr tab); 
void jstr_debug (jstr tab);
void ext_jstr_debug (jstr tab);
void jstr_print_positive_values (jstr tab);
int jstr_search (jstr tab, char n);
int jstr_nb_occurences (jstr tab, char n);
void jstr_sort1 (jstr tab);
jstr jstr_clone ( jstr tab);

int jstr_sum (jstr tab);
float jstr_average (jstr tab);
float jstr_median (jstr tab);

/* retoure le résultat de la concaténation de T1 et T2 */
jstr jstr_contat (jstr T1, jstr T2);

/* Ajoute à la fin T1 des copies des caractéres de T2,
en respectant l'ordre de ces derniers.
Le contenu de T2 n'est pas modifié.
 */
void D_jstr_concat (jstr T1, jstr T2);

/* retoune le plus petite valeur contenue dans tab*/
char jstr_get_min (jstr tab);
/* */
/* int mini = tab.data[0]/
/* 25 26 8 12 13 */
/*retourne l'index de la plus petite valeur contenue dans tab */
int jstr_get_index_of_min (jstr tab);

/*
  retourne l'index de la plus petite valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int jstr_get_index_of_min_from  (jstr tab, int n);
/**/
/* retoune le plus grande valeur contenue dans tab*/
char jstr_get_max (jstr tab);

/*retourne l'index de la plus grande valeur contenue dans tab */
int jstr_get_index_of_max (jstr tab);

/*
  retourne l'index de la plus grande valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int jstr_get_index_of_max_from  (jstr tab, int index);

jstr jstr_input (void);

char* regstr_input (void);

void jstr_reverse (jstr j);

jstr int_to_jstr (int n);

char* int_to_regstr (int n);

#endif
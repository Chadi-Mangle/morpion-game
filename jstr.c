/* jstr = string */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "jstr.h"
#include "tools.h"
#include "intarray.h"

jstr jstr_input (void)
{
  jstr j = standard_empty_jstr_create ();
  char c = getchar ();
  while ( c != '\n')
    {
      jstr_add (j, c);
      c = getchar ();
    }
  return j;
}

char* regstr_input (void)
{
  jstr j = jstr_input ();
  char* str = jstr_to_regstr (j);
  jstr_destroy (j);
  return str; 
}

void jstr_resize (jstr tab, int newalloc)
{
  char* newdata = tools_malloc (sizeof (char) * newalloc);
  int i;

  for (i = 0; i < tab->len; i++)
    newdata[i] = tab->data[i];

  tools_free (tab->data, sizeof (char) * tab->alloc);

  tab->data = newdata;
  tab->alloc = newalloc;

}

void ext_jstr_set (jstr tab, int index, char value)
{
  int i;
  
  if (index < 0)
    {
      printf("ext_jstr_set : impossible d'écrire en case %d.\n", index);
      return;
    }
  if (index < tab->len)
    {
     tab->data[index] = value;
     return; 
    }
  if (index >= tab->alloc)
    jstr_resize (tab, 1 + 2 * index);

  for (i = tab->len; i < index; i++)
    tab->data[i] = 0;

  tab->data[index] = value;

  if (index >= tab->len)
    tab->len = index + 1;

}

/*
Déplace un seul élément (trés rapide).
Atention : modifie l'ordre des éléments de tab
Si on souhaite que l'ordre reste inchangé,
il faut appeler la fonction intarry_delete.

*/
void UNSORTED_jstr_delete (jstr tab, int index)
{
  if((index < 0) || (index >= tab->len))
    {
     printf("intarry_delete : index invalide %d.\n",index );
     return;
    }

  tab->data[index] = tab->data[tab->len - 1];
  
  tab->len--;
}
/*
Déplace jusqu'à N éléments (dans le pire des car),
N étant la taille du tableau.
*/
void jstr_delete (jstr tab, int index)
{
  int i;
  if((index < 0) || (index >= tab->len))
    {
     printf("intarry_delete : index invalide %d.\n",index );
     return;
    }
  for (i = index + 1; i < tab->len; i++)
    tab->data[i - 1] = tab->data[i];

  tab->len--;

}


void jstr_add (jstr tab, char value)
{
  ext_jstr_set (tab, tab->len, value);  
}

/* */
/* retoune le plus grande valeur contenue dans tab*/
char jstr_get_max (jstr tab)
{
  int index_maxi = jstr_get_index_of_max (tab);
  return tab->data[index_maxi];
} 

/*retourne l'index de la plus grande valeur contenue dans tab */
int jstr_get_index_of_max (jstr tab)

{
  return jstr_get_index_of_max_from (tab, 0);
}

/*
  retourne l'index de la plus grande valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int jstr_get_index_of_max_from  (jstr tab, int index)
{
  if ((index < 0) || (index >= tab->len))
  {
    printf ("jstr_get_index_of_max_from :\nL'index %d est invalide.\n", index);
    printf ("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
    return 0;
  }

  char maxi = tab->data[index];
  int index_maxi = index;
  int i;
  for (i =  index + 1; i < tab->len; i++)
    {
      if (tab->data[i] > maxi)
      {
        maxi = tab->data[i];
        index_maxi = i;
      } 
    }
return index_maxi;
}




/* retoune le plus petite valeur contenue dans tab*/
char jstr_get_min (jstr tab)
{
  char index_mini = jstr_get_index_of_min (tab);
  return tab->data[index_mini];
} 
/*
{
int mini = tab->data[0];
int i;
for (i = 1; i < tab->len; i++)
  {
    if (tab->data[i] < mini)
      mini = tab->data[i];
  }
return mini;
}
*/

/*retourne l'index de la plus petite valeur contenue dans tab */
int jstr_get_index_of_min (jstr tab)

{
  return jstr_get_index_of_min_from (tab, 0);
}

/*
  retourne l'index de la plus petite valeur contenur dans tab,
  entre la case numéro n et fin du tableau.
  */
int jstr_get_index_of_min_from  (jstr tab, int index)
{
  if ((index < 0) || (index >= tab->len))
  {
    printf ("jstr_get_index_of_min_from :\nL'index %d est invalide.\n", index);
    printf ("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
    return 0;
  }

  char mini = tab->data[index];
  int index_mini = index;
  int i;
  for (i =  index + 1; i < tab->len; i++)
    {
      if (tab->data[i] < mini)
      {
        mini = tab->data[i];
        index_mini = i;
      } 
    }
return index_mini;
}

/*  i: T1 = 1 2 3 8 9 ; i : T2 = 23 45 -7 */

/* on retourne un tableau de longueur 8*/

/* j : 1 2 3 8 9 23 45 - 7 */

/* cette fonction n'est correcte que si T1->len != 0 ou T2->len != 0 */
jstr jstr_contat (jstr T1, jstr T2)
{
 jstr T = jstr_create ( T1->len + T2->len);
 int i, j = 0;

 /* 1ére étape : on copie T1 vers le début de T*/
 for ( i = 0; i < T1->len; i++)
   {
    T->data[j] = T1->data[i];
    j++;
   }
/* 2éme étape on copie T2 vers T à partir de l'endroit
où la premiére copie s'est arrêtée */

 for (i = 0; i < T2->len; ++i)
   {
      T->data[j] = T2->data[i];
      j++;
   }
 return T;
}

void jstr_create_aux (jstr tab)
{
  int i;
  if (tab->alloc <= 0)
  {
    tab->alloc = 4;
    printf("jstr_create_aux : taille allouée <= 0.\n");
    printf("nous allouons %d à la plac.\n", tab->alloc);
  }

  tab->data = tools_malloc (tab->alloc * sizeof (char));

  for (i = 0; i < tab->alloc; i++)
    tab->data[i] = 0;
}

jstr standard_empty_jstr_create (void)
{
  return empty_jstr_create (jstr_DEFAUT_ALLOC);
}


jstr empty_jstr_create (int alloc)
{
  jstr tab = tools_malloc (sizeof (struct jstr));
    tab->len = 0;
  tab->alloc = alloc;
  jstr_create_aux (tab);
  return tab;
}
jstr jstr_create (int len)
{
  jstr tab = tools_malloc (sizeof (struct jstr));
  tab->len = len;
  tab->alloc = len;
  jstr_create_aux (tab);
  return tab;
}


int jstr_nb_occurences (jstr tab, char n)
{
  int nb_occurences = 0;
  int i;
  for (i = 0; i < tab->len; i++)
  {
    if (tab->data[i] == n)
      nb_occurences++;
  }
  return nb_occurences;
}


int jstr_search (jstr tab, char n)
{
  int i;
  for (i = 0; i < tab->len; i++)
    {
      if (tab->data[i] == n)
        return 1;
    }
  return 0;
}

void jstr_print_positive_values (jstr tab)
{
  int i;
  for (i = 0; i < tab->len; i++)
  {
    if (tab->data[i] >= 0)
      printf ("%d", tab->data[i]);
  }
}
void ext_jstr_debug (jstr tab)
{
 printf("Tab. alloc = %d ; len = len = %d\n", tab->alloc, tab->len);
 jstr_debug (tab);
}

void jstr_debug (jstr tab)
{
	int i;
  	for (i = 0; i < tab->len; i++)
		printf ("%c", tab->data[i]);
}

void jstr_destroy (jstr tab)
{
  tools_free (tab->data, sizeof (char) * tab->alloc);
  tools_free (tab, sizeof (s_jstr));
}

void regular_jstr_destroy (jstr* ttab)
{

  if (ttab == NULL)
  {
    printf("regular_jstr_destroy : ttab is a NULL pointer. \n");
    return;
  }

  {
    jstr tab = *ttab;
    if (tab == NULL)
      return;
    jstr_destroy (tab);
    *ttab = NULL;
  }
}


char jstr_get (jstr tab, int index)
{
  if ((index < 0) || (index >= tab->len))
  {
    printf ("jstr_get :\nL'index %d est invalide.\n", index);
    printf ("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
    return -1;
  }
  return tab->data[index];
}

void jstr_set (jstr tab, int index, char value)
{
  if ((index < 0) || (index >= tab->len))
  {
    printf ("jstr_set :\nL'index %d est invalide.\n", index);
    printf ("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
    return;
  }
  tab->data[index] = value; 
}
int jstr_length (jstr tab)
{
  return tab->len;
}
/* Allocation mémoire automatique
   Allocation mémoire statique */



void jstr_sort1 (jstr tab)
{
  int i;
  
  for (i = 0; i <= tab->len -2; i++)
    {
      int indice_min = jstr_get_index_of_min_from (tab, i);
      /*jstr_swap (&(tab->data[i]), &(tab->data[indice_min]));*/
      char_swap (tab->data + i, tab->data + indice_min);
      
    }
}

int jstr_sum (jstr tab)
{
  int sum = 0;
  int i;
  for (i = 0; i < tab->len; i++)
    sum += ((int) tab->data[i]);
  if (tab->len <= 0)
    {
      printf("jstr_sum : tableau de longueur <= 0. \n");
      return -1;
    }
  return sum;
}

jstr jstr_clone ( jstr tab)
{
  jstr copy = jstr_create (tab->len);
  int i;
  for (i = 0; i < tab->len; i++)
    copy->data[i] = tab->data[i];

  return copy;
}

float jstr_average (jstr tab)
{
  int sum = jstr_sum (tab);
  if (tab->len <= 0)
  {
    printf("jstr_average : tableau de longueur <= 0. \n");
    return -1.0;
  }
  return ((sum * 1.0) / tab->len); 
}

float jstr_median (jstr tab)
{
  if (tab->len <= 0)
  {
   printf("jstr_average : tableau de longueur <= 0. \n");
   return -1.0; 
  }

  jstr copy = jstr_clone (tab);
  float median;
  jstr_sort1 (copy);

  if (copy->len % 2 == 1)
    median = copy->data[(copy->len - 1) / 2];
  else /* tab->len % 2 == 0 */
    {
      int v1 = (int) copy->data[(copy->len - 1) / 2];
      int v2 = (int) copy->data[copy->len / 2];
      median = (v1 + v2 ) / 2.0;
    }
jstr_destroy (copy);
return median;
}

jstr regstr_to_jstr (char* str)
{
  jstr tab = standard_empty_jstr_create ();
  int i;
  for (int i = 0; str[i] != '\0'; i++)
    jstr_add (tab, str[i]);
  return tab;
}
char* jstr_to_regstr (jstr tab)
{
  char* str = tools_malloc (sizeof (char) * (tab->len + 1));
  int i;
  for (i = 0; i < tab->len; i++)
    str[i] = tab->data[i];
  str[tab->len] = '\0';
  return str;
}

/* Ajoute à la fin T1 des copies des caractéres de T2,
en respectant l'ordre de ces derniers.
Le contenu de T2 n'est pas modifié.
 */
void D_jstr_concat (jstr T1, jstr T2)
{
  int i;
  for (i = 0; i < T2->len; i++)
    jstr_add (T1, T2->data[i]);
}

int jstr_equal_substr (jstr j1, int s1, int e1, jstr j2, int s2)
{
  int len = e1 - s1 +1;
  int e2 = s2 + len -1;

  if (s1 > e1)
  {
    int_swap (&s1, &e1);
    printf ("jstr_equal_substr : s1 était inférieur à e1. J'échage les deux.\n");
  }

  if ((s1 < 0) || (s2 < 0) || (s1 >= j1->len) || (e1 >= j1->len) || (s2 >= j2->len))
  {
    printf ("jstr_equal_substr : out of bounds. s1 = %d ; e1 = %d ;\n", s1, e1);
    printf ("s2 = %d ; j1->len = %d ; j2->len = %d.\n", s2, j1->len, j2->len);
    return 0;
  }

  if (e2 >= j2 ->len)
    return 0;
{
  int i;
  for (i = 0; i < len; i++)
    {
      if (j1->data[i + s1] != j2->data[i + s2])
        return 0;
    }
  return 1;
  }

}



int jstr_equal (jstr j1, jstr j2)
{
  if (j1 == j2)
    return 1;
  else if (j1->len != j2->len)
    return 0;
  else
   return jstr_equal_substr (j1, 0, j1->len -1, j2, 0);
}

/*
Fonction auxiliaire pour jstr_find_substr_indices 
et jstr_find_substr_proper_indices.
La différence entre les deux est que la valeur ajoutée au compteur i
est sub->len dans le cas de proper et 1 dans l'autre cas.

intarray jstr_find__substr_indices_aux (jstr j, jstr sub, int incr_when_occurence_found)
{
  intarray A = standard_empty_intarray_create ();
  int i;
  for (i = 0; i <= j->len - sub->len; i++)
    {
      if (jstr_equal_substr (j, i, i + sub->len - 1, sub, 0))
      {
        intarray_add (A, i);
        i += incr_when_occurence_found;
      }
        else
          i++;
    }
  return A;
}
*/
intarray jstr_find_substr_indices (jstr j, jstr sub)

  {
  intarray A = standard_empty_intarray_create ();
  int i;
  for (i = 0; i <= j->len - sub->len; i++)
    {
      if (jstr_equal_substr (j, i, i + sub->len - 1, sub, 0))
        intarray_add (A, i);
    }
  return A;
}

intarray jstr_find_proper_substr_indices (jstr j, jstr sub)
{
  intarray A = standard_empty_intarray_create ();
  int i;
  for (i = 0; i <= j->len - sub->len;)
    {
      if (jstr_equal_substr (j, i, i + sub->len - 1, sub, 0))
      {
        intarray_add (A, i);
        i += sub->len;
      }
        else
          i++;
    }
  return A;
}

int jstr_compare (jstr j1, jstr j2) /*-1, 0 ou +1 */
{
  int minlen = j1->len;
  int i;
  if (j2->len < minlen)
    minlen = j2->len;

  for (i = 0; i < minlen; i++)
  {
    if (j1->data[i] < j2->data[i])
      return -1;
    else if (j1->data[i] > j2->data[i])
      return 1;
  }

if (j1->len > j2->len)
  return 1;
else if (j1->len < j2->len)
  return -1;
else /*j1->len == J2->len + tous les caractéres identiques */
return 0;

}
/*
  abcde
  ebcda
  edcba

  i allant de 0 à 1 
*/
void jstr_reverse (jstr j)
{
  if (j->len <= 1)
    return;
  {
    int last = (j->len -2) / 2;
    int i;
    for (i = 0; i <= last; i++)
    {
      char tmp = j->data[i];
      j->data[i] = j->data[j->len  - 1 - i];
      j->data[j->len  - 1 - i] = tmp;
    }
  }
}

/* n 1298 
   
   n % 10 => 8
   n /= 10 => 129
   n % 10 => 9
   n /= 10 => 12
   n % 10 => 2
   n /= 10 => 1
   n % 10 => 1
   n /= 10 => 0

   don 8921 avce jstr_reverse => 1298 


*/

/* attention : cette version ne fonctionne que si n >= 0 */
jstr int_to_jstr (int n)
{
  jstr j = standard_empty_jstr_create ();
  if (n == 0)
    {
      jstr_add (j, '0');
      return j;
    }


  while (n != 0)
    {
      jstr_add (j, '0' + n % 10);
      n /= 10;
    }
  jstr_reverse (j);
  return j;
}


char* int_to_regstr (int n)
{
  jstr j = int_to_jstr (n);
  char* str = jstr_to_regstr (j);
  jstr_destroy (j);
  return str;
}
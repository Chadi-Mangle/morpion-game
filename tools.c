#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "tools.h"

void regstr_destroy (char** sstr)
{
	regstr_destroy_of_len (sstr, strlen (*sstr));
}

void regstr_destroy_of_len (char** sstr, int len)
{
	char* str = *sstr;
	tools_free (str, sizeof (char) * (len + 1));
	*sstr = NULL;
}

bool regstr_equal (char* str1, char* str2)
{
	int i = 0;
	while ((str1[i] != '\0') && (str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return FALSE;
		i++;
	}
	/*
	if (ste1[i] == str2[i])
		return TRUE;
	else
	return FALSE;	
	*/
	return str1[i] == str2[i];
}


char* regstr_clone (char* str)
{
	int len = strlen (str);
	char* clone = (char*) tools_malloc (sizeof (char) * (len + 1));
	int i;
	for (i = 0; i < len; i++)
		clone[i] = str[i];
	clone[i] = '\0';
	return clone;
}

int tool_random_int (int vmin, int vmax)
{
	int amp = vmax - vmin + 1;
	double _alea = (1.0 * rand () / INT_MAX) * amp;
	int alea = (int) (vmin + _alea);
	if (alea < vmin)
		alea = vmin;
	else if (alea > vmax)
		alea = vmax;
	return alea;
}


/*
	le for est exécuté b fois exactement.
	Dans ce for, il y a 5 opérations élémentaires:
	- une mul;
	- une addition;
	- deux affectations;
	- un test d'égalité.

	Nombre d'opérations élémentaires total:
	5 * b=> de ordre de b.

	La complexité algorithmique en temps
	de puiss_iter est :
	- de l'ordre de b. 
	- fontion linéaire de b;
 */
float puiss_iter (float a, int b)
{
	float r = 1;
	int i;
	if (b < 0)
		return 1.0 / puiss_iter (a, -b);
	for (i = 1; i <= b; i++)
		/*printf(" iter i = %d\n", i);*/
		r *= a;

	return r;
}

/* 
	La complexité en temps de puiss_rec est
	fonction linéaire de b car il y a exactement
	b appels récursifs.
*/
float puiss_rec (float a, int b)
{
	if (b < 0)
		return 1.0 / puiss_rec (a, -b);
	else if (b == 0)
		return 1.0;
	else /*b > 0 */
	/*printf(" rec b = %d\n", b);*/
	return a * puiss_rec (a, b - 1);
}
/*
	c (b) 
	2^ = b
	c (b) = log_2 (b)

	x |-> log_2 (x)
	est la réciproque sur ]0 ; +infini[
	de x |-> 2^x.
	
	La complexitè logarthimique 
	La complexité est une fonction logarithmique de b.

*/
float puiss_alex (float a, int b)
{
	if (b < 0)
		return 1.0 / puiss_rec (a, -b);
	else if (b == 0)
		return 1.0;
	else if ( b % 2 == 0)
	{	
		/*printf(" rec b = %d\n", b);*/
		return puiss_alex (a * a, b / 2);
	}
	else /* b % 2 == 1 */
	{
			/*printf(" rec b = %d\n", b);*/
			return a * puiss_alex (a * a, (b - 1) / 2);
	}
}



void tools_memory_init (void)
{
	GLOBAL_ALLOC_MEMORY = 0;	
}

void* tools_malloc (int alloc)
{
	void* ptr = malloc (alloc);
	GLOBAL_ALLOC_MEMORY += alloc;
	return ptr;
}

void tools_free (void* ptr, int alloc)
{
	free (ptr);
	GLOBAL_ALLOC_MEMORY -= alloc;
}

void tools_memory_check_at_end_of_app (void)
{
	if (GLOBAL_ALLOC_MEMORY != 0)
		printf ("Ce programme a une ou fuite(s) de mémoire. \n%d octets n'ont pas été libérés.", GLOBAL_ALLOC_MEMORY);
}

void int_swap (int* m, int* n)
{
  int tmp = *m;
  *m = *n;
  *n = tmp;
}

void char_swap (char* m, char* n)
{
  char tmp = *m;
  *m = *n;
  *n = tmp;
}

int safe_string_to_int (char* str, int* ok );
/*
	pour chaque caractére c de str :
	resultat *= 10;
	resultat += (c - 48);
*/
int string_to_int (char* str)
{
	int ok;
	int n = safe_string_to_int (str, &ok);
	if (ok == 0)
		printf("string_to_int : la chaîne %s n'est pas mumérique. \n",str );

	return n;
}

int get_int (int minv, int maxv)
{
	int n;
	scanf ("%d", &n);
	while ((n < minv) || (n > maxv))
	{
		printf ("min = %d ; max = %d. Recommencez :", minv, maxv);
		scanf ("%d", &n);

	}
return n;
}


/*
	ok vaut 1 si pas de caractére autre que '0' ou '9'
	ok vaut o sinon
*/

int safe_string_to_int (char* str, int* ok )
{
	if (str[0]== '-')
		return -safe_string_to_int (str + 1, ok);

	*ok = 1;
	if (str[0] == '\0')
	{
		*ok = 0;
		return 0;
	}
	int n = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < '0') || (str[i] > '9'))
			{
		
				*ok = 0;
			}
		n *= 10;
		n += (str[i] - 48);
		i++;
	}
return n;
}

void int_normalize_and_warn (int *n, int minv, int maxv)
{
	if (*n < minv)
		{
			fprintf (stderr, "int %d normalized to %d.\n", minv);
			*n = minv;
		}
	else if (*n > maxv)
	{
			fprintf (stderr, "int %d normalized to %d.\n", maxv);
			*n = maxv;
	}
}

void int_normalize (int *n, int minv, int maxv)
{
	if (*n < minv)
		*n = minv;
	else if (*n > maxv)
	*n = maxv;

}
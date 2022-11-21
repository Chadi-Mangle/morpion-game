#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char bool;
#define TRUE 1
#define FALSE 0

int GLOBAL_ALLOC_MEMORY;

void tools_memory_init (void);
void* tools_malloc (int alloc);
void tools_free (void* ptr, int alloc);
void tools_memory_check_at_end_of_app (void);

int tool_random_int (int vmin, int vmax);


/* regstr = regular str = string with a terminal '\0' */
typedef char* regstr;

void int_swap (int* m, int* n);
void char_swap (char* m, char* n);

int string_to_int (char* str);

/*
	ok vaut 1 si pas de caractére autre que '0' ou '9'
	ok vaut o sinon
*/
int safe_string_to_int (char* str, int* ok );

/*
	il faudra mieux bétonner cette fonction
	quand jstr sera compélté pour lire n'importe quelle entrée.

*/
int get_int (int minv, int maxv);

float puiss_iter (float a, int b);
float puiss_rec (float a, int b);
float puiss_alex (float a, int b);

void int_normalize_and_warn (int *n, int minv, int maxv);
void int_normalize (int *n, int minv, int maxv);

char* regstr_clone (char* str);
void regstr_destroy (char** sstr);

void regstr_destroy_of_len (char** sstr, int len);

bool regstr_equal (char* str1, char* str2);

#endif 
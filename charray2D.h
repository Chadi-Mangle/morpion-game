#ifndef __CHARRAY2D_H__
#define __CHARRAY2D_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tools.h"
#include "file.h"



/* j = numéro de ligne et i = numéro de colonne */
/* y = numéro de ligne et x = numéro de colonne */
/*
	méthode 1 : char** ; "adressage" lent ; plus simple
	méthode 2 : char* ; "adressage" plus rapide ; plus comliqué à utiliser
	méthode 3 : char* / char** ; "adressage" rapide ; plus simple à utiliser
*/

typedef struct _charray S_charray;
typedef struct _charray* charray;

struct _charray {
	int w; /* width */ 
	int h; /* height */
	char bg;
	char* data;
	char** pixel;
};

/* méthode 2

A->data = tools_malloc (sizeof (char) * A->w * A->h);
*/

/*méthode 1

data est un charr*
data[j] est un char*

pour accéder a un lignes
for (x = 0, x < TOTO->w; x++);
printf ("%c, data[y][x] );

=>fragmentation de la mémoire
data[y][x]

data + sizeof (char*) * y + sizeof (char) * x


*/

charray charray_create (int w, int h, char bg); /* bg = bakground */

void charray_destroy (charray* A);

void charray_debug (charray A);

void charray_fill (charray A, char bg);

char charray_get (charray A, int x, int y);
void charray_set (charray A, int x, int y, char value);

/* src et tar doivent être deux charrays différents */
void charray_copy (charray src, int sx1, int sy1,
				   charray tar, int tx1, int ty1, int w, int h);

/* src et tar doivent être deux charrays différents */
void charray_copy_alpha (charray src, int sx1, int sy1,
				   charray tar, int tx1, int ty1, int w, int h);

charray charray_crop (charray A, int x1, int y1, int w, int h);

charray charray_clone (charray A);

/* primitives géométriques */

void charray_draw_hor_line (charray A, int x1, int x2, int y, char c);
void charray_draw_ver_line (charray A, int x, int y1, int y2, char c);

void charray_draw_empty_box (charray A, int x1, int y1,
							 int x2, int y2, char c);

void charray_draw_filled_box (charray A, int x1, int y1,
							 int x2, int y2, char c);

void charray_draw_disk (charray A, int cx, int cy, float radius, char c);

void charray_write (charray A, file F);


void charray_save (charray A, char* filename);

charray charray_read (file F);

charray charray_load (char* filename);


#endif
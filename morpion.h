#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <math.h>*/

#include "charray2D.h"
#include "tools.h"

typedef struct _morpion* morpion;

struct _morpion {
	charray grid;
	char player; /* 'X' ou 'O' */
	char status; /*  'X' si 'X' gagne. 'O' si 'O' gagne. '?' si nul. '.' sinon */
	int nb_empty;
};



morpion morpion_init (void);
void morpion_destroy (morpion* M);

void morpion_display (morpion M);
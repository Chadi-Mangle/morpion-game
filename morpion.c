#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <math.h>*/

#include "charray2D.h"
#include "tools.h"
#include "morpion.h"

void morpion_swap_player (morpion M)
{
	if (M->player == 'X')
		M->player = 'O';
	else 
		M->player = 'X';
}

void morpion_saisie (morpion  M, int* i, int *j)
{
	printf ("Joueur %c, à vous de jouer !\n", M->player);
	printf ("Entrez le numéro de colonne : ");
	*i = get_int (0, M->grid->w - 1);
	printf ("Entrez le numéro de ligne : ");
	*j = get_int (0, M->grid->h - 1);
	printf ("\n");
	while (M->grid->pixel[*j][*i] != '.')

	{
		printf ("CASE DEJA OCCUPEE. Recommencez.\n");
		printf ("Entrez le numéro de colonne : ");
		*i = get_int (0, M->grid->w - 1);
		printf ("Entrez le numéro de ligne : ");
		*j = get_int (0, M->grid->h - 1);
		printf ("\n");
	}
}

void morpion_end (morpion M)
{
	morpion_swap_player (M);
	if (M->status == '?')
		printf ("Match nul !\n\n");
	else
		printf ("Le jouer %c a gagné !\n\n", M->player);
}

void morpion_tests_hor (morpion M, int i, int j)
{
	int jj, ii;
	for (jj = j; jj <= j + 4; jj++)
	{
		int nb_align = 1;
		for (ii = i + 1; ii <= i +4; ii++)
		{
			if ((M->grid->pixel[jj][ii] != '.') && (M->grid->pixel[jj][ii] == M->grid->pixel[jj][ii - 1]))
				nb_align++;
		}
		if (nb_align >= 5)
			M->status = M->player;
	} 
}

void morpion_tests_ver (morpion M, int i, int j)
{
	int jj, ii;
	for (ii = i; ii <= i + 4; ii++)
	{
		int nb_align = 1;
		for (jj = j + 1; jj <= j +4; jj++)
		{
			if ((M->grid->pixel[jj][ii] != '.') && (M->grid->pixel[jj][ii] == M->grid->pixel[jj -1][ii]))
				nb_align++;
		}
		if (nb_align >= 5)
			M->status = M->player;
	} 
}
/* \ */
void morpion_tests_diag1 (morpion M, int i, int j)
{
	int nb_align = 1;
	int ii, jj = j;
	for (ii = i; ii <= i + 3; ii++)
	{
		if ((M->grid->pixel[jj][ii] != '.') && (M->grid->pixel[jj][ii] == M->grid->pixel[jj + 1][ii + 1]))
		nb_align++;

		jj++;
	}
	if (nb_align >= 5)
		M->status = M->player;
}

/* / */
void morpion_tests_diag2 (morpion M, int i, int j)
{
	int nb_align = 1;
	int ii, jj = j;
	for (ii = i + 4; ii >= i + 1; ii--)
	{
		if ((M->grid->pixel[jj][ii] != '.') && (M->grid->pixel[jj][ii] == M->grid->pixel[jj + 1][ii - 1]))
		nb_align++;

		jj++;
	}
	if (nb_align >= 5)
		M->status = M->player;
}

void morpion_tests (morpion M)
{
	int j, i;
	for (j = 0; j <= M->grid->h -5; j++)
	{
		for (i = 0; i <= M->grid->w -5; i++ )
		{
			morpion_tests_hor (M, i, j);
			morpion_tests_ver (M, i, j);
			morpion_tests_diag1 (M, i, j);
			morpion_tests_diag2 (M, i, j);
		}
	}
	if ((M->nb_empty == 0) && (M->status == '.'))
		M->status = '?';
}


void morpion_play (morpion M)
{
	int j, i; /* numéro ligne, numéro colonne */
	morpion_display (M);
	while (M->status == '.')
	{
		morpion_saisie (M, &i, &j);
		M->grid->pixel[j][i] = M->player;
		M->nb_empty--;
		morpion_tests (M); 
		morpion_display (M);
		morpion_swap_player (M);

			
	}
	morpion_end (M);
}


int main(int argc, char** argv[])
{
	tools_memory_init ();
	{	
		morpion M = morpion_init();

		morpion_play (M);

		morpion_destroy (&M);
		tools_memory_check_at_end_of_app ();
	}		
}

morpion morpion_init (void)
{
	morpion M = tools_malloc (sizeof (struct _morpion));
	M->player = 'O';
	M->status = '.';
	M->grid = charray_create (9, 9, '.');
	M->nb_empty = 81;
	return M;
}

void morpion_destroy (morpion* MM)
{
	morpion M = *MM;
	charray_destroy (&(M->grid));
	tools_free (M, sizeof (struct _morpion));
	*MM = NULL;
}

void morpion_display (morpion M)
{
	int j, i;
	printf("   0 1 2 3 4 5 6 7 8\n");
	for (j = 0; j < M->grid->h; j++)
	{
		printf("%d ", j);
			for (i = 0; i < M->grid->w; i++)
			printf(" %c", M->grid->pixel[j][i]);
		printf("\n");
	}
	printf("\n");
}
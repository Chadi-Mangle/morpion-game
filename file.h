#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_BUFFER_SIZE 4096

#define FILE_READ_ONLY 0
#define FILE_WRITE_ONLY 1

#define FILE_EOF 500


typedef struct _file* file;

struct _file {
	char* filename;
	int handler;
	int mode;
	char* buffer;
	int len; /* 0 <= len <= FILE_BUFFER_SIZE */
	int cursor; /* 0 <= cursor <= len -1 */

};

file file_open (char* filename, int mode);

void file_close (file* FF);

/* return FILE_EOF when the end of file F reached */
int file_read_char (file F);

int file_read_char_and_stop (file F);

void file_go_to_next_char (file F);

void file_write_char (file F, char c);

void file_write_string (file F, char* str);

/*tente de lire le prochain int qui apparait dans F
aprés avoir ignoré tous les cractéres : ' ' , '\n', CR , LF.....
 */
void file_read_next_text_int (file F, int* nn, bool* is_integral, bool *eof);

/* tente de lire un int à la position actuelle dans F*/
void file_read_text_int (file F, int* nn, bool* is_integral, bool *eof);

void file_write_text_int (file F, int n);

void file_write_binary_int32 (file F, int n);

void file_read_binary_int32 (file F, int* n, bool* eof);

/* homologue de read ; retourne le nombre d'octes effectivement lu */
int file_read (file F, void* buffer, int nb_to_read);

/* homologue de read */
void file_write (file F, void* buffer, int nb_to_write);

/*
  peut*étre double emploi avec file_write_string
  vérifier et virer le doublon si nécessaire.
*/
void file_write_str (file F, char* str);

void file_read_str_of_len (file F, int len, char** sstr, bool* eof);

void file_read_str_until_sep (file F, char** str, bool* eof);

void file_read_next_text_str (file F, char** str, bool *eof);


#endif 
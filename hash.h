#include "lista.h"

typedef struct {
  char *valor; 
  Lista *listaPostagens;
} Palavra;

typedef struct hash Hash;

Hash* criaHash(int);
void liberaHash(Hash*);
int valorString(char*);
int insereHash(Hash*, char*, Postagem);
int buscaPalavra(Hash*, char*, Palavra*);
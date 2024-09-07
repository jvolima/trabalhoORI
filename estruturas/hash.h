#include "set.h"

#pragma once
typedef struct {
  char *valor; 
  Set *postagens;
} Palavra;

typedef struct hash Hash;

Hash* criaHash(int);
void liberaHash(Hash*);
int valorString(char*);
int insereHash(Hash*, char*, Postagem);
Set* buscaPostagens(Hash*, char*, int*);
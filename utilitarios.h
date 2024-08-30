#include "set/set.h"
#include "hash/hash.h"

int palavraComposta(char*, int, int);
void limparString(char*);
char** separarBuscaEmComponentes(char*, int*);
char** converterComponentesParaPostfix(char**, int, int*);
Set* avaliarPostfix(Hash*, char**, int); 

#include "estruturas/hash.h"

int palavraComposta(char*, int, int);
void limparString(char*);
char** separarBuscaEmComponentes(char*, int*);
char** converterComponentesParaPostfix(char**, int, int*, int*);
Set* avaliarPostfix(Hash*, char**, int, int*); 

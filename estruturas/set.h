#include "arvoreAvl.h"

typedef struct set Set;

Set* criaSet();
void liberaSet(Set* s);
int insereSet(Set* s, Postagem postagem);
int tamanhoSet(Set* s);
int consultaSet(Set* s, Postagem postagem);
Set* uniaoSet(Set* A, Set* B);
Set* interseccaoSet(Set* A, Set* B);
Set* interseccaoSetComNot(Set* A, Set* B);
void beginSet(Set *s);
int endSet(Set *s);
void nextSet(Set *s);
void getItemSet(Set *s, Postagem *postagem);
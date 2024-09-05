#include "hash.h"

typedef struct No *ArvRB;

ArvRB* criaArvRB();
void insereArvRB(ArvRB *, Palavra);
void insereArvRBFixup(ArvRB*, struct No*);
int buscaChave(ArvRB*, char*, Palavra*);
int adicionarPostagem(ArvRB*, Palavra, Postagem);
void liberaArvRB(ArvRB*);
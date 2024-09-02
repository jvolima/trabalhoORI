#include "hash.h"

typedef struct no No;

struct no {
  Palavra info;
  No *esq;
  No *dir;
  No *pai;
  char cor;
};

typedef No *ArvRB;

ArvRB* criaArvRB();
int buscaChave(ArvRB*, char*, Palavra*);
int adicionarPostagem(ArvRB*, Palavra, Postagem);
void insereArvRB(ArvRB *, Palavra);
void insereArvRBFixup(ArvRB*, No *);
void liberaArvRB(ArvRB*);
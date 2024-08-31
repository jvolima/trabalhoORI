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

ArvRB *cria_arv_rb();
int busca_chave(ArvRB*, char*, Palavra*);
int adicionar_postagem(ArvRB*, Palavra, Postagem);
void red_black_insert(ArvRB *, Palavra);
void red_black_insert_fixup(ArvRB*, No *);
void libera_red_black(ArvRB*);
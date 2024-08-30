#include "../hash/lista.h"

struct iterator {
  Postagem valor;
  struct iterator *prox;
};

typedef struct No* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, Postagem data);
int consulta_ArvAVL(ArvAVL *raiz, Postagem valor);
void iterator_ArvAVL(ArvAVL *raiz, struct iterator **iter);
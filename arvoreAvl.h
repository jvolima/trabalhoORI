struct iterator {
  int valor;
  struct iterator *prox;
};

typedef struct No* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_ArvAVL(ArvAVL *raiz);
int insere_ArvAVL(ArvAVL *raiz, int data);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void iterator_ArvAVL(ArvAVL *raiz, struct iterator **iter);
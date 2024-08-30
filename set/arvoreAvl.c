#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h" 

struct No {
  Postagem info;
  int altura;
  struct No *esq;
  struct No *dir;
};

ArvAVL* cria_ArvAVL() {
  ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
  if (raiz != NULL) {
    *raiz = NULL;
  }

  return raiz;
}

void libera_No(struct No* no) {
  if (no == NULL) {
    return;
  }

  libera_No(no->esq);
  libera_No(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz) {
  if (raiz == NULL) {
    return;
  }

  libera_No(*raiz);
  free(raiz);
}

int altura_No(struct No* no) {
  if (no == NULL) {
    return -1;
  }
    
  return no->altura;
}

int fatorBalanceamento_No(struct No* no) {
  return labs(altura_No(no->esq) - altura_No(no->dir));
}

int maior(int x, int y) {
  if (x > y) {
    return x;
  }
     
  return y;
}

int consulta_ArvAVL(ArvAVL *raiz, Postagem valor) {
  if (raiz == NULL) {
    return 0;
  }

  struct No* atual = *raiz;
  while (atual != NULL) {
    if (valor.rrn == atual->info.rrn) {
      return 1;
    }

    if (valor.rrn > atual->info.rrn) {
      atual = atual->dir;
    } else { 
      atual = atual->esq;
    }
  }

  return 0;
}

void RotacaoLL(ArvAVL *A) {
  struct No *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(altura_No((*A)->esq),altura_No((*A)->dir)) + 1;
  B->altura = maior(altura_No(B->esq),(*A)->altura) + 1;
  *A = B;
}

void RotacaoRR(ArvAVL *A) {
  struct No *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(altura_No((*A)->esq),altura_No((*A)->dir)) + 1;
  B->altura = maior(altura_No(B->dir),(*A)->altura) + 1;
  (*A) = B;
}

void RotacaoLR(ArvAVL *A) {
  RotacaoRR(&(*A)->esq);
  RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A) {
  RotacaoLL(&(*A)->dir);
  RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, Postagem valor){
  int res;
  if (*raiz == NULL) {
    struct No *novo;
    novo = (struct No*)malloc(sizeof(struct No));
    if(novo == NULL) {
      return 0;
    }

    novo->info = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;

    return 1;
  }

  struct No *atual = *raiz;
  if (valor.rrn < atual->info.rrn) {
    if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
      if (fatorBalanceamento_No(atual) >= 2) {
        if (valor.rrn < (*raiz)->esq->info.rrn) {
          RotacaoLL(raiz);
        } else {
          RotacaoLR(raiz);
        }
      }
    }
  } else {
    if(valor.rrn > atual->info.rrn) {
      if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
        if (fatorBalanceamento_No(atual) >= 2) {
          if ((*raiz)->dir->info.rrn < valor.rrn) {
            RotacaoRR(raiz);
          } else {
            RotacaoRL(raiz);
          }
        }
      }
    } else {
      return 0;
    }
  }

  atual->altura = maior(altura_No(atual->esq),altura_No(atual->dir)) + 1;

  return res;
}

struct No* procuraMenor(struct No* atual) {
  struct No *no1 = atual;
  struct No *no2 = atual->esq;
  while (no2 != NULL) {
    no1 = no2;
    no2 = no2->esq;
  }

  return no1;
}

void iterator_ArvAVL(ArvAVL *raiz, struct iterator **iter){
  if (raiz == NULL) {
    return;
  }

  if (*raiz != NULL) {
    iterator_ArvAVL(&((*raiz)->esq),iter);

    struct iterator* no;
    no = (struct iterator*) malloc(sizeof(struct iterator));
    no->valor = (*raiz)->info;
    no->prox = *iter;
    *iter = no;

    iterator_ArvAVL(&((*raiz)->dir),iter);
  }
}
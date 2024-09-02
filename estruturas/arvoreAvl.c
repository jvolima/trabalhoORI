#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h" 

struct No {
  Postagem info;
  int altura;
  struct No *esq;
  struct No *dir;
};

ArvAVL* criaArvAVL() {
  ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
  if (raiz != NULL) {
    *raiz = NULL;
  }

  return raiz;
}

void liberaNoAVL(struct No* no) {
  if (no == NULL) {
    return;
  }

  liberaNoAVL(no->esq);
  liberaNoAVL(no->dir);
  free(no);
  no = NULL;
}

void liberaArvAVL(ArvAVL* raiz) {
  if (raiz == NULL) {
    return;
  }

  liberaNoAVL(*raiz);
  free(raiz);
}

int alturaNo(struct No* no) {
  if (no == NULL) {
    return -1;
  }
    
  return no->altura;
}

int fatorBalanceamentoNo(struct No* no) {
  return labs(alturaNo(no->esq) - alturaNo(no->dir));
}

int maior(int x, int y) {
  if (x > y) {
    return x;
  }
     
  return y;
}

int consultaArvAVL(ArvAVL *raiz, Postagem valor) {
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

void rotacaoLL(ArvAVL *A) {
  struct No *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
  B->altura = maior(alturaNo(B->esq), (*A)->altura) + 1;
  *A = B;
}

void rotacaoRR(ArvAVL *A) {
  struct No *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(alturaNo((*A)->esq),alturaNo((*A)->dir)) + 1;
  B->altura = maior(alturaNo(B->dir),(*A)->altura) + 1;
  (*A) = B;
}

void rotacaoLR(ArvAVL *A) {
  rotacaoRR(&(*A)->esq);
  rotacaoLL(A);
}

void rotacaoRL(ArvAVL *A) {
  rotacaoLL(&(*A)->dir);
  rotacaoRR(A);
}

int insereArvAVL(ArvAVL *raiz, Postagem valor){
  int res;
  if (*raiz == NULL) {
    struct No *novo;
    novo = (struct No*) malloc(sizeof(struct No));
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
    if ((res = insereArvAVL(&(atual->esq), valor)) == 1) {
      if (fatorBalanceamentoNo(atual) >= 2) {
        if (valor.rrn < (*raiz)->esq->info.rrn) {
          rotacaoLL(raiz);
        } else {
          rotacaoLR(raiz);
        }
      }
    }
  } else {
    if(valor.rrn > atual->info.rrn) {
      if ((res = insereArvAVL(&(atual->dir), valor)) == 1) {
        if (fatorBalanceamentoNo(atual) >= 2) {
          if ((*raiz)->dir->info.rrn < valor.rrn) {
            rotacaoRR(raiz);
          } else {
            rotacaoRL(raiz);
          }
        }
      }
    } else {
      return 0;
    }
  }

  atual->altura = maior(alturaNo(atual->esq), alturaNo(atual->dir)) + 1;

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

void iteratorArvAVL(ArvAVL *raiz, struct iterator **iter){
  if (raiz == NULL) {
    return;
  }

  if (*raiz != NULL) {
    iteratorArvAVL(&((*raiz)->esq),iter);

    struct iterator* no;
    no = (struct iterator*) malloc(sizeof(struct iterator));
    no->valor = (*raiz)->info;
    no->prox = *iter;
    *iter = no;

    iteratorArvAVL(&((*raiz)->dir),iter);
  }
}
#include <stdio.h>
#include <stdlib.h>
#include "arvoreAvl.h" 

struct No {
  Postagem info;
  int altura;
  struct No *esq;
  struct No *dir;
};

// Função para criar a árvore AVL
ArvAVL* criaArvAVL() {
  ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
  if (raiz != NULL) {
    *raiz = NULL;
  }

  return raiz;
}

// Função para retornar a altura do nó informado
int alturaNo(struct No* no) {
  if (no == NULL) {
    return -1;
  }
    
  return no->altura;
}

// Função para retornar o fator de balanceamento do nó informado
int fatorBalanceamentoNo(struct No* no) {
  return labs(alturaNo(no->esq) - alturaNo(no->dir));
}

// Função para calcular o maior valor entre dois inteiros 
int maior(int x, int y) {
  if (x > y) {
    return x;
  }
     
  return y;
}

// Função para verificar se existe um nó na árvore com o valor informado
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

// Função para rotacionar à direita
void rotacaoLL(ArvAVL *A) {
  struct No *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
  B->altura = maior(alturaNo(B->esq), (*A)->altura) + 1;
  *A = B;
}

// Função para rotacionar à esquerda
void rotacaoRR(ArvAVL *A) {
  struct No *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(alturaNo((*A)->esq),alturaNo((*A)->dir)) + 1;
  B->altura = maior(alturaNo(B->dir),(*A)->altura) + 1;
  (*A) = B;
}

// Função para rotacionar à esquerda e depois à direita
void rotacaoLR(ArvAVL *A) {
  rotacaoRR(&(*A)->esq);
  rotacaoLL(A);
}

// Função para rotacionar à direita e depois à esquerda
void rotacaoRL(ArvAVL *A) {
  rotacaoLL(&(*A)->dir);
  rotacaoRR(A);
}

// Função para inserir valor na árvore AVL
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

// Função para percorrer a árvore AVL em ordem e armazenar os elementos no iterator
void iteratorArvAVL(ArvAVL *raiz, struct iterator **iter){
  if (raiz == NULL) {
    return;
  }

  if (*raiz != NULL) {
    iteratorArvAVL(&((*raiz)->esq), iter);

    struct iterator* no;
    no = (struct iterator*) malloc(sizeof(struct iterator));
    no->valor = (*raiz)->info;
    no->prox = *iter;
    *iter = no;

    iteratorArvAVL(&((*raiz)->dir), iter);
  }
}

// Função para liberar nó da árvore AVL
void liberaNoAVL(struct No* no) {
  if (no == NULL) {
    return;
  }

  liberaNoAVL(no->esq);
  liberaNoAVL(no->dir);
  free(no);
  no = NULL;
}

// Função para liberar árvore AVL
void liberaArvAVL(ArvAVL* raiz) {
  if (raiz == NULL) {
    return;
  }

  liberaNoAVL(*raiz);
  free(raiz);
}
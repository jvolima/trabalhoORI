#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreRb.h"

#define BLACK '0'
#define RED '1'

struct No {
  Palavra info;
  struct No *esq;
  struct No *dir;
  struct No *pai;
  char cor;
};

// Função para criar árvore rubro-negra
ArvRB *criaArvRB() {
  ArvRB *raiz = (ArvRB*) malloc(sizeof(ArvRB));
  if (raiz != NULL) {
    *raiz = NULL;
  }

  return raiz;
}

// Função para verificar se existe um nó na árvore com o valor informado
int buscaChave(ArvRB *raiz, char *valor, Palavra *palavra) {
  if (raiz == NULL) {
    return 0; 
  }

  struct No *atual = *raiz;
  while (atual != NULL) {
    if (strcmp(valor, atual->info.valor) == 0) {
      *palavra = atual->info;
      return 1; 
    }

    if (strcmp(valor, atual->info.valor) > 0) {
      atual = atual->dir; 
    } else {
      atual = atual->esq;
    }
  }

  return 0; 
}

int adicionarPostagem(ArvRB *raiz, Palavra valor, Postagem postagem) {
  if (raiz == NULL) {
    return 0;
  }

  struct No *atual = *raiz; 
  while (atual != NULL) {
    if (strcmp(valor.valor, atual->info.valor) == 0) {
      insereSet(atual->info.postagens, postagem);
      return 1; 
    }

    if (strcmp(valor.valor, atual->info.valor) > 0) {
      atual = atual->dir; 
    } else {
      atual = atual->esq;
    }
  }

  return 0; 
}

// Função para rotacionar à esquerda
struct No *rotacaoEsquerda(ArvRB *raiz, struct No *novo) {
  struct No *filhoDir = novo->dir; 
  novo->dir = filhoDir->esq; 

  if (filhoDir->esq != NULL) {
    filhoDir->esq->pai = novo;
  }

  filhoDir->pai = novo->pai;
  if (novo->pai == NULL) {
    *raiz = filhoDir;
  } else if (novo == novo->pai->esq) {
    novo->pai->esq = filhoDir;
  } else {
    novo->pai->dir = filhoDir; 
  }

  filhoDir->esq = novo;
  novo->pai = filhoDir;

  return novo->pai;
}

// Função para rotacionar à direita
struct No *rotacaoDireita(ArvRB *raiz, struct No *novo) {
  struct No *filhoEsq = novo->esq; 
  novo->esq = filhoEsq->dir;

  if (filhoEsq->dir != NULL) {
    filhoEsq->dir->pai = novo;
  }

  filhoEsq->pai = novo->pai;
  if (novo->pai == NULL) {
    *raiz = filhoEsq;
  } else if (novo == novo->pai->dir) {
    novo->pai->dir = filhoEsq;
  } else {
    novo->pai->esq = filhoEsq;
  }

  filhoEsq->dir = novo;
  novo->pai = filhoEsq;

  return novo->pai;
}

// Função para rotacionar à esquerda e depois à direita
struct No *rotacaoEsquerdaDireita(ArvRB *raiz, struct No *novo) {
  struct No *filhoEsq = novo->esq;
  rotacaoEsquerda(raiz, filhoEsq);
  return rotacaoDireita(raiz, novo);
}

// Função para rotacionar à direita e depois à esquerda
struct No *rotacaoDireitaEsquerda(ArvRB *raiz, struct No *novo) {
  struct No *filhoDir = novo->dir;
  rotacaoDireita(raiz, filhoDir);
  return rotacaoEsquerda(raiz, novo);
}

// Função para inserir valor na árvore rubro-negra
void insereArvRB(ArvRB *raiz, Palavra info) {
  if (raiz == NULL) {
    return;
  }

  struct No *novo = (struct No*) malloc(sizeof(struct No));
  novo->info = info;
  novo->cor = RED; 
  novo->esq = NULL;
  novo->dir = NULL;

  struct No *atual = *raiz;
  struct No *anterior = NULL;

  while (atual != NULL) {
    anterior = atual;
    if (strcmp(novo->info.valor, atual->info.valor) > 0) {
      atual = atual->dir;
    } else {
      atual = atual->esq;
    }
  }

  if (anterior == NULL) {
    novo->cor = BLACK;
    *raiz = novo;
    novo->pai = NULL;
  } else if (strcmp(novo->info.valor, anterior->info.valor) > 0) {
    anterior->dir = novo;
    novo->pai = anterior;
  } else {
    anterior->esq = novo;
    novo->pai = anterior;
  }

  insereArvRBFixup(raiz, novo);
}

// Função para consertar propriedades da árvore rubro-negra após inserção
void insereArvRBFixup(ArvRB *raiz, struct No *novo) {
  while (novo->pai != NULL && novo->pai->cor == RED) {
    if (novo->pai->pai != NULL && novo->pai == novo->pai->pai->esq) {
      struct No *tio = novo->pai->pai->dir; 
      if (tio != NULL && tio->cor == RED) {
        novo->pai->cor = BLACK;
        tio->cor = BLACK;
        novo->pai->pai->cor = RED;
        novo = novo->pai->pai;
      } else {
        if (novo == novo->pai->dir) {
          novo->pai->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoEsquerdaDireita(raiz, novo->pai->pai);
          }
        } else {
          novo->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoDireita(raiz, novo->pai->pai);
          }
        }
      }
    } else {
      struct No *tio = novo->pai->pai->esq;
      if (tio != NULL && tio->cor == RED) {
        novo->pai->cor = BLACK;
        tio->cor = BLACK;
        novo->pai->pai->cor = RED;
        novo = novo->pai->pai;
      } else {
        if (novo == novo->pai->esq) {
          novo->pai->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoDireitaEsquerda(raiz, novo->pai->pai);
          }
        } else {
          novo->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoEsquerda(raiz, novo->pai->pai);
          }
        }
      }
    }
  }
  (*raiz)->cor = BLACK; 
}

// Função para liberar nó da árvore rubro-negra
void liberaNoRB(ArvRB no) {
  if (no == NULL) {
    return;
  }

  liberaNoRB(no->esq);
  liberaNoRB(no->dir);
  liberaSet(no->info.postagens);
  free(no->info.valor);
  free(no);
  no = NULL;
}

// Função para liberar árvore rubro-negra
void liberaArvRB(ArvRB *raiz) {
  if (raiz == NULL) {
    return;
  }

  liberaNoRB(*raiz);
  free(raiz);
}
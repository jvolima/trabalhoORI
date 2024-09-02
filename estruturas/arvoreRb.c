// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreRb.h"

// Macros
#define BLACK '0'
#define RED '1'

// Função para criar árvore rubro-negra
ArvRB *criaArvRB() {
  // Aloca memória para a raiz da árvore e retorna um ponteiro para ela
  return (ArvRB *) malloc(sizeof(ArvRB));
}

// Função para verificar se existe um nó na árvore com o valor informado
int buscaChave(ArvRB *raiz, char *valor, Palavra *palavra) {
  if (raiz == NULL) {
    return 0; // Se a árvore estiver vazia, retorna 0 (não encontrado)
  }

  No *atual = *raiz; // Começa a busca a partir da raiz
  while (atual != NULL) {
    if (strcmp(valor, atual->info.valor) == 0) {
      *palavra = atual->info;
      return 1; // Valor encontrado, retorna 1
    }

    if (strcmp(valor, atual->info.valor) > 0) {
      atual = atual->dir; // Continua a busca no subárvore direita
    } else {
      atual = atual->esq; // Continua a busca no subárvore esquerda
    }
  }

  return 0; // Valor não encontrado, retorna 0
}

int adicionarPostagem(ArvRB *raiz, Palavra valor, Postagem postagem) {
  if (raiz == NULL) {
    return 0;
  }

  No *atual = *raiz; // Começa a busca a partir da raiz
  while (atual != NULL) {
    if (strcmp(valor.valor, atual->info.valor) == 0) {
      insereSet(atual->info.postagens, postagem);
      return 1; // Valor encontrado, retorna 1
    }

    if (strcmp(valor.valor, atual->info.valor) > 0) {
      atual = atual->dir; // Continua a busca no subárvore direita
    } else {
      atual = atual->esq; // Continua a busca no subárvore esquerda
    }
  }

  return 0; // Valor não encontrado, retorna 0
}

// Função para rotacionar à esquerda
No *rotacaoEsquerda(ArvRB *raiz, No *novo) {
  No *filhoDir = novo->dir; // Filho à direita se tornará o novo pai
  novo->dir = filhoDir->esq; // Atualiza a subárvore direita do nó original

  if (filhoDir->esq != NULL) {
    filhoDir->esq->pai = novo; // Atualiza o pai do filho à esquerda
  }

  filhoDir->pai = novo->pai; // Atualiza o pai do filho à direita
  if (novo->pai == NULL) {
    *raiz = filhoDir; // Se o nó original era a raiz, atualiza a raiz
  } else if (novo == novo->pai->esq) {
    novo->pai->esq = filhoDir; // Atualiza a subárvore esquerda do pai do nó original
  } else {
    novo->pai->dir = filhoDir; // Atualiza a subárvore direita do pai do nó original
  }

  filhoDir->esq = novo; // Coloca o nó original à esquerda do filho à direita
  novo->pai = filhoDir; // Atualiza o pai do nó original

  return novo->pai; // Retorna o novo pai
}

// Função para rotacionar à direita
No *rotacaoDireita(ArvRB *raiz, No *novo) {
  No *filhoEsq = novo->esq; // Filho à esquerda se tornará o novo pai
  novo->esq = filhoEsq->dir; // Atualiza a subárvore esquerda do nó original

  if (filhoEsq->dir != NULL) {
    filhoEsq->dir->pai = novo; // Atualiza o pai do filho à direita
  }

  filhoEsq->pai = novo->pai; // Atualiza o pai do filho à esquerda
  if (novo->pai == NULL) {
    *raiz = filhoEsq; // Se o nó original era a raiz, atualiza a raiz
  } else if (novo == novo->pai->dir) {
    novo->pai->dir = filhoEsq; // Atualiza a subárvore direita do pai do nó original
  } else {
    novo->pai->esq = filhoEsq; // Atualiza a subárvore esquerda do pai do nó original
  }

  filhoEsq->dir = novo; // Coloca o nó original à direita do filho à esquerda
  novo->pai = filhoEsq; // Atualiza o pai do nó original

  return novo->pai; // Retorna o novo pai
}

// Função para rotacionar à esquerda e depois à direita
No *rotacaoEsquerdaDireita(ArvRB *raiz, No *novo) {
  No *filhoEsq = novo->esq;
  rotacaoEsquerda(raiz, filhoEsq); // Primeiro, rotaciona à esquerda o filho à esquerda
  return rotacaoDireita(raiz, novo); // Depois, rotaciona à direita o nó original
}

// Função para rotacionar à direita e depois à esquerda
No *rotacaoDireitaEsquerda(ArvRB *raiz, No *novo) {
  No *filhoDir = novo->dir;
  rotacaoDireita(raiz, filhoDir); // Primeiro, rotaciona à direita o filho à direita
  return rotacaoEsquerda(raiz, novo); // Depois, rotaciona à esquerda o nó original
}

// Função para inserir valor na árvore rubro-negra
void insereArvRB(ArvRB *raiz, Palavra info) {
  if (raiz == NULL) {
    return;
  }

  // Cria um novo nó e inicializa seus valores
  No *novo = (No *) malloc(sizeof(No));
  novo->info = info;
  novo->cor = RED; // Novo nó sempre é inserido como vermelho
  novo->esq = NULL;
  novo->dir = NULL;

  No *atual = *raiz;
  No *anterior = NULL;

  // Percorre a árvore para encontrar a posição correta para o novo nó
  while (atual != NULL) {
    anterior = atual;
    if (strcmp(novo->info.valor, atual->info.valor) > 0) {
      atual = atual->dir;
    } else {
      atual = atual->esq;
    }
  }

  // Insere o novo nó na posição encontrada
  if (anterior == NULL) {
    novo->cor = BLACK; // Raiz sempre é preta
    *raiz = novo;
    novo->pai = NULL;
  } else if (strcmp(novo->info.valor, anterior->info.valor) > 0) {
    anterior->dir = novo;
    novo->pai = anterior;
  } else {
    anterior->esq = novo;
    novo->pai = anterior;
  }

  // Chama a função para consertar as propriedades da árvore rubro-negra
  insereArvRBFixup(raiz, novo);
}

// Função para consertar propriedades da árvore rubro-negra após inserção
void insereArvRBFixup(ArvRB *raiz, No *novo) {
  // Enquanto o pai do nó é vermelho, continua ajustando
  while (novo->pai != NULL && novo->pai->cor == RED) {
    if (novo->pai->pai != NULL && novo->pai == novo->pai->pai->esq) {
      No *tio = novo->pai->pai->dir; // Tio do nó
      if (tio != NULL && tio->cor == RED) {
        // Tio vermelho, apenas recolore
        novo->pai->cor = BLACK;
        tio->cor = BLACK;
        novo->pai->pai->cor = RED;
        novo = novo->pai->pai;
      } else {
        if (novo == novo->pai->dir) {
          // Nó é filho direito, precisa de rotação
          novo->pai->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoEsquerdaDireita(raiz, novo->pai->pai);
          }
        } else {
          // Nó é filho esquerdo, apenas rotaciona
          novo->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoDireita(raiz, novo->pai->pai);
          }
        }
      }
    } else {
      No *tio = novo->pai->pai->esq; // Tio do nó
      if (tio != NULL && tio->cor == RED) {
        // Tio vermelho, apenas recolore
        novo->pai->cor = BLACK;
        tio->cor = BLACK;
        novo->pai->pai->cor = RED;
        novo = novo->pai->pai;
      } else {
        if (novo == novo->pai->esq) {
          // Nó é filho esquerdo, precisa de rotação
          novo->pai->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoDireitaEsquerda(raiz, novo->pai->pai);
          }
        } else {
          // Nó é filho direito, apenas rotaciona
          novo->cor = BLACK;
          if (novo->pai->pai != NULL) {
            novo = rotacaoEsquerda(raiz, novo->pai->pai);
          }
        }
      }
    }
  }
  (*raiz)->cor = BLACK; // Garante que a raiz é sempre preta
}

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

void liberaArvRB(ArvRB *raiz) {
  if (raiz == NULL) {
    return;
  }

  liberaNoRB(*raiz);
  free(raiz);
}
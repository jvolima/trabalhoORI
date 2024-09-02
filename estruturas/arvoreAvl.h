#pragma once
typedef struct {
  int rrn;
  int tamanhoLinha;
} Postagem;

struct iterator {
  Postagem valor;
  struct iterator *prox;
};

typedef struct No* ArvAVL;

ArvAVL* criaArvAVL();
void liberaArvAVL(ArvAVL*);
int insereArvAVL(ArvAVL*, Postagem);
int consultaArvAVL(ArvAVL*, Postagem);
void iteratorArvAVL(ArvAVL*, struct iterator**);
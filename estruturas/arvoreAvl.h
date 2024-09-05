#pragma once
typedef struct {
  int rrn;
  int tamanhoLinha;
} Postagem;

struct iterator {
  Postagem valor;
  struct iterator *prox;
};

typedef struct No *ArvAVL;

ArvAVL* criaArvAVL();
int insereArvAVL(ArvAVL*, Postagem);
int consultaArvAVL(ArvAVL*, Postagem);
void iteratorArvAVL(ArvAVL*, struct iterator**);
void liberaArvAVL(ArvAVL*);
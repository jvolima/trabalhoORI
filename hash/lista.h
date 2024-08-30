#pragma once
typedef struct {
  int rrn;
  int tamanhoLinha;
} Postagem;

typedef struct lista Lista;

Lista* criaLista();
void liberaLista(Lista*);
int insereLista(Lista*, Postagem);
int quantidadeLista(Lista*);
Postagem* retornaLista(Lista*);
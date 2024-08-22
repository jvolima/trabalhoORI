#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define TAMANHO_INICIAL 10

struct lista {
  int quantidade;
  int tamanho;
  Postagem *postagens;
};

Lista* criaLista() {
  Lista *lista;
  lista = (Lista*) malloc(sizeof(Lista));
  lista->quantidade = 0;
  lista->tamanho = TAMANHO_INICIAL;
  lista->postagens = (Postagem*) malloc(sizeof(Postagem) * lista->tamanho);

  return lista;
}

void liberaLista(Lista *lista) {
  free(lista);
}

int insereLista(Lista *lista, Postagem postagem) {
  if (lista == NULL) {
    return 0;
  }

  for (int i = 0; i < lista->quantidade; i++) {
    if (lista->postagens[i].rrn == postagem.rrn) {
      return 0;
    }
  }

  if (lista->quantidade == lista->tamanho) {
    lista->tamanho *= 2;
    lista->postagens = (Postagem*) realloc(lista->postagens, sizeof(Postagem) * lista->tamanho);
  }

  lista->postagens[lista->quantidade] = postagem;
  lista->quantidade++;

  return 1;
}

int quantidadeLista(Lista *lista) {
  return lista->quantidade;
}

Postagem* retornaLista(Lista *lista) {
  return lista->postagens;
}
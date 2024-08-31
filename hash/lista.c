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
  Lista *lista = (Lista*) malloc(sizeof(Lista));
  
  if (lista != NULL) {
    lista->quantidade = 0;
    lista->tamanho = TAMANHO_INICIAL;
    lista->postagens = (Postagem*) malloc(sizeof(Postagem) * lista->tamanho);

    if (lista->postagens == NULL) {
      free(lista);
      return NULL;
    }
  }

  return lista;
}

void liberaLista(Lista *lista) {
  free(lista->postagens);
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
    Postagem *listaDePostagensTemporaria = (Postagem*) realloc(lista->postagens, sizeof(Postagem) * lista->tamanho * 2);
    if (listaDePostagensTemporaria == NULL) {
      // liberaLista(lista);
      return 0;
    }
    lista->tamanho *= 2;
    lista->postagens = listaDePostagensTemporaria;
  }

  lista->postagens[lista->quantidade] = postagem;
  lista->quantidade++;

  return 1;
}

int quantidadeLista(Lista *lista) {
  if (lista == NULL) {
    return 0;
  }

  return lista->quantidade;
}

Postagem* retornaLista(Lista *lista) {
  if (lista == NULL) {
    return NULL;
  }
  
  return lista->postagens;
}
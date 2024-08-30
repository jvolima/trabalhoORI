#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h" 

typedef struct no No;
struct no {
  Palavra palavra;
  No *prox;
};

struct hash {
  int tamanho;
  No **palavras;
};

Hash* criaHash(int tamanho) {
  Hash* hash = (Hash*) malloc(sizeof(Hash));

  if (hash != NULL) {
    int i;
    hash->tamanho = tamanho;
    hash->palavras = (No**) malloc(tamanho * sizeof(No*));

    if (hash->palavras == NULL) {
      free(hash);
      return NULL;
    }

    for (i = 0; i < hash->tamanho; i++) {
      hash->palavras[i] = NULL;
    }  
  }

  return hash;
}

void liberaHash(Hash *hash) {
  if (hash == NULL) {
    return;
  }

  for (int i = 0; i < hash->tamanho; i++) {
    No *atual = hash->palavras[i];

    while (atual != NULL) {
      No *temp = atual;
      atual = atual->prox;

      liberaLista(temp->palavra.listaPostagens);
      free(temp->palavra.valor);
      free(temp);
    }
  }

  free(hash->palavras);
  free(hash);
}

int valorString(char *str) {
  int i, valor = 7;
  int tam = strlen(str);

  for (i = 0; i < tam; i++) {
    valor = 31 * valor + (int) str[i];
  }

  return (valor & 0x7FFFFFFF);
}

int chaveDivisao(int chave, int TABLE_SIZE) {
  return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int insereHash(Hash *hash, char *novaPalavra, Postagem novaPostagem) {
  if (hash == NULL || hash->palavras == NULL) {
    return 0;
  }
        
  int chave = valorString(novaPalavra);
  int pos = chaveDivisao(chave, hash->tamanho);

  No *atual = hash->palavras[pos];
  No *anterior = NULL;
  while (atual != NULL) {
    if ((strcmp(atual->palavra.valor, novaPalavra) == 0)) {
      insereLista(atual->palavra.listaPostagens, novaPostagem);
      return 1;
    }
    anterior = atual;
    atual = atual->prox;
  }

  No *novo = (No*) malloc(sizeof(No));
  Palavra palavra;
  palavra.valor = (char*) malloc(strlen(novaPalavra) + 1);
  strcpy(palavra.valor, novaPalavra);
  palavra.listaPostagens = criaLista();
  insereLista(palavra.listaPostagens, novaPostagem);
  novo->palavra = palavra;
  novo->prox = NULL;

  if (anterior != NULL) {
    anterior->prox = novo;
  } else {
    hash->palavras[pos] = novo;
  }
  
  return 1;
}

int buscaPalavra(Hash *hash, char *str, Palavra *palavra) {
  if (hash == NULL || hash->palavras == NULL) {
    return 0;
  }
        
  int chave = valorString(str);
  int pos = chaveDivisao(chave, hash->tamanho);

  No *atual = hash->palavras[pos];
  while (atual != NULL) {
    if ((strcmp(atual->palavra.valor, str) == 0)) {
      *palavra = atual->palavra;
      return 1;
    }
    atual = atual->prox;
  }
  
  return 0;
}
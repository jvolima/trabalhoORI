#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h" 
#include "arvoreRb.h"

struct hash {
  int tamanho;
  ArvRB **palavras;
};

Hash* criaHash(int tamanho) {
  Hash* hash = (Hash*) malloc(sizeof(Hash));

  if (hash != NULL) {
    int i;
    hash->tamanho = tamanho;
    hash->palavras = (ArvRB**) malloc(tamanho * sizeof(ArvRB*));
  
    if (hash->palavras == NULL) {
      free(hash);
      return NULL;
    }

    for (i = 0; i < hash->tamanho; i++) {
      hash->palavras[i] = criaArvRB();
      if (hash->palavras[i] == NULL) {
        for (int j = 0; j < i; j++) {
          liberaArvRB(hash->palavras[j]);
        }
        free(hash->palavras);
        free(hash);
        return NULL;
      }
    }  
  }

  return hash;
}

void liberaHash(Hash *hash) {
  if (hash == NULL) {
    return;
  }

  for (int i = 0; i < hash->tamanho; i++) {
    liberaArvRB(hash->palavras[i]);
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

int chaveDivisao(int chave, int tamanhoHash) {
  return (chave & 0x7FFFFFFF) % tamanhoHash;
}

int insereHash(Hash *hash, char *novaPalavra, Postagem novaPostagem) {
  if (hash == NULL || hash->palavras == NULL) {
    return 0;
  }
        
  int chave = valorString(novaPalavra);
  int pos = chaveDivisao(chave, hash->tamanho);

  Palavra palavra;
  palavra.valor = (char*) malloc(strlen(novaPalavra) + 1);
  if (palavra.valor == NULL) {
    return 0;
  }
  strcpy(palavra.valor, novaPalavra);

  if (adicionarPostagem(hash->palavras[pos], palavra, novaPostagem)) {
    return 1;
  }

  palavra.postagens = criaSet();
  if (palavra.postagens == NULL) {
    return 0;
  }

  if (!insereSet(palavra.postagens, novaPostagem)) {
    return 0;
  }

  insereArvRB(hash->palavras[pos], palavra);

  return 1;
}

Set* buscaPalavra(Hash *hash, char *str, int *deuCerto) {
  *deuCerto = 0;

  if (hash == NULL || hash->palavras == NULL) {
    return NULL;
  }
        
  int chave = valorString(str);
  int pos = chaveDivisao(chave, hash->tamanho);
  Palavra palavra;

  if (!buscaChave(hash->palavras[pos], str, &palavra)) {
    return NULL;
  }

  *deuCerto = 1;
  
  return palavra.postagens;
}
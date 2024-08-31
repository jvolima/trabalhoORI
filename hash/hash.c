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
      hash->palavras[i] = cria_arv_rb();
    }  
  }

  return hash;
}

void liberaHash(Hash *hash) {
  if (hash == NULL) {
    return;
  }

  for (int i = 0; i < hash->tamanho; i++) {
    ArvRB *atual = hash->palavras[i];
    libera_red_black(atual);
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

  Palavra palavra;
  palavra.valor = (char*) malloc(strlen(novaPalavra) + 1);
  if (palavra.valor == NULL) {
    return 0;
  }
  strcpy(palavra.valor, novaPalavra);

  if (adicionar_postagem(hash->palavras[pos], palavra, novaPostagem)) {
    return 1;
  }

  palavra.listaPostagens = criaLista();
  if (palavra.listaPostagens == NULL) {
    return 0;
  }

  if (!insereLista(palavra.listaPostagens, novaPostagem)) {
    return 0;
  }

  red_black_insert(hash->palavras[pos], palavra);

  return 1;
}

int buscaPalavra(Hash *hash, char *str, Palavra *palavra) {
  if (hash == NULL || hash->palavras == NULL) {
    return 0;
  }
        
  int chave = valorString(str);
  int pos = chaveDivisao(chave, hash->tamanho);

  return busca_chave(hash->palavras[pos], str, palavra);
}
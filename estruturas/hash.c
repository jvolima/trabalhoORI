#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h" 
#include "arvoreRb.h"

struct hash {
  int tamanho;
  ArvRB **palavras;
};

// Função para criar a tabela hash
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

// Função para liberar a tabela hash
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

// Função para converter a string para um valor inteiro
int valorString(char *str) {
  int i, valor = 7;
  int tam = strlen(str);

  for (i = 0; i < tam; i++) {
    valor = 31 * valor + (int) str[i];
  }

  return (valor & 0x7FFFFFFF);
}

// Função para calcular a posição da chave na tabela hash utilizando o método da divisão
int chaveDivisao(int chave, int tamanhoHash) {
  return (chave & 0x7FFFFFFF) % tamanhoHash;
}

// Função para inserir a chave na tabela hash
int insereHash(Hash *hash, char *valor, Postagem novaPostagem) {
  if (hash == NULL || hash->palavras == NULL) {
    return 0;
  }
        
  int chave = valorString(valor);
  int pos = chaveDivisao(chave, hash->tamanho);

  Palavra palavra;
  palavra.valor = (char*) malloc(strlen(valor) + 1);
  if (palavra.valor == NULL) {
    return 0;
  }
  strcpy(palavra.valor, valor);

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

// Função para buscar postagens de uma palavra
Set* buscaPostagens(Hash *hash, char *valor, int *deuCerto) {
  *deuCerto = 0;

  if (hash == NULL || hash->palavras == NULL) {
    return NULL;
  }
        
  int chave = valorString(valor);
  int pos = chaveDivisao(chave, hash->tamanho);
  Palavra palavra;

  if (!buscaChave(hash->palavras[pos], valor, &palavra)) {
    return NULL;
  }

  *deuCerto = 1;
  
  return palavra.postagens;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define MAX_LINHA 500

int main() {
  FILE *arquivoTweets;
  Palavra palavra;
  Postagem postagem1, postagem2;
  char nome[20], linha[MAX_LINHA], *valor;

  Hash *hash = criaHash(11);

  strcpy(nome, "Joao");
  postagem1.rrn = 5;
  postagem1.tamanhoLinha = 10;
  postagem2.rrn = 7;
  postagem2.tamanhoLinha = 14;

  insereHash(hash, nome, postagem1);
  insereHash(hash, nome, postagem2);
  
  buscaPalavra(hash, "Joao", &palavra);
  printf("%s\n", palavra.valor);
  printf("%d\n", quantidadeLista(palavra.listaPostagens));
  
  arquivoTweets = fopen("teste.csv", "r");
  if (arquivoTweets == NULL) {
    printf("Erro ao abrir arquivo de tweets.");
    exit(1);
  }

  while (fgets(linha, MAX_LINHA, arquivoTweets) != NULL) {
    strtok(linha, ",");
    strtok(NULL, ",");
    valor = strtok(NULL, "\n");

    if (valor != NULL) {
        printf("%s\n", valor);
    } else {
        printf("Valor não encontrado na linha: %s\n", linha);
    }
  }

  return 0;
}

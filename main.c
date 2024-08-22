#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define MAX_LINHA 500

int main() {
  FILE *arquivoTweets;
  Palavra palavra;
  Postagem postagem1, postagem2;
  char linha[MAX_LINHA], *valor;

 Hash *hash = criaHash(11);

  valor = (char*) malloc(20 * sizeof(char));
  strcpy(valor, "Joao");
  postagem1.rrn = 5;
  postagem1.tamanhoLinha = 10;
  postagem2.rrn = 7;
  postagem2.tamanhoLinha = 14;

  insereHash(hash, valor, postagem1);
  insereHash(hash, valor, postagem2);
  
  buscaPalavra(hash, "Joao", &palavra);
  printf("%s\n", palavra.valor);
  
  arquivoTweets = fopen("corpus.csv", "r");
  if (arquivoTweets == NULL) {
    printf("Erro ao abrir arquivo de tweets.");
    exit(1);
  }

  while (1) {
    fgets(linha, MAX_LINHA, arquivoTweets);
    if (feof(arquivoTweets)) {
      break;
    }

    strtok(linha, ",");
    strtok(NULL, ",");
    valor = strtok(NULL, "\n");

    printf("%s\n", valor);
  }

  return 0;
}

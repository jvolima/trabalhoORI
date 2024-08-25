#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "utilitarios.h"

#define MAX_LINHA 500

int main() {
  FILE *arquivoTweets;
  Palavra palavra;
  Postagem postagem;
  char nome[20], linha[MAX_LINHA], *valor, *stringPalavra;

  Hash *hash = criaHash(19);
 
  arquivoTweets = fopen("teste.csv", "r");
  if (arquivoTweets == NULL) {
    printf("Erro ao abrir arquivo de tweets.");
    exit(1);
  }

  while (fgets(linha, MAX_LINHA, arquivoTweets) != NULL) {
    postagem.tamanhoLinha = strlen(linha);
    postagem.rrn = ftell(arquivoTweets) - postagem.tamanhoLinha;

    strtok(linha, ",");
    strtok(NULL, ",");
    valor = strtok(NULL, "\n");
    limparString(valor);

    stringPalavra = strtok(valor, " ");
    while (stringPalavra != NULL) {
      insereHash(hash, stringPalavra, postagem);
      stringPalavra = strtok(NULL, " ");
    }
  }

  if (buscaPalavra(hash, "so", &palavra)) {
    printf("%s\n", palavra.valor);
    printf("%d\n", quantidadeLista(palavra.listaPostagens));
  }

  return 0;
}
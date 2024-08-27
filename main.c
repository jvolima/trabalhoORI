#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "utilitarios.h"

#define MAX_LINHA 300
#define MAX_BUSCA 300

int main() {
  Hash *hash = criaHash(19);
 
  FILE *arquivoTweets = fopen("teste.csv", "r");
  if (arquivoTweets == NULL) {
    printf("Erro ao abrir arquivo de tweets.");
    exit(1);
  }

  Postagem postagem;
  char linha[MAX_LINHA], *valor, *stringPalavra;
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

  Palavra palavra;
  int escolha;
  char busca[MAX_BUSCA];
  char linhaArquivo[MAX_LINHA];
  while (1) {
    printf("(1) Buscar nova palavra\n(2) Sair da busca\n");
    scanf("%d", &escolha);

    if (escolha == 2) {
      break;
    }

    printf("Formule a sua busca utilizando operadores lógicos (AND, OR, NOT): ");
    scanf("%s", busca);

    if (!buscaPalavra(hash, busca, &palavra)) {
      printf("Palavra não encontrada.\n\n");
      continue;     
    }

    Postagem *postagens = retornaLista(palavra.listaPostagens);
    for (int i = 0; i < quantidadeLista(palavra.listaPostagens); i++) {
      fseek(arquivoTweets, postagens[i].rrn, SEEK_SET);
      fgets(linhaArquivo, postagens[i].tamanhoLinha, arquivoTweets);
      printf("%s\n", linhaArquivo);  
    }

    printf("\n");
  }

  liberaHash(hash);
  fclose(arquivoTweets);

  return 0;
}
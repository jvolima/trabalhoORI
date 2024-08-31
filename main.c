#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash/hash.h"
#include "utilitarios.h"

#define MAX_LINHA 300
#define MAX_BUSCA 300

int main() {
  Hash *hash = criaHash(19);
 
  FILE *arquivoTweets = fopen("files/teste.csv", "r");
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

  int escolha;
  char busca[MAX_BUSCA];
  while (1) {
    printf("(1) Buscar nova palavra\n(2) Sair da busca\n");
    scanf("%d", &escolha);

    if (!(escolha == 1 || escolha == 2)) {
      printf("Opção inválida!\n");
      continue;
    }

    if (escolha == 2) {
      break;
    }

    printf("Formule a sua busca utilizando operadores lógicos (AND, OR, NOT): ");
    scanf(" %[^\n]", busca);

    int numComponentes;
    char **componentes = separarBuscaEmComponentes(busca, &numComponentes);

    int tamanhoPostfix;
    char **postfix = converterComponentesParaPostfix(componentes, numComponentes, &tamanhoPostfix);

    Set *resultado = avaliarPostfix(hash, postfix, tamanhoPostfix);

    for (beginSet(resultado); !endSet(resultado); nextSet(resultado)) {
      char linhaSaida[MAX_LINHA];
      Postagem postagemSaida;

      getItemSet(resultado, &postagemSaida);
      fseek(arquivoTweets, postagemSaida.rrn, SEEK_SET);
      fgets(linhaSaida, postagemSaida.tamanhoLinha, arquivoTweets);
      printf("%s\n", linhaSaida);
    }

    for (int i = 0; i < numComponentes; i++) {
      free(componentes[i]);
    }
    free(componentes);
    free(postfix);

    printf("\n");
  }

  liberaHash(hash);
  fclose(arquivoTweets);

  return 0;
}
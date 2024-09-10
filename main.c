#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas/hash.h"
#include "utilitarios.h"

#define MAX_LINHA 1000
#define MAX_BUSCA 300

int main() {
  // Cria a hash com um número primo
  Hash *hash = criaHash(10007);
 
  FILE *arquivoTweets = fopen("files/corpus.csv", "r");
  if (arquivoTweets == NULL) {
    printf("Erro ao abrir arquivo de tweets.");
    exit(1);
  }

  // Leitura do arquivo e inserção na hash
  Postagem postagem;
  char linha[MAX_LINHA], *valor, *stringPalavra;
  while (fgets(linha, MAX_LINHA, arquivoTweets) != NULL) {
    postagem.tamanhoLinha = strlen(linha);
    postagem.rrn = ftell(arquivoTweets) - postagem.tamanhoLinha;

    strtok(linha, ",");
    strtok(NULL, ",");
    valor = strtok(NULL, "\n");
    
    // Retira caracteres especiais e espaços vazios
    limparString(valor);

    stringPalavra = strtok(valor, " ");
    while (stringPalavra != NULL) {
      insereHash(hash, stringPalavra, postagem);
      stringPalavra = strtok(NULL, " ");
    }
  }

  // Interação com o usuário
  int escolha;
  char busca[MAX_BUSCA];
  while (1) {
    printf("(1) Buscar nova palavra\n(2) Sair da busca\nOpção: ");
    if (scanf(" %d", &escolha) != 1) {
      while (getchar() != '\n');
      printf("(ERRO) Opção inválida!\n\n");
      continue;
    }

    while (getchar() != '\n'); 

    if (!(escolha == 1 || escolha == 2)) {
      printf("(ERRO) Opção inválida!\n\n");
      continue;
    }

    if (escolha == 2) {
      break;
    }

    printf("Formule a sua busca utilizando operadores lógicos (AND, OR, NOT): ");
    scanf(" %[^\n]", busca);

    // Separar a string recebida em componentes
    int numComponentes;
    char **componentes = separarBuscaEmComponentes(busca, &numComponentes);

    if (componentes == NULL || numComponentes == 0) {
      printf("(ERRO) Pesquisa inválida.\n\n");
      continue;
    }

    // Converter os componentes para o formato postfix
    int tamanhoPostfix, tipoErro;
    char **postfix = converterComponentesParaPostfix(componentes, numComponentes, &tamanhoPostfix, &tipoErro);
    
    // Tratamento de erros
    if (postfix == NULL) {
      switch (tipoErro) {
        case 1:
          printf("(ERRO) Tente novamente.\n\n");
          break;
        case 2:
          printf("(ERRO) Busca inválida.\n\n");
          break;

        default:
          printf("(ERRO) Tente novamente.\n\n");
          break;
      }
      continue;
    }

    // Encontrar postagens relacionadas a busca com base no postfix
    Set *resultado = avaliarPostfix(hash, postfix, tamanhoPostfix, &tipoErro);

    // Tratamento de erros
    if (resultado == NULL) {
      switch (tipoErro) {
        case 1:
          printf("(ERRO) Necessário ao menos duas palavras para utilizar operadores lógicos AND ou OR.\n\n");
          break;
        case 2:
          printf("(ERRO) Conjunto universo não deve ser utilizado.\n\n");
          break;
        case 3:
          printf("Nenhuma postagem encontrada.\n\n");
          break;

        default:
          printf("(ERRO) Tente novamente.\n\n");
          break;
      }

      continue;
    }

    // Imprimir postagens encontradas na busca
    for (beginSet(resultado); !endSet(resultado); nextSet(resultado)) {
      char linhaSaida[MAX_LINHA];
      Postagem postagemSaida;

      getItemSet(resultado, &postagemSaida);
      fseek(arquivoTweets, postagemSaida.rrn, SEEK_SET);
      fgets(linhaSaida, postagemSaida.tamanhoLinha, arquivoTweets);
      printf("%s\n", linhaSaida);
    }

    printf("Quantidade de postagem(ns) encontrada(s): %d\n", tamanhoSet(resultado));

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

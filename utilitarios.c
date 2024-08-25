#include <string.h>
#include <ctype.h>
#include "utilitarios.h"

int palavraComposta(char* valor, int i, int tamanho) {
  return (i > 0 && i < tamanho - 1 && isalpha(valor[i - 1]) && isalpha(valor[i + 1]));
}

void limparString(char* valor) {
  int tamanho = strlen(valor);
  int quantidadeCaracteresValidos = 0;

  char stringLimpa[tamanho + 1];

  for (int i = 0; i < tamanho; i++) {
    if (isalpha(valor[i])) {
      stringLimpa[quantidadeCaracteresValidos++] = tolower(valor[i]);
    } else if ((valor[i] == '-' || valor[i] == '\'') && palavraComposta(valor, i, tamanho)) {
      stringLimpa[quantidadeCaracteresValidos++] = valor[i];
    } else if (quantidadeCaracteresValidos > 0 && stringLimpa[quantidadeCaracteresValidos - 1] != ' ') {
      stringLimpa[quantidadeCaracteresValidos++] = ' ';
    }
  }

  if (quantidadeCaracteresValidos > 0 && stringLimpa[quantidadeCaracteresValidos - 1] == ' ') {
    quantidadeCaracteresValidos--;
  }

  stringLimpa[quantidadeCaracteresValidos] = '\0';

  strcpy(valor, stringLimpa);
}
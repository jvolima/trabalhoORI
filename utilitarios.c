#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilitarios.h"

#define MAX_COMPONENTES 100
#define MAX_PILHA 100

int palavraComposta(char* valor, int i, int tamanho) {
  return (i > 0 && i < tamanho - 1 && isalpha(valor[i - 1]) && isalpha(valor[i + 1]));
}

void limparString(char* valor) {
  int tamanho = strlen(valor);
  int quantidadeCaracteresValidos = 0;

  char stringLimpa[tamanho + 1];

  for (int i = 0; i < tamanho; i++) {
    if (isalpha(valor[i]) || isdigit(valor[i])) {
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

char** separarBuscaEmComponentes(char* busca, int* numComponentes) {
  char** componentes = malloc(MAX_COMPONENTES * sizeof(char*));
  if (componentes == NULL) {
    return NULL;
  }

  char* componente;
  int i = 0;

  while (*busca != '\0') {
    while (isspace(*busca)) {
      busca++;
    }

    if (*busca == '\0') {
      break;
    }

    if (*busca == '(' || *busca == ')' || !isalnum(*busca)) {
      componentes[i] = malloc(2 * sizeof(char));  
      componentes[i][0] = *busca;
      componentes[i][1] = '\0';
      i++;
      busca++;
    } else {
      componente = busca;
      while (*busca != '\0' && isalnum(*busca)) {
        busca++;
      }
      int tamanho = busca - componente;
      componentes[i] = malloc((tamanho + 1) * sizeof(char));
      strncpy(componentes[i], componente, tamanho);
      componentes[i][tamanho] = '\0';
      i++;
    }
  }

  *numComponentes = i;
  return componentes;
}

int precedencia(char* operacao) {
  if (strcmp(operacao, "NOT") == 0) {
    return 3;
  }

  if (strcmp(operacao, "AND") == 0) {
    return 2;
  }

  if (strcmp(operacao, "OR") == 0) {
    return 1;
  }

  return 0;
}

char** converterComponentesParaPostfix(char** componentes, int tamanho, int *tamanhoPostfix) {
  char** resultado = (char**) malloc (MAX_PILHA * sizeof(char*));
  if (resultado == NULL) {
    return NULL;
  }

  char* pilha[MAX_PILHA];
  int topo = -1;
  int indice = 0;

  for (int i = 0; i < tamanho; i++) {
    char* componente = componentes[i];

    if (strcmp(componente, "NOT") != 0 && strcmp(componente, "AND") != 0 && strcmp(componente, "OR") != 0 && strcmp(componente, "(") != 0 && strcmp(componente, ")") != 0) {
      for (int i = 0; componente[i] != '\0'; i++) {
        componente[i] = tolower(componente[i]);
      }
      resultado[indice] = componente;
      indice++;
    } else if (strcmp(componente, "(") == 0) {
      topo++;
      pilha[topo] = componente;
    } else if (strcmp(componente, ")") == 0) {
      while (topo != -1 && strcmp(pilha[topo], "(") != 0) {
        resultado[indice] = pilha[topo];
        indice++;
        topo--;
      }
      topo--; 
    } else {
      while (topo != -1 && precedencia(pilha[topo]) >= precedencia(componente)) {
        resultado[indice] = pilha[topo];
        indice++;
        topo--;
      }
      topo++;
      pilha[topo] = componente;
    }
  }

  while (topo != -1) {
    resultado[indice] = pilha[topo];
    indice++;
    topo--;
  }

  *tamanhoPostfix = indice;

  return resultado;
}

Set* avaliarPostfix(Hash* hash, char** postfix, int quantidade) {
  Set* pilha[MAX_PILHA];
  int topo = -1;
  int operadorNot = 0;
  int elementoNegado = -1;

  for (int i = 0; i < quantidade; i++) {
    if (strcmp(postfix[i], "NOT") == 0) {
      if (elementoNegado != -1) {
        return NULL;
      }
      operadorNot = 1;
      elementoNegado = topo;
    } else if (strcmp(postfix[i], "AND") == 0) {
      if (topo < 1) {
        return NULL;
      }
    
      Set* set1 = pilha[topo];
      topo--; 
      Set* set2 = pilha[topo];
      topo--;

      if (operadorNot) {
        if (elementoNegado == 0) {
          pilha[++topo] = interseccaoSetComNot(set1, set2);
        } else {
          pilha[++topo] = interseccaoSetComNot(set2, set1);
        }
      } else {
        pilha[++topo] = interseccaoSet(set1, set2);
      }
      operadorNot = 0;
      elementoNegado = -1;
    } else if (strcmp(postfix[i], "OR") == 0) {
        if (topo < 1) { 
          return NULL;
        }
 
        Set* set1 = pilha[topo];
        topo--;
        Set* set2 = pilha[topo];
        topo--;

        if (operadorNot) {
          return NULL;
        } else { 
          pilha[++topo] = uniaoSet(set1, set2);
        }
        operadorNot = 0;
    } else {
      Palavra palavra;
      if (buscaPalavra(hash, postfix[i], &palavra)) {
        Set* conjunto = criaSet();
        Postagem* postagens = retornaLista(palavra.listaPostagens);
        for (int i = 0; i < quantidadeLista(palavra.listaPostagens); i++) {
          insereSet(conjunto, postagens[i]);
        }
        pilha[++topo] = conjunto;
      }
    } 
  }

  if (topo != 0) { 
    return NULL;
  }

  return pilha[topo]; 
}

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "arvoreAvl.h"

struct set {
  ArvAVL* arv;
  int quantidade;
  struct iterator *iter;
};

Set* criaSet() {
  Set* s = (Set*) malloc (sizeof(Set));
  if (s != NULL) {
    s->arv = criaArvAVL();
    s->quantidade = 0;
    s->iter = NULL;
  }

  return s;
}

void liberaSet(Set* s) {
  if (s != NULL){
    liberaArvAVL(s->arv);

    struct iterator* no;
    while(s->iter != NULL) {
      no = s->iter;
      s->iter = s->iter->prox;
      free(no);
    }

    free(s);
  }
}

int insereSet(Set* s, Postagem postagem) {
  if (s == NULL) {
    return 0;
  }

  if (insereArvAVL(s->arv, postagem)) {
    s->quantidade++;
    return 1;
  }

  return 0;
}

int tamanhoSet(Set* s) {
  if (s == NULL) {
    return 0;
  }

  return s->quantidade;
}

int consultaSet(Set* s, Postagem postagem) {
  if(s == NULL) {
    return 0;
  }

  return consultaArvAVL(s->arv, postagem);
}

void beginSet(Set *s){
  if (s == NULL) {
    return;
  }

  s->iter = NULL;
  iteratorArvAVL(s->arv, &(s->iter));
}

int endSet(Set *s){
  if (s == NULL) {
    return 1;
  }

  if (s->iter == NULL) {
    return 1;
  }

  return 0;
}

void nextSet(Set *s) {
  if (s == NULL) {
    return;
  }

  if (s->iter != NULL) {
    struct iterator *no = s->iter;
    s->iter = s->iter->prox;
    free(no);
  }
}

void getItemSet(Set *s, Postagem *postagem) {
  if (s == NULL) {
    return;
  }

  if (s->iter != NULL) {
    *postagem = s->iter->valor;
  }
}

Set* uniaoSet(Set* A, Set* B) {
  if (A == NULL || B == NULL) {
    return NULL;
  }

  Postagem postagem;
  Set *C = criaSet();

  for (beginSet(A); !endSet(A); nextSet(A)) {
    getItemSet(A, &postagem);
    insereSet(C, postagem);
  }

  for (beginSet(B); !endSet(B); nextSet(B)) {
    getItemSet(B, &postagem);
    insereSet(C, postagem);
  }

  return C;
}

Set* interseccaoSet(Set* A, Set* B) {
  if (A == NULL || B == NULL) {
    return NULL;
  }

  Postagem postagem;
  Set *C = criaSet();

  if (tamanhoSet(A) < tamanhoSet(B)) {
    for (beginSet(A); !endSet(A); nextSet(A)) {
      getItemSet(A, &postagem);
      if (consultaSet(B, postagem)) {
        insereSet(C, postagem);
      }   
    }
  } else {
    for (beginSet(B); !endSet(B); nextSet(B)) {
      getItemSet(B, &postagem);
      if (consultaSet(A,postagem)) {
        insereSet(C,postagem);
      }
    }
  }

  return C;
}

Set* interseccaoSetComNot(Set* A, Set* B) {
  if (A == NULL || B == NULL) {
    return NULL;
  }

  Postagem postagem;
  Set *C = criaSet(); 

  for (beginSet(A); !endSet(A); nextSet(A)) {
    getItemSet(A, &postagem);

    if (!consultaSet(B, postagem)) {
      insereSet(C, postagem);
    }
  }

  return C;
}
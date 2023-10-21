#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
  int id;
  struct Nodo *linkEsquerdo;
  struct Nodo *linkDireito;
  int altura;
} Nodo;

// aloca na memoria o nodo
Nodo *alocarNodo(int id) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));

  nodo->id = id;
  nodo->linkEsquerdo = NULL;
  nodo->linkDireito = NULL;
  nodo->altura = 1;

  return nodo;
}

// captura a altura de um nodo a
int getAltura(Nodo *a) {
  if (a == NULL)
    return 0;
  return a->altura;
}

// captura o fator de balanceamento de um nodo a
int getFB(Nodo *a) {
  if (a == NULL)
    return 0;
  return getAltura(a->linkEsquerdo) - getAltura(a->linkDireito);
}

// calcula altura de um nodo a
void calcularAltura(Nodo *a) {
  if (a == NULL)
    return;

  int alturaSubEsq = getAltura(a->linkEsquerdo);
  int alturaSubDir = getAltura(a->linkDireito);

  if (alturaSubEsq > alturaSubDir)
    a->altura = 1 + alturaSubEsq;
  else
    a->altura = 1 + alturaSubDir;
}

// rotacao direita simples
Nodo *rotacaoDireita(Nodo *a) {
  Nodo *b = a->linkEsquerdo;
  Nodo *T2 = b->linkDireito;

  b->linkDireito = a;
  a->linkEsquerdo = T2;

  calcularAltura(a);
  calcularAltura(b);

  // nova raiz
  return b;
}

// rotacao esquerda simples
Nodo *rotacaoEsquerda(Nodo *a) {
  Nodo *b = a->linkDireito;
  Nodo *T2 = b->linkEsquerdo;

  b->linkEsquerdo = a;
  a->linkDireito = T2;

  calcularAltura(a);
  calcularAltura(b);

  // nova raiz
  return b;
}

// insercao
Nodo *inserirAVL(Nodo *raiz, int id) {
  if (raiz == NULL)
    return alocarNodo(id);

  if (id < raiz->id)
    raiz->linkEsquerdo = inserirAVL(raiz->linkEsquerdo, id);
  else if (id > raiz->id)
    raiz->linkDireito = inserirAVL(raiz->linkDireito, id);
  else
    return raiz;

  calcularAltura(raiz);

  int fb = getFB(raiz);

  // direita simples
  if (fb > 1 && id < raiz->linkEsquerdo->id)
    return rotacaoDireita(raiz);

  // esquerda simples
  if (fb < -1 && id > raiz->linkDireito->id)
    return rotacaoEsquerda(raiz);

  // direita dupla
  if (fb > 1 && id > raiz->linkEsquerdo->id) {
    raiz->linkEsquerdo = rotacaoEsquerda(raiz->linkEsquerdo);
    return rotacaoDireita(raiz);
  }

  // esquerda dupla
  if (fb < -1 && id < raiz->linkDireito->id) {
    raiz->linkDireito = rotacaoDireita(raiz->linkDireito);
    return rotacaoEsquerda(raiz);
  }

  return raiz;
}

// imprime em 2D (transversal in-order)
void imprime2D(Nodo *raiz, int tab) {
  if (raiz == NULL)
    return;

  int cont = 5;
  tab += cont;

  imprime2D(raiz->linkDireito, tab);

  printf("\n");
  for (int i = cont; i < tab; i++)
    printf(" ");
  printf("%d\n", raiz->id);

  imprime2D(raiz->linkEsquerdo, tab);
}

// Função principal
int main(void) {
  Nodo *raiz = NULL;

  raiz = inserirAVL(raiz, 6);
  raiz = inserirAVL(raiz, 5);
  raiz = inserirAVL(raiz, 4);
  raiz = inserirAVL(raiz, 2);
  raiz = inserirAVL(raiz, 9);
  raiz = inserirAVL(raiz, 1);

  imprime2D(raiz, 0);

  return 0;
}

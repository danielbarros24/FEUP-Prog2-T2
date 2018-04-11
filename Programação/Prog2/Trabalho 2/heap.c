/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heapvalida(heap *h) {
  return h == NULL || h->elementos == NULL ? 0 : 1;
}

int strvalida(const char *str) {
  return str == NULL || str[0] == '\0' ? 0 : 1;
}

heap* heap_nova(int capacidade)
{
  if(capacidade <= 0) {
    return NULL;
  }

  heap *h = malloc(sizeof(heap));
  if(h == NULL) {
    return NULL;
  }

  h->capacidade = capacidade + 1;
  h->tamanho = 0;
  
  h->elementos = malloc(sizeof(elemento) * (capacidade + 1));
  if(h->elementos == NULL) {
    return NULL;
  }

  return h;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
  if(!heapvalida(h) || !strvalida(texto)) {
    return 0;
  }

  if(h->tamanho == h->capacidade) {
    return 0;
  }

  elemento *el = malloc(sizeof(elemento));
  el->prioridade = prioridade;
  el->valor = strdup(texto);

  if(el->valor == NULL) {
    return 0;
  }

  h->tamanho++;

  int i;
  for(i = h->tamanho; i > 1 && h->elementos[i / 2]->prioridade > prioridade; i /= 2) {
    h->elementos[i] = h->elementos[i / 2];
  }

  h->elementos[i] = el;
  return 1;
}

void heap_apaga(heap *h)
{
  if(h == NULL) {
    return;
  }

  if(h->elementos != NULL) {
    int i;
    for(i = 1; i <= h->tamanho; i++) {
      free(h->elementos[i]->valor);
    }

    free(h->elementos);
  }

  free(h);
}

int heap_remove0(heap *h, int index) {
  if(index * 2 > h->tamanho) {
    return index;
  }
  
  elemento *filho1 = h->elementos[index * 2];
  elemento *filho2;

  if(index * 2 + 1 > h->tamanho ||
   filho1->prioridade < (filho2 = h->elementos[index * 2 + 1])->prioridade) {
    h->elementos[index] = filho1;
    return heap_remove0(h, index * 2);
  }

  h->elementos[index] = filho2;
  return heap_remove0(h, index * 2 + 1);
}

char* heap_remove(heap * h)
{
  if(!heapvalida(h) || h->tamanho == 0) {
    return NULL;
  }

  elemento *raiz = h->elementos[1];
  elemento *folha = h->elementos[h->tamanho];

  char *valor = strdup(raiz->valor);
  free(raiz->valor);
  free(raiz);

  int index = heap_remove0(h, 1);
  h->elementos[index] = folha;
  h->elementos[h->tamanho] = 0;
  h->tamanho--;

  int prioridade = folha->prioridade;

  int i;
  for(i = index; i > 1 && h->elementos[i / 2]->prioridade > prioridade; i /= 2) {
    elemento *cache = h->elementos[i];
    h->elementos[i] = h->elementos[i / 2];
    h->elementos[i / 2] = cache;
  }

  return valor;
}

heap* heap_constroi(elemento* v, int n_elementos)
{
  if(v == NULL || n_elementos <= 0) {
    return NULL;
  }

  heap *h = heap_nova(n_elementos);
  if(h == NULL) {
    return NULL;
  }

  int i;
  for(i = 0; i < n_elementos; i++) {
    elemento el = v[i];

    if(!strvalida(el.valor) || heap_insere(h, el.valor, el.prioridade) == 0) {
      heap_apaga(h);
      return NULL;
    }
  }

  return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
  return -1;
}

void mostraHeap(heap *h, int indice)
{
  int i, nivel = 0;
  
  if (indice < h->tamanho)
  {
    i = indice;
    while(i > 1)
    {
      i = i/2;
      nivel++;
    }
    
    mostraHeap(h, indice*2);
    
    for(i = 0; i < 3 * nivel; i++)
      printf("     ");
    
    printf("%s (%d)\n",h->elementos[indice]->valor, h->elementos[indice]->prioridade);
    
    mostraHeap(h, indice*2+1);
  }
}
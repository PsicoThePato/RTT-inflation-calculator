#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int id;           // identificador do nó
  double value;     // valor associado ao nó
  int from;
}Item;

#define id(A)          (A.id)                           // retorna identificador do nó
#define value(A)        (A.value)                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item t = A; A = B; B = t; }   // troca dois nós


int compare_item(const void* A, const void* B);


#endif

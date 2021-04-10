#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"


typedef struct pq
{
    Item* pq;
    int* map;
    int N;
}PQ;

PQ* PQ_init(int maxN); // cria uma min PQ* com capacidade maxN
void PQ_insert(Item v, PQ* pqStruct);   // Insere Item na PQ*. A maior prioridade é a do Item com menor campo 'value'
int PQ_hasX(int x, PQ* pqStruct);
Item PQ_delmin(PQ* pqStruct);       // Remove Item com menor campo 'value' da PQ*
void PQ_decrease_key(int id, double value, PQ* pqStruct); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(PQ* pqStruct);          // Retorna Item com menor campo 'value' da PQ*
bool PQ_empty(PQ* pqStruct);        // Retorna True se a PQ* não tem elementos
int  PQ_size(PQ* pqStruct);         // Número de elementos na PQ*
void PQ_finish(PQ* pqStruct);       // Libera memória

#endif

#include <stdio.h>
#include <stdlib.h>
#include "headers/PQ.h"


static void swap(int i, int j, PQ* pqStruct) {
    exch(pqStruct->pq[i], pqStruct->pq[j]);
    pqStruct->map[id(pqStruct->pq[i])] = i;
    pqStruct->map[id(pqStruct->pq[j])] = j;
}

void fix_up(Item *a, int k, PQ* pqStruct) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2, pqStruct);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k, PQ* pqStruct){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j, pqStruct);
    k = j;
  }
}

PQ* PQ_init(int maxN) {
    PQ* pqStruct = malloc(sizeof(PQ));
    pqStruct->pq = (Item *) malloc((maxN+1) * sizeof (Item));
    pqStruct->map = (int *) malloc((maxN+1) * sizeof (int));
    pqStruct->N = 0;
    return pqStruct;
}

void PQ_insert(Item v, PQ* pqStruct) {
    pqStruct->N++;
    pqStruct->pq[pqStruct->N] = v;
    pqStruct->map[id(v)] = pqStruct->N;
    fix_up(pqStruct->pq, pqStruct->N, pqStruct);
}

Item PQ_delmin(PQ* pqStruct) {
    Item min = pqStruct->pq[1];
    swap(1, pqStruct->N, pqStruct);
    pqStruct->N--;
    fix_down(pqStruct->pq, pqStruct->N, 1, pqStruct);

    return min;
}

Item PQ_min(PQ* pqStruct) {
    return pqStruct->pq[1];
}

void PQ_decrease_key(int id, double value, PQ* pqStruct) {
    int i = pqStruct->map[id];
    value(pqStruct->pq[i]) = value;
    fix_up(pqStruct->pq, i, pqStruct);
}

bool PQ_empty(PQ* pqStruct) {
    return pqStruct->N == 0;
}

int  PQ_size(PQ* pqStruct) {
    return pqStruct->N;
}

void PQ_finish(PQ* pqStruct) {
    free(pqStruct->pq);
    free(pqStruct->map);
    free(pqStruct);
}



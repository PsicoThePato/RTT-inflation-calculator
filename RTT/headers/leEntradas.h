#ifndef _LEENTRADAS_H_
#define _LEENTRADAS_H_

#include "graphOperations.h"
#include "../headers/linkedList.h"
#include "item.h"


Grafo* inicializaGrafo();


void getLineData(FILE* entry, int* dataArray, int nTokens);


int** allocAdjMatrix(int nV);


void getnNodes(FILE* entry, int *servitorsArray, int nS);


void allocAdjList(FILE* entry, int E, List* nodeList);


void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim);


Item* rtt_calc(Grafo* graph, int* src, int* to, int nSrc, int nTo);

#endif
#ifndef _LEENTRADAS_H_
#define _LEENTRADAS_H_

#include "graphOperations.h"
#include "../headers/linkedList.h"
#include "item.h"


Grafo* inicializaGrafo();


void getLineData(FILE* entry, int* dataArray, int nTokens);


void getnNodes(FILE* entry, int *servitorsArray, int nS);


void allocAdjList(FILE* entry, int E, List* nodeList);


#endif
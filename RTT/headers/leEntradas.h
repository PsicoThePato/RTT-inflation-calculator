#ifndef _LEENTRADAS_H_
#define _LEENTRADAS_H_

#include "graphOperations.h"

Grafo* inicializaGrafo();


void allocVE(FILE* entry, int* Firstline);


int** allocAdjMatrix(int nV);

#endif
#ifndef _GRAPHOPERATIONS_H_
#define _GRAPHOPERATIONS_H_

#include "linkedList.h"

typedef struct grafo
{
    int nS;
    int* servidores;
    int nM;
    int* monitores;
    int nC;
    int* clients;
    int nV;
    List* adjList;
}Grafo;


void destroiGrafo(Grafo* grafo);

int** allocAdjMatrix(int nV);

void assertCarregueiCerto(Grafo* grafo);


#endif
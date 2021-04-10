#ifndef _GRAPHOPERATIONS_h_
#define _GRAPHOPERATIONS_h_

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

void assertCarregueiCerto(Grafo* grafo);
#endif
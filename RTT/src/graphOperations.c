#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/graphOperations.h"
#include "../headers/linkedList.h"
#include "../headers/leEntradas.h"

void destroiGrafo(Grafo* grafo)
{
    for(int i=0; i<grafo->nV; i++)
    {
        destroyList(&grafo->adjList[i]);
    }
    free(grafo->clients);
    free(grafo->monitores);
    free(grafo->servidores);
    free(grafo->adjList);
    free(grafo);
}

void assertCarregueiCerto(Grafo* grafo)
{
    assert(grafo->nV == 5);
    assert(grafo->nS == 1);
    assert(grafo->nC == 1);
    assert(grafo->nM == 2); 
    
    int clients[] = {4};
    for(int i=0; i<grafo->nC; i++)
    {
        assert(grafo->clients[i] == clients[i]);
    }

    int monitors[] = {1,2};
    for(int i=0; i<grafo->nM; i++)
    {
        assert(grafo->monitores[i] == monitors[i]);
    }

    int servitors[] = {0};
    for(int i=0; i<grafo->nS; i++)
    {
        assert(grafo->servidores[i] == servitors[i]);
    }

    int** adjMatrix = allocAdjMatrix(grafo->nV);
    adjMatrix[0][1] = 10;
    adjMatrix[0][3] = 5;
    adjMatrix[1][3] = 2;
    adjMatrix[1][2] = 1;
    adjMatrix[2][4] = 4;
    adjMatrix[3][1] = 3;
    adjMatrix[3][2] = 3;
    adjMatrix[4][2] = 6;
    adjMatrix[4][0] = 7;
    for(int i=0; i<grafo->nV; i++)
    {
        Node* node = grafo->adjList[i].head;
        while(node)
        {
            assert(node->weight == (double)adjMatrix[i][node->nodeLabel]);
            node = node->next;
        }
    }

    for(int j=0; j<grafo->nV; j++)
    {
        free(adjMatrix[j]);
    }
    free(adjMatrix);
}
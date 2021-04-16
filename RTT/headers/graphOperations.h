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


/*
 * destroiGrafo
 * IN:	 grafo - Estrutura grafo com todos os atributos
 *              corretamente inicializados.
 * OUT:
 * POST: Libera toda a memória utilizada por <grafo>
 */
void destroiGrafo(Grafo* grafo);


/*
 * dijkstraSP
 * IN:	 nV - Número de vértices para alocação da matriz
 *              quadrada nVxnV
 * OUT:	 Matriz nVxnV inicializada com 0.
 * POST: Alocação de memória para a matriz.
 */
int** allocAdjMatrix(int nV);


/*
 * assertCarregueiCerto
 * IN:	 grafo - Estrutura grafo com todos os atributos
 *              corretamente inicializados.

 * OUT:	 
 * POST: Interrompe a execução caso o grafo não esteja de acordo com um caso
 *      de teste.
 */
void assertCarregueiCerto(Grafo* grafo);


#endif
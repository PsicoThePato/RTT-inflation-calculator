#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "graphOperations.h"
#include "item.h"
#include "PQ.h"


/*
 * dijkstraSP
 * IN:	 grafo - Estrutura grafo com todos os atributos
 *              corretamente inicializados.
 * 		 source - Número que representa o nó à partir do qual
 *                as distâncias serão traçadas
 * OUT:	 Vetor de items com a distância do nó <source> para todos os
 *        outros vértices.
 * POST: Alocação de memória para o vetor Item*
 */
Item* dijkstraSP(Grafo* grafo, int source);


/*
 * relax
 * IN:	 edge - Nó da listra encadeada que representa as adjacências do grafo.
 * 		 pq - Priority queue
 *       from - Número que representa de qual vértice está se caminhado de
 *       distTo - Vetor de distâncias para os vértices i.
 *       edgeTo - Vetor Itens que permite consultar o menor caminho
 *                  para cada vértice.
 *       source - Vetor do qual se está partindo.
 * OUT:
 * POST: Potencial inserção ou atualização do vértice edge->nodeLabel na pq
 *          ,atualização do valor no vetor distTo e edgeTo.
 */
void relax(Node* edge, PQ* pq, int from, double* distTo, Item* edgeTo, int source);

#endif
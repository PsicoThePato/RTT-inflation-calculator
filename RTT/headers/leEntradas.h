#ifndef _LEENTRADAS_H_
#define _LEENTRADAS_H_

#include "graphOperations.h"
#include "../headers/linkedList.h"
#include "item.h"


/*
 * inicializaGrafo
 * IN:	 path_arquivo - Caminho para arquivo com
 *      informações de inicialização.
 * OUT: Grafo inicializado com valores indicados no arquivo.
 * POST: Aloca memória para Grafo e todos seus atributos.
 */
Grafo* inicializaGrafo(char* path_arquivo);


/*
 * getLineData
 * IN:	 entry - Ponteiro para arquivo.
 *       dataArray - Vetor com nTokens posições.
 *       nTokens - Número de dados a serem pegos da linha.
 * OUT:
 * POST: Insere <nTokens> números no vetor dataArray, lidos da linha
 *       apontada por entry.
 */
void getLineData(FILE* entry, int* dataArray, int nTokens);


/*
 * getnNodes
 * IN:	 entry - Ponteiro para arquivo
 *       servitorsArray - Vetor de inteiros com <nS> posições.
 *       nS - Número de elementos a serem lidos.
 * OUT:
 * POST: Insere <nS> números no servitorsArray, lidos como
 * os primeiros números das próximas <nS> linhas apontadas
 * por entry.
 */
void getnNodes(FILE* entry, int *servitorsArray, int nS);


/*
 * allocAdjList
 * IN:	 entry - Ponteiro para arquivo
 *       E - Sinceramente eu não uso isso pra nada, mas não
 *          não dá tempo de tirar
 *       nodeList - Array de listas encadeadas
 * OUT:
 * POST: Para cada lista encadeada i, insere os vértices adjacentes a
 *      i nela.
 */
void allocAdjList(FILE* entry, int E, List* nodeList);


#endif
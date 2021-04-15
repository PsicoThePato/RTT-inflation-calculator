#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/leEntradas.h"
#include "../headers/error.h"
#include "../headers/dijkstra.h"
#include "../headers/item.h"
#include "../headers/linkedList.h"


Grafo* inicializaGrafo(char* path_arquivo)
{
    int firstLine[2]; //trocar pra malloc na função getLineData depois(?)
    int secondLine[3];

    FILE* entry = fopen(path_arquivo, "r");
    checkNullPointer(entry, "Problema na abertura do arquivo\n");
    getLineData(entry, firstLine, 2);
    getLineData(entry, secondLine, 3);
    Grafo* graph = malloc(sizeof(Grafo));
    graph->nS = secondLine[0];
    graph->nC = secondLine[1];
    graph->nM = secondLine[2];
    graph->nV = firstLine[0];
    int nE = firstLine[1];
    
    int *servitors = malloc(graph->nS * sizeof(int));
    int *clients = malloc(graph->nC * sizeof(int));
    int *monitors = malloc(graph->nM * sizeof(int));

    getnNodes(entry, servitors, graph->nS);
    getnNodes(entry, clients, graph->nC);
    getnNodes(entry, monitors, graph->nM);
    graph->servidores = servitors;
    graph->clients = clients;
    graph->monitores = monitors;

    List* nodeList = malloc(sizeof(List) * graph->nV);
    for(int i=0; i<graph->nV; i++)
    {
        newList(&nodeList[i]);
    }
    allocAdjList(entry, nE, nodeList);
    fclose(entry);

    graph->servidores = servitors;
    graph->clients = clients;
    graph->monitores = monitors;
    graph->adjList = nodeList;
    return graph;

}


void getLineData(FILE* entry, int *dataArray, int nTokens)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t nRead;
    char* token;
    int auxIter = 0;
    const char delim = ' ';
    nRead = getline(&line, &len, entry);
    token = strtok(line, &delim);
    while(token != NULL)
    {
        dataArray[auxIter] = atoi(token);
        auxIter++;
        token = strtok(NULL, &delim);
    }
    free(line);
}


void getnNodes(FILE* entry, int *servitorsArray, int nS)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t nRead;
    for(int i=0; i<nS; i++)
    {
        nRead = getline(&line, &len, entry);
        servitorsArray[i] = atoi(line);  // each line will only have one character.
    }
    free(line);
}


void allocAdjList(FILE* entry, int E, List* nodeList)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t nRead;
    char* token;
    int auxIter = 0;
    const char delim = ' ';

    int nodeA;
    int nodeB;
    double weight;
    for(int i=0; i<E; i++)
    {
        fscanf(entry, "%d %d %lf", &nodeA, &nodeB, &weight);
        addTail(&nodeList[nodeA], weight, nodeB);
    }
}
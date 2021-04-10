#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/leEntradas.h"
#include "../headers/error.h"
#include "../headers/dijkstra.h"
#include "../headers/item.h"


Grafo* inicializaGrafo()
{
    int firstLine[2]; //trocar pra malloc na função getLineData depois(?)
    int secondLine[3];

    FILE* entry = fopen("in/teste.txt", "r");
    checkNullPointer(entry, "Problema na abertura do arquivo\n");
    getLineData(entry, firstLine, 2);
    getLineData(entry, secondLine, 3);
    Grafo* graph = malloc(sizeof(Grafo));
    graph->nS = secondLine[0];
    graph->nC = secondLine[1];
    graph->nM = secondLine[2];
    graph->nV = firstLine[0];
    int nE = firstLine[1];
    
    int servitors[graph->nS];
    int clients[graph->nC];
    int monitors[graph->nM];
    getnNodes(entry, servitors, graph->nS);
    getnNodes(entry, clients, graph->nC);
    getnNodes(entry, monitors, graph->nM);
    graph->servidores = servitors;
    graph->clients = clients;
    graph->monitores = monitors;

    List* nodeList = malloc(sizeof(List) * graph->nV);
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


int** allocAdjMatrix(int nV)
{
    int **adjacency_matrix = malloc(sizeof(int *) * nV);
    checkNullPointer(adjacency_matrix, "Problema na alocação de matriz de adjacências\n");
    for(int i = 0; i < nV; i++)
    {
        adjacency_matrix[i] = calloc(nV, sizeof(int));
        checkNullPointer(adjacency_matrix[i], "Problema na alocação de uma linha da matriz de adj\n");
    }

    return adjacency_matrix;
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


int main()
{
    Grafo* graph = inicializaGrafo();
    assertCarregueiCerto(graph);
    Item* edgeTo = dijkstraSP(graph, 0);
    for(int i = 0; i < graph->nV; i++)
    {
        printf("(%d, %d, %lf)\n", edgeTo[i].id, i, edgeTo[i].value);
    }
    free(edgeTo);
    destroiGrafo(graph);
}
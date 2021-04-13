#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/leEntradas.h"
#include "../headers/error.h"
#include "../headers/dijkstra.h"
#include "../headers/item.h"
#include "../headers/linkedList.h"


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


void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim)
{
    for(int i = 0; i < src_delim; i++)
    {
        Item* edgeTo = dijkstraSP(graph, src_nodes[i]);
        for(int j=0; j<to_delim; j++)
        {
            real_rtt_calc[i + j].id = to_nodes[j];
            real_rtt_calc[i + j].value += edgeTo[to_nodes[j]].value;
        }
        free(edgeTo);
    }
}


void sum_dist_array(Item* src_to, Item* to_src, Grafo* graph)
{
    for(int i=0; i<graph->nS; i+=graph->nC)
    {
        for(int j=0; j<graph->nC;j++)
        {
            src_to[i+j].value += to_src[i + j*graph->nS].value; 
        } 
    }
}


Item* rtt_calc(Grafo* graph)
{
    Item* real_rtt_calc = calloc(graph->nS * graph->nC, sizeof(Item));
    Item* aux_rtt_calc = calloc(graph->nS * graph->nC, sizeof(Item));
    update_rtt_array_values(graph, real_rtt_calc, graph->servidores, graph->clients, graph->nS, graph->nC);
    update_rtt_array_values(graph, aux_rtt_calc, graph->clients, graph->servidores, graph->nC, graph->nS);
    sum_dist_array(real_rtt_calc, aux_rtt_calc, graph);
    return real_rtt_calc;
}


Item* rtt_aprox_calc(Grafo* graph)
{
    Item* real_rtt_calc = calloc(graph->nS * graph->nC, sizeof(Item));
    Item* aux_rtt_calc = calloc(graph->nS * graph->nC, sizeof(Item));
    update_rtt_array_values(graph, real_rtt_calc, graph->servidores, graph->clients, graph->nS, graph->nC);
    update_rtt_array_values(graph, aux_rtt_calc, graph->clients, graph->servidores, graph->nC, graph->nS);
    sum_dist_array(real_rtt_calc, aux_rtt_calc, graph);
    return real_rtt_calc;
}



int main()
{
    Grafo* graph = inicializaGrafo();
    //Item* edgeTo = dijkstraSP(graph, 0);
    Item* real_rtt_calc = rtt_calc(graph);
    for(int i=0; i<graph->nC * graph ->nS;i++)
    {
        printf("A distancia para o node %d eh %lf\n", real_rtt_calc[i].id, real_rtt_calc[i].value);
    }
    free(real_rtt_calc);
    //free(edgeTo);
    destroiGrafo(graph);
}

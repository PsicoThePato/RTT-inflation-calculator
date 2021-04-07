#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/leEntradas.h"
#include "../headers/error.h"



Grafo* inicializaGrafo()
{
    int firstLine[2]; //trocar pra malloc na função getLineData depois(?)
    int secondLine[3];
    Grafo myGrafo;
    FILE* entry = fopen("in/teste.txt", "r");
    checkNullPointer(entry, "Problema na abertura do arquivo\n");
    getLineData(entry, firstLine, 2);
    getLineData(entry, secondLine, 3);
    
    int servitors[secondLine[0]];
    int clients[secondLine[1]];
    int monitors[secondLine[2]];
    getnNodes(entry, servitors, secondLine[0]);
    getnNodes(entry, clients, secondLine[1]);
    getnNodes(entry, monitors, secondLine[2]);

    //allocAdjMatrix(firstLine[0]);
    List* nodeList = malloc(sizeof(List) * firstLine[0]);
    allocAdjList(entry, firstLine[1], nodeList);
    for(int i=0; i<firstLine[0]; i++)
    {
        Node* node = nodeList[i].head;
        while(node)
        {
            printf("A aresta (%d %d) tem peso %lf\n", i, node->nodeLabel, node->weight);
            node = node->next;
        }
    }

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
    printf("%s\n", line);
    while(token != NULL)
    {
        printf("To lendo o token %s\n", token);
        dataArray[auxIter] = atoi(token);
        auxIter++;
        token = strtok(NULL, &delim);
    }
    
    for(int i = 0; i < nTokens; i++)
    {
        printf("Testando getLineData: i = %d \n", dataArray[i]);
    }
    
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

    for(int i = 0; i < nV; i++)
    {
        for(int j = 0; j < nV; j++)
        {
            printf("Testando allocAdj: [%d,%d] = %d\n", i, j, adjacency_matrix[i][j]);
        }
    }
    return adjacency_matrix;
}


void getnNodes(FILE* entry, int *servitorsArray, int nS)
{
    printf("TESTANDO getnNodes: ns=%d\n", nS);
    char* line = NULL;
    size_t len = 0;
    ssize_t nRead;
    for(int i=0; i<nS; i++)
    {
        nRead = getline(&line, &len, entry);
        servitorsArray[i] = atoi(line);  // each line will only have one character.
    }

    for(int i = 0; i < nS; i++)
    {
        printf("Testando getnNodes: i = %d \n", servitorsArray[i]);
    }
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
        // nRead = getline(&line, &len, entry);
        // token = strtok(line, &delim);
        // printf("%s\n", line);
        // int nodeA = atoi(&line[0]); //  #todo tirar esse hardcode do inferno
        // int nodeB = atoi(&line[2]); //  #todo tirar esse hardcode do inferno
        // double weight = atof(&line[4]); //  #todo tirar esse hardcode do inferno
        addTail(&nodeList[nodeA], weight, nodeB);
    
    }
}


int main()
{
    inicializaGrafo();
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/leEntradas.h"
#include "../headers/error.h"


Grafo* inicializaGrafo()
{
    int firstLine[2]; //trocar pra malloc na função allocVE depois(?)
    Grafo myGrafo;
    FILE* entry = fopen("in/teste.txt", "r");
    checkNullPointer(entry, "Problema na abertura do arquivo");
    allocVE(entry, firstLine);
    allocAdjMatrix(firstLine[0]);

}


void allocVE(FILE* entry, int *firstLine)
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
        firstLine[auxIter] = atoi(token);
        auxIter++;
        token = strtok(NULL, &delim);
    }
    for(int i = 0; i < 2; i++)
    {
        printf("Testando allocVe: i = %d \n", firstLine[i]);
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


int main()
{
    inicializaGrafo();
}
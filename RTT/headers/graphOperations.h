#ifndef _GRAPHOPERATIONS_h_
#define _GRAPHOPERATIONS_h_


typedef struct grafo
{
    int* servidores;
    int* monitores;
    int* clients;
    int** weightMatrix;
}Grafo;


#endif
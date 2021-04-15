#include <stdlib.h>
#include <stdio.h>

#include "../headers/item.h"
#include "../headers/graphOperations.h"
#include "../headers/rttOperations.h"
#include "../headers/leEntradas.h"


int main()
{
    Grafo* graph = inicializaGrafo();
    Item* real_rtt_calc = rtt_calc(graph, graph->servidores, graph->clients, graph->nS, graph->nC);
    for(int i=0; i<graph->nC * graph ->nS;i++)
    {
        printf("A distancia do node %d para o node %d eh %lf\n", real_rtt_calc[i].from, real_rtt_calc[i].id, real_rtt_calc[i].value);
    }
    free(real_rtt_calc);
    Item* real_rtt_calc1 = rtt_aprox_calc(graph);
    //free(edgeTo);
    destroiGrafo(graph);
}

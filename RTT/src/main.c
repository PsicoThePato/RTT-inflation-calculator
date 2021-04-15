#include <stdlib.h>
#include <stdio.h>

#include "../headers/item.h"
#include "../headers/graphOperations.h"
#include "../headers/rttOperations.h"
#include "../headers/leEntradas.h"
#include "../headers/geraSaida.h"

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Número bizarro de argumentos de entrada\n");
        exit(1);
    }
    char *arqEntrada = argv[1];
    char *arqSaida = argv[2];

    Grafo* graph = inicializaGrafo(arqEntrada);
    Item* real_rtt_calc = rtt_calc(graph, graph->servidores, graph->clients, graph->nS, graph->nC);
    Item* aprox_rtt = rtt_aprox_calc(graph);
    for(int i=0; i<graph->nC*graph->nS; i++)
    {
        printf("O valor aprox do nó %d para %d é %lf\n", aprox_rtt[i].from, aprox_rtt[i].id, aprox_rtt[i].value);
    }
    rtt_inflation(real_rtt_calc, aprox_rtt, graph->nC * graph->nS);

    escreveArquivo(real_rtt_calc, graph->nS * graph->nC, arqSaida);
    destroiGrafo(graph);
    free(real_rtt_calc);
    free(aprox_rtt);
}

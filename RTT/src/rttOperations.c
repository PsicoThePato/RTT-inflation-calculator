#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "../headers/item.h"
#include "../headers/graphOperations.h"
#include "../headers/dijkstra.h"


void sum_dist_array(Item* src_to, Item* to_src, int step, int outer_lim, int inner_lim)
{
    for(int i=0; i<outer_lim; i+=inner_lim)
    {
        for(int j=0; j<inner_lim;j++)
        {
            src_to[i+j].value += to_src[i + j*step].value; 
        } 
    }
}


void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim)
{
    for(int i = 0; i < src_delim; i++)
    {
        Item* edgeTo = dijkstraSP(graph, src_nodes[i]);
        for(int j=0; j<to_delim; j++)
        {
            real_rtt_calc[i + j].from = src_nodes[i];
            real_rtt_calc[i + j].id = to_nodes[j];
            real_rtt_calc[i + j].value += edgeTo[to_nodes[j]].value;
        }
        free(edgeTo);
    }
}


Item* rtt_calc(Grafo* graph, int* src, int* to, int nSrc, int nTo)
{
    Item* real_rtt_calc = calloc(nSrc * nTo, sizeof(Item));
    Item* aux_rtt_calc = calloc(nSrc * nTo, sizeof(Item));
    update_rtt_array_values(graph, real_rtt_calc, src, to, nSrc, nTo);
    update_rtt_array_values(graph, aux_rtt_calc, to, src, nTo, nSrc);
    sum_dist_array(real_rtt_calc, aux_rtt_calc, nSrc, nSrc, nTo);
    free(aux_rtt_calc);
    return real_rtt_calc;
}


Item* rtt_aprox_calc(Grafo* graph)
{
    Item* server_monitor;
    Item* monitor_client;
    Item* end_rtt = calloc(graph->nM * graph->nS * graph->nC, sizeof(Item));
 
    server_monitor = rtt_calc(graph, graph->servidores, graph->monitores, graph->nS, graph->nM);
    monitor_client = rtt_calc(graph, graph->monitores, graph->clients, graph->nM, graph->nC);
    
    int aux = 0;
    int bigArrayRef = 0;
    double server_to_client = FLT_MAX;
    for(int i=0; i<graph->nS; i+=graph->nM)
    {
        for(int j=0; j<graph->nC; j++)
        {
            for(int k=0; k<graph->nM; k++)
            {
                if(server_monitor[i + k].value + monitor_client[k*graph->nC + j].value < server_to_client)
                {   
                    server_to_client = server_monitor[i + k].value + monitor_client[k*graph->nC + j].value;
                    end_rtt[bigArrayRef].from = server_monitor[i + k].from;
                    end_rtt[bigArrayRef].id = monitor_client[k*graph->nC + j].id;
                    end_rtt[bigArrayRef].value = server_to_client;
                }
            }
        }
    }


    for(int i=0; i<graph->nC * graph->nS; i++)
    {
        printf("A distancia do node %d para o node %d eh %lf\n", end_rtt[i].from, end_rtt[i].id, end_rtt[i].value);
    }
    free(server_monitor);
    free(monitor_client);
    return end_rtt;
}


void rtt_inflation(Item* real_rtt, Item* aprox_rtt, int size)
{
    for(int i = 0; i < size; i++)
    {
        real_rtt[i].value = aprox_rtt[i].value/real_rtt[i].value;
    }
}
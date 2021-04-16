#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "../headers/item.h"
#include "../headers/graphOperations.h"
#include "../headers/dijkstra.h"


void sum_dist_array(Item* src_to, Item* to_src, int step, int outer_lim, int inner_lim)

{
    //[s0t0 s0t1 s0t2 s1t0]
    //[[t0s0 t0s1 t0s2] [t1s0 t1s1 t1s2]]
    int arrayIdx = 0;
    for(int i=0; i<outer_lim; i++)
    {
        for(int j=0; j<inner_lim;j++)
        {
            src_to[arrayIdx].value += to_src[i + j*step].value;
            arrayIdx++;
        }
    }
}


void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim)
{
    int arrayIdx = 0;
    for(int i = 0; i < src_delim; i++)
    {
        Item* edgeTo = dijkstraSP(graph, src_nodes[i]);
        for(int j=0; j<to_delim; j++)
        {
            real_rtt_calc[arrayIdx].from = src_nodes[i];
            real_rtt_calc[arrayIdx].id = to_nodes[j];
            real_rtt_calc[arrayIdx].value += edgeTo[to_nodes[j]].value;
            arrayIdx++;
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
    printf("APROX RTT\n");
    Item* server_monitor_pairs;
    Item* monitor_client_pairs;
    Item* end_rtt = calloc(graph->nS * graph->nC, sizeof(Item));

    server_monitor_pairs = rtt_calc(graph, graph->servidores, graph->monitores, graph->nS, graph->nM);
    monitor_client_pairs = rtt_calc(graph, graph->monitores, graph->clients, graph->nM, graph->nC);
    int big_idx = 0;
    for(int i = 0; i < graph->nS; i++)
    {
        for(int j = 0; j < graph->nC; j++)
        {
            double best_s2c_dist = DBL_MAX;
            for(int k = 0; k < graph->nM; k++)
            {
                int sm_idx = i * graph->nM + k;
                int mc_idx = k * graph->nC + j;
                int serverM = server_monitor_pairs[sm_idx].from;
                int monitorS = server_monitor_pairs[sm_idx].id;
                int monitorC = monitor_client_pairs[mc_idx].from;
                int clientM = monitor_client_pairs[mc_idx].id;
                double total_dist = server_monitor_pairs[sm_idx].value + monitor_client_pairs[mc_idx].value;
                if(total_dist < best_s2c_dist)
                {
                    best_s2c_dist = total_dist;
                    end_rtt[big_idx].from = server_monitor_pairs[sm_idx].from;
                    end_rtt[big_idx].id = monitor_client_pairs[mc_idx].id;
                    end_rtt[big_idx].value = best_s2c_dist;
                }
            }
            big_idx++;
        }
    }
    free(server_monitor_pairs);
    free(monitor_client_pairs);
    return end_rtt;
}


void rtt_inflation(Item* real_rtt, Item* aprox_rtt, int size)
{
    for(int i = 0; i < size; i++)
    {
        real_rtt[i].value = aprox_rtt[i].value/real_rtt[i].value;
    }
}
#ifndef _RTTOPERATIONS_H_
#define _RTTOPERATIONS_H_

#include "graphOperations.h"
#include "item.h"


void sum_dist_array(Item* src_to, Item* to_src, int step, int outer_lim, int inner_lim);

void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim);

Item* rtt_calc(Grafo* graph, int* src, int* to, int nSrc, int nTo);

Item* rtt_aprox_calc(Grafo* graph);
#endif
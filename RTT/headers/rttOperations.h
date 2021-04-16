#ifndef _RTTOPERATIONS_H_
#define _RTTOPERATIONS_H_

#include "graphOperations.h"
#include "item.h"


/*
 * sum_dist_array
 * IN:	 src_to - Vetor de itens
 * 		 to_src - Vetor de itens
 *       step - Passo
 *       outer_lim - Quantos elementos do primeiro
 *                   vetor devem ser pegos.
 *       inner_lim - Quantos grupos no segundo vetor devem ser pegos
 * OUT:
 * POST: Soma os <outer_lim> elementos de src_to com os valores de
 *       to_src segundo a regra src_to[i] + to_src[i +j*step].
 *       Guarda os resultados em src_to. 
 *       (ideal para somar pares em posições diferentes, como os vetores 
 *       [[s0c0 s0c1] [s1c0 s1c1] [s2c0 s2c1]]
        [[c0s0 c0s1 c0s2] [c1s0 c1s1 c1s2]])
 *       
 */
void sum_dist_array(Item* src_to, Item* to_src, int step, int outer_lim, int inner_lim);


/*
 * sum_dist_array
 * IN:	 graph - Grafo inicializado com valores corretos
 * 		 real_rtt_calc - Vetor com <src_delim> posições
 *       src_nodes - Vetor de inteiros representando vértices de destino.
 *       to_nodes - Vetor de inteiros representando vértices de chegada.
 *       src_delim - Número de itens de real_rtt_calc a serem usados como source
 *       to_delim - Número de itens de to_nodes cujas distâncias à eles serão salvas.
 * OUT:
 * POST: Para cada item em src_nodes salva a distância dele para todos itens em to_nodes
 *       no vetor real_rtt_calc.
 *       
 */
void update_rtt_array_values(Grafo* graph, Item* real_rtt_calc, int* src_nodes, int* to_nodes, int src_delim, int to_delim);


/*
 * sum_dist_array
 * IN:	 graph - Grafo inicializado com valores corretos
 * 		 src - Vetor com <nSrc> posições representando vértices.
 *       to - Vetor de <nTo> posições representando vértices de destino.
 *       nSrc - tamanho de src
 *       nTo - Tamanho de to
 * OUT:  Vetor de itens com o valor de rtt entre todos os elementos de src e to salvo
 *       no atributo valor.
 * POST: Aloca memória para o vetor de itens.
 *       
 */
Item* rtt_calc(Grafo* graph, int* src, int* to, int nSrc, int nTo);


/*
 * rtt_aprox_calc
 * IN:	 graph - Grafo inicializado com valores corretos

 * OUT:  Vetor de itens com o valor de rtt aproximado entre todos os elementos de src e to salvo
 *       no atributo valor. Usa o atributo graph->monitores como suporte para a aproximação.
 * POST: Aloca memória para o vetor de itens.
 *       
 */
Item* rtt_aprox_calc(Grafo* graph);


/*
 * rtt_inflation
 * IN:	 real_rtt - Vetor de itens com valores de rtt dos seus vértices.
 *       aprox_rtt - Vetor de itens com valores de rtt* dos seus vértices
 *       size - tamanho dos vetores.

 * OUT:
 * POST: Salva aprox_rtt[i].value/real_rtt[i].value em real_rtt para cada i até size.
 *       
 */
void rtt_inflation(Item* real_rtt, Item* aprox_rtt, int size);


#endif
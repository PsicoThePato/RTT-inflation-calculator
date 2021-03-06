#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../headers/dijkstra.h"
#include "../headers/item.h"
#include "../headers/PQ.h"


void relax(Node* edge, PQ* pq, int from, double* distTo, Item* edgeTo, int source)
{
    int to = edge->nodeLabel;
    if(distTo[to] > distTo[from] + edge->weight)
    {
        distTo[to] = distTo[from] + edge->weight;
        edgeTo[to].id = to;
        edgeTo[to].from = source;
        edgeTo[to].value = distTo[to];
        if(PQ_hasX(to, pq))
        {
            PQ_decrease_key(to, distTo[to], pq);
            return;
        } 
        Item node = {to, distTo[to], from};
        PQ_insert(node, pq);
    }
}


Item* dijkstraSP(Grafo* grafo, int source)
{
    Item *edgeTo = calloc(grafo->nV, sizeof(Item));  //calloc to please valgrind-sama

    double distTo[grafo->nV];
    for(int i=0; i<grafo->nV; i++)
    {
        distTo[i] = DBL_MAX;
    }

    distTo[source] = 0;
    Item no_inical = {source, 0.0, source};

    PQ* pq = PQ_init(grafo->nV);
    PQ_insert(no_inical, pq);

    while(!PQ_empty(pq))
    {
        Item min_item = PQ_delmin(pq);
        int min_node = min_item.id;
        Node* node = grafo->adjList[min_node].head;
        while(node)
        {
            relax(node, pq, min_node, distTo, edgeTo, source);
            node = node->next;
        }
    }
    PQ_finish(pq);
    return edgeTo;
}
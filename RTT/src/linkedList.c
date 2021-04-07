
#include <stdio.h>
#include <stdlib.h>

#include "../headers/linkedList.h"
#include "../headers/error.h"


void newList(List* list) 
{
	list->head = NULL;
	list->tail = NULL;	
}


int destroyList(List * list) 
{
	
	while(list->head) 
    {
		Node* current = list->head;
		list->head = current->next;
		free(current);
	}
	
	return 0;
}


int addTail(List * list, double weight, int nodeLabel) 
{
	
	Node* node = malloc(sizeof(Node));
	checkNullPointer(node, "Problema na alocação de novo nó da lista.\n");
	
    node->weight = weight;
	node->nodeLabel = nodeLabel;
	node->next = NULL;
	
	if(!list->head)
		list->head = node;
	
	
	if(list->tail)
		list->tail->next = node;
	
	list->tail = node;
	
	return 0;
	
}

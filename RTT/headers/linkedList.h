#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_



typedef struct listNode 
{
	double weight;
	int nodeLabel;
	struct listNode* next;	
}Node;


typedef struct 
{
	Node* head; 			// Pointer to list head
	Node* tail;			// Pointer to list tail
}List;


void newList(List* list);


int destroyList(List* list);


int addTail(List* list, double weight, int nodeB);


#endif
#include "../headers/item.h"

int compare_item(const void* A, const void* B)
{
  double valA = ((Item*)A)->value;
  double valB = ((Item*)B)->value;
  if(valA< valB)
    return -1;
  if(valA == valB)
    return 0;
  return 1;
}
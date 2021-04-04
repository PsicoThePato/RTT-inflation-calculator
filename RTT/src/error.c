#include <stdio.h>
#include <stdlib.h>


void checkNullPointer(void* pointer, char* errorMessage)
{
    if(!pointer)
    {
        perror(errorMessage);
        exit(1);

    }
}
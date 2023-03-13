#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void * mymalloc(int size)
{
    if (size < 1 || size > 4094) // check if the size can fit in memory
    {
        printf("Malloc Error: file = %s, line = %d, bytes = %d\n", __FILE__, __LINE__, size);
        return NULL;
    }
    miniblock * ptr = (miniblock *) &myblock[0];
    if (myblock[0] == '\0') // initialize myblock with an empty block
    {
        ptr->size = -4094;
        printf("Created main memory:\n\t[ %d ]\n", ptr->size);
    }
    int index = 0;
    while ( (index < 4096)) // loop until there is a place to allocate
    {   
        ptr = (miniblock *) &myblock[index];
        if (size <= abs(ptr->size) && ptr->size < 1)
        {
            break;
        }
        index += abs(ptr->size) + sizeof(miniblock);
    }
    if (index == 4096) // there is no place to allocate
    {
        printf("Malloc Error: file = %s, line = %d, bytes = %d\n", __FILE__, __LINE__, size);
        return NULL;
    }
    if (abs(ptr->size) <= size + sizeof(miniblock)) // if block cannot be split then use it
    {
        ptr->size = abs(ptr->size);
        printf("Created block:\n\t[ %d ]\n", ptr->size);
        return ptr;
    }
    else // if block can be split then split it and then use it
    {
        int index2 = index + sizeof(miniblock) + size;
        miniblock * ptr2 = (miniblock *) &myblock[index2];
        ptr2->size = abs(abs(ptr->size) - size - sizeof(miniblock)) * -1;
        ptr->size = size;
        printf("Created block:\n\t[ %d ]\n", ptr->size);
        return ptr;
    }
}

void myfree(void * temp)
{
    miniblock * prev = NULL;
    miniblock * ptr = (miniblock *) &myblock[0];
    int previndex = 0;
    int ptrindex = 0;
    while (ptrindex < 4096) // loop through array ...
    {
        if (ptr == temp) // ... until we find the block to be freed
        {
            break;
        }
        previndex = ptrindex;
        ptrindex += abs(ptr->size) + sizeof(miniblock);
        prev = ptr;
        ptr = (miniblock *) &myblock[ptrindex];
    }
    if (ptrindex == 4096) // the block to be freed is not there
    {
        printf("Free Error: file = %s, line = %d\n", __FILE__, __LINE__);
        return;
    }
    if (ptr->size < 0) // the block cannot be freed
    {
        printf("Free Error: file = %s, line = %d\n", __FILE__, __LINE__);
        return;
    }
    ptr->size = abs(ptr->size) * -1; // free the block
    printf("Freed block:\n\t[ %d ]\n", ptr->size);
    if (prev != NULL && prev->size < 0) // if the previous block is free then merge
    {
        prev->size = (abs(prev->size) + abs(ptr->size) + sizeof(miniblock)) * -1;
        ptr = prev;
        ptrindex = previndex;
    }
    int nextindex = ptrindex + abs(ptr->size) + sizeof(miniblock);
    if (nextindex != 4096) // if there is a next block
    {
        miniblock * next = (miniblock *) &myblock[nextindex];
        if (next->size < 0) // if the next block is free then merge
        {
            ptr->size = (abs(ptr->size) + abs(next->size) + sizeof(miniblock)) * -1;
        }
    }
}

void print()
{
    if (myblock[0] == '\0') // myblock not initialized
    {
        printf("Print Error\n");
        return;
    }
    printf("Total Memory:\n\t");
    miniblock * ptr = (miniblock *) &myblock[0];
    int index = 0;
    while (index < 4096) // loop through array and print each block
    {
        ptr = (miniblock *) &myblock[index];
        printf("[ %d ] -> ", ptr->size);
        index += abs(ptr->size) + sizeof(miniblock);
    }
    printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ulimit.h>
#include <stddef.h>
#include <pthread.h>

typedef struct _threadNode {
    int s; int e; int target; int*arr; 
} threadNode;

void* threadMe(void* args) {
    threadNode * ptr = (threadNode*) args;
    // ptr has start, end, target, array
    int found = 0;
    int i;
    for (i = ptr->s; i<ptr->e;i++) {
        if (ptr->arr[i] == ptr->target) { // forund target in thread
            ptr->target = i;
            pthread_exit((void*) i);
        }
    }
    int *notfound = (int*) -1;
    pthread_exit((void*)notfound);

    
}
int size; 
int lookfornum(int* arr, int arrsize, int target,int block) {

    if (block > 250 || block <= 0) {return -2;}

    //Round Up the Number of Threads...........................
    double round = (double)arrsize/block;
    double check = (double)round- (int)round;
    int threadsize = (int)round;
    if (check != 0) {threadsize++;} // Pround up number of threads
    //printf("\tThread Count: %d\n", threadsize);
    //....................................
    size = threadsize; //GLOBAL

    pthread_t thread[threadsize];

    int i;
    for (i = 0; i < threadsize; i++) {
        threadNode *searchMe = (threadNode*)malloc(sizeof(threadNode));
        
        if (i == 0) {searchMe->s = 0;}
        else {searchMe->s = threadsize*block;}
        
        if (threadsize == 0) {searchMe->e = block;}
        else {searchMe->e = threadsize*block +block;}

        searchMe->arr = arr;
        searchMe->target=target;

        pthread_create(&thread[i],NULL, threadMe, (void*)searchMe);
    }
    void* stat;
    int ret;
    for (i = 0; i < threadsize; i++) {
        pthread_join(thread[i], (void*)&ret);
        if (ret > 0 &&ret <arrsize) { return ret;}
    }
  
    return -1;
}

int proc_thread() {return 1;}

int pt_size() {return size;}
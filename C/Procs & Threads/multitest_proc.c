#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <ulimit.h>
#include <stddef.h>

// SET ULIMIT

int size; // GlOBAL

int lookfornum(int* arr, int arrsize, int target, int block) {
    // we to run process for every 250 integers in array
    if (block > 250 || block <= 0) { return -2;}

    int i,j,proc;
   
    //Round Up the Number of Processes...........................
    double round = (double)arrsize/block;
    double check = (double)round- (int)round;
    int procsize = (int)round;
    if (check != 0) {procsize++;} // Procsize has number of processes rounded up
    //....................................
    size = procsize;    
    if (procsize > 2000) {fprintf(stderr,"ERROR, ULIMIT SURPASSED\n"); exit(-4);} // passed limit

    pid_t pid[procsize]; // Define pid array size to number of processes

    proc = 0;
    for (i = 0; i < procsize; i++) {
        pid[proc] = fork(); // Forks process ...
        int cond;
        if (i== 0) {cond = block;} 
        else {cond = i*block+block;}
      
        if (pid[proc] < 0) {
            printf("Fork Failed\n"); return -1;
        } else if (pid[proc] == 0) { // Child Process       
            for (j = i*block; j < cond; j++) { // loop to search for value in array of size 250
                if (arr[j] == target) { // Found Target
                    //printf("Found Target: %d\n\tIn PID: %d\n\tIndex: %d\n", target, getpid(),j);
                    //printf("Found in Process: %d\n",proc);
                    exit(j%block); // j has index of target, rather mod by 250 then 256
                }
            }
        exit(-1); // 255, 8 bit conversion.
        } else { // Parent
         
        }
        proc++; // This helps determine which process we're in
    }
// Parent
    int status = 0;
    int ret = -1;
    for (i = 0; i<proc; i++) {
        waitpid(pid[i],&status,0);
        int stat = WEXITSTATUS(status);
       
        if (stat != 255) { 
            int value = block*(i)+stat; 
            ret = value;
        }  // This is because it returns 1 byte number so it must be converted. The exit status is modding it by 256
    }
    if (ret > arrsize-1) {ret = -1;} // index doesnt exist
    return ret;
}

int proc_thread() {return 0;}
int pt_size() {return size;}

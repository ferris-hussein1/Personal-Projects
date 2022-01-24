#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

void testAll();
void testA();
void testB();
void testC();
void testD();
void testE();
void testF();
void testG();

int main(int argc, char ** argv)
{
    testG();
    return 0;
}

void testAll()
{
    int i;
    double A_time, B_time, C_time, D_time, E_time, F_time, G_time;
    

    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testA(); }
    gettimeofday(&tv2, NULL);
    A_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
   // timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testB(); }
    gettimeofday(&tv2, NULL);
    B_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testC(); }
    gettimeofday(&tv2, NULL);
    C_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testD(); }
    gettimeofday(&tv2, NULL);
    D_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testE(); }
    gettimeofday(&tv2, NULL);
    E_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
    gettimeofday(&tv1, NULL);
    for (i=0; i<100;i++) {testF(); }
    gettimeofday(&tv2, NULL);
    F_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));

   
    gettimeofday(&tv1, NULL);
    testG();
    gettimeofday(&tv2, NULL);
    G_time = ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));

    printf("\n");
    printf("TestA took %f seconds for 100 iterations, %f seconds per test\n", A_time,A_time/100);
    printf("TestB took %f seconds for 100 iterations, %f seconds per test\n", B_time,B_time/100);
    printf("TestC took %f seconds for 100 iterations, %f seconds per test\n", C_time,C_time/100);
    printf("TestD took %f seconds for 100 iterations, %f seconds per test\n", D_time,D_time/100);
    printf("TestE took %f seconds for 100 iterations, %f seconds per test\n", E_time,E_time/100);
    printf("TestF took %f seconds for 100 iterations, %f seconds per test\n", F_time,F_time/100);
    printf("Extra TestCase G, took %f seconds to run\n\n", G_time);

}

void testA()
{
    int i = 0;
    for (; i<150; i++)
    {
        int * n = malloc(1);
        free(n);
    }
}

void testB()
{
    int * arr[50];
    int i, j;
    for (i=0; i<3; i++)
    {
        for (j=0; j<50; j++)
        {
            arr[j] = malloc(1);
        }
        for (j=0; j<50; j++)
        {
            free(arr[j]);
        }
    }
}

void testC()
{
    int * arr[50];
    int n = 0;
    while (n != 50)
    {
        if (n == 0)
        {
            arr[n] = malloc(1);
            n++;
        }
        else
        {
            if (rand() % 2 == 0)
            {
                arr[n] = malloc(1);
                n++;
            }
            else
            {
                free(arr[n-1]);
                n--;
            }
        }
    }
    while (n != -1)
    {
        free(arr[n]);
        n--;
    }
}

void testD()
{
    int * arr[50];
    int n = 0;
    int bytes = 0;
    while (n != 50)
    {
        if (n == 0)
        {
            bytes = rand() % 64;
            arr[n] = malloc(bytes + 1);
            n++;
        }
        else
        {
            if (rand() % 2 == 0)
            {
                bytes = rand() % 64;
                arr[n] = malloc(bytes + 1);
                n++;
            }
            else
            {
                free(arr[n-1]);
                n--;
            }
        }
    }
    while (n != -1)
    {
        free(arr[n]);
        n--;
    }
}

void testE()
{
    short * w = malloc(-1); 
    int * x = malloc(0);
    long * z = malloc(4095);

    int * s = (int*)malloc(4094);
    int * t = (int*)malloc(1);
    free(s); //resets

    int* ptr;
    free(ptr);

    short * freeTwice = (short*)malloc(1);
    free(freeTwice);
    free(freeTwice);
}

void testF()
{
    int * w = (int*)malloc(8);
    char * x = (char*)malloc(4);
    short * y = (short*)malloc(8);
    long * z = (long*)malloc(20); 

    free(x); 
    free(y); 
    print();
   
    free(w);
    free(z);
}

void testG() 
{
   int * w = (int*)malloc(8);
    char * x = (char*)malloc(4);
    short * y = (short*)malloc(8);
    long * z = (long*)malloc(20); 

    free(x); 
    free(y); 
    print();
   
    free(w);
    free(z);
    print();
   
}
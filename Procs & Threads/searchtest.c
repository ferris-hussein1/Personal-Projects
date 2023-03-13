#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "multitest.h"

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void allTests();

int *randomGenerator(int arrsize);

int *randomGenerator(int arrsize) {
    if (arrsize < 0) {
        fprintf(stderr,"\nERROR, SIZE OF ARRAY CANNOT BE NEGATiVE\n");
        exit(-1); //exits program
    }
    int * arr = (int*)malloc(sizeof(int)*arrsize);
    int i;
    for (i = 0; i < arrsize; i++) {arr[i] = i+1;}

    int swapCount = 0;
    if (arrsize > 1000) {  // Generate random for at least 75% of arrsize
        for (i = 0; i < arrsize ;i++) {
            int tmp = arr[i];
            int x = rand()%arrsize;
            arr[i] = arr[x];
            arr[x] = tmp; // Swap
            swapCount++;
            if (swapCount == arrsize*0.75) {break;}
        }
    } else {
         for (i = 0; i < arrsize ;i++) {
            int tmp = arr[i];
            int x = rand()%arrsize;
            arr[i] = arr[x];
            arr[x] = tmp; // Swap
            swapCount++;
         }
    }
 //   printf("Swaps: %d\n",swapCount);


    return arr;
}

void test1() { // size cannot exceed 500,0000
    int size = 1000;
    int target = 1001;
    int block = 250;

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("\nTest1\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }
    
    printf("\tTarget found in index: %d\n",index);
    printf("\tCheck: randArray[%d] = %d\n\n", index,randArray[index]);
}

void test2() {
    int size = 54321;
    int target = 12345;
    int block = 250;

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("Test2\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }

    printf("\tTarget found in index: %d\n",index);
    printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
}

void test3() {
    int size = 2344;
    int target = 1;
    int block = 250;

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("\nTest3\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }

    printf("\tTarget found in index: %d\n",index);
    printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
}


void test4() {
    int size = 100000;
    int target = 32982;
    int block = 250; //

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("\nTest4\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }

    printf("\tTarget found in index: %d\n",index);   
    printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
}

void test5() { 
    int size = 2019;
    int target = 2019; 
    int block = 100; //

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("\nTest5\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }
    
    printf("\tTarget found in index: %d\n",index);
    printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
}

void test6() {
    int size = 2019;
    int target = 2019; 
    int block = 250; //

    int * randArray = randomGenerator(size);
    int index = find(randArray,size,target,block);

    printf("\nTest6\n");
    printf("\tBlock Size: %d\n",block);
    printf("\tArray Size: %d\n",size);
    printf("\tLooking For: %d\n",target);

    if (index == -1) { fprintf(stderr,"\tTARGET NOT FOUND\n"); return;}
    else if (index == -2) {fprintf(stderr,"ERROR, BLOCK TOO BIG. BLOCK SIZE MUST BE BETWEEN 1-250\n"); return; }
    else if (index < -2){return;}

    printf("\tTarget found in index: %d\n",index);
    printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
}


void allTests() {
   
    int i;
    float stdv[100];

    float time1,time2,time3,time4,time5,time6;
    float min1,min2,min3,min4,min5,min6;
    float max1,max2,max3,max4,max5,max6;
    float st1,st2,st3,st4,st5,st6; // standard deviation
    // EXTRA CREDIT
    float mean1,mean2,mean3,mean4,mean5,mean6; // AVERAGE PROC OR THREAD SWITCHES
   
    struct timeval tv1, tv2;
    int temp;
    
    min1 = 0; max1 = 0; time1 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test1(); 
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        stdv[i]= min_max;
        if (min1 == 0 || min_max < min1 ) {min1 = min_max;} 
        if (max1 == 0 || min_max > max1) {max1 = min_max;}
        time1 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st1 = 0;
    float avg1 = (time1/100); 
    
    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean1 = 0;
    temp = pt_size();
    mean1 = avg1/temp;
    // EXTRA CREDIT

    float val = 0;
    float sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i]-avg1);
        sum += pow(val,2);
    }
    st1 = (sqrtf(sum/100)); //MICRO
  
   // return;

    min2 = 0; max2 = 0; time2 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test2();
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        stdv[i]= min_max;
        if (min2 == 0 || min_max < min2) {min2 = min_max;} 
        if (max2 == 0 || min_max > max2) {max2 = min_max;} 
        time2 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st2 = 0;
    float avg2 = (time2/100); 

    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean2 = 0;
    temp = pt_size();
    mean2 = avg2/temp;
    // EXTRA CREDIT

    val = 0;
    sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i] -avg2);
        sum += pow(val,2);
    }
    st2 = (sqrtf(sum/100)); //MICRO
   
    min3 = 0; max3 = 0; time3 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test3(); 
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        if (min3 == 0 || min_max < min3) {min3 = min_max;} 
        if (max3 == 0 || min_max > max3) {max3 = min_max;}
        time3 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st3 = 0;
    float avg3 = (time3/100); 

    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean3 = 0;
    temp = pt_size();
    mean3 = avg3/temp;
    // EXTRA CREDIT

    val = 0;
    sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i]-avg3);
        sum += pow(val,2);
    }
    st3 = (sqrtf(sum/100)); //MICRO

    
   
    min4 = 0; max4 = 0; time4 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test4(); 
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        if (min4 == 0 || min_max < min4) {min4 = min_max;} 
        if (max4 == 0 || min_max > max4) {max4 = min_max;}
        time4 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st4 = 0;
    float avg4 = (time4/100); 

    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean4 = 0;
    temp = pt_size();
    mean4 = avg4/temp;
    // EXTRA CREDIT

    val = 0;
    sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i]-avg4);
        sum += pow(val,2);
    }
    st4 = (sqrtf(sum/100)); //MICRO

   
    min5 = 0; max5 = 0; time5 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test5(); 
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        if (min5 == 0 || min_max < min5) {min5 = min_max;} 
        if (max5 == 0 || min_max > max5) {max5 = min_max;}
        time5 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st5 = 0;
    float avg5 = (time5/100); 

    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean5 = 0;
    temp = pt_size();
    mean5 = avg5/temp;
    // EXTRA CREDIT

    val = 0;
    sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i]-avg5);
        sum += pow(val,2);
    }
    st5 = (sqrtf(sum/100)); //MICRO

    min6 = 0; max6 = 0; time6 = 0;
    for (i=0; i<100;i++) {
        gettimeofday(&tv1, NULL);
        test6(); 
        gettimeofday(&tv2, NULL);
        float min_max = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)*1000000);
        if (min6 == 0 || min_max < min6) {min6 = min_max;} 
        if (max6 == 0 || min_max > max6) {max6 = min_max;}
        time6 += ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
    }
    st6 = 0;
    float avg6 = (time6/100); 

    // EXTRA CREDIT. DIVIDE AVERAGE TIME BY NUMBER OF PROC/THREADS TO GET AVERAGE PROC/THREAD TIME
    mean6 = 0;
    temp = pt_size();
    mean6 = avg6/temp;
    // EXTRA CREDIT

    val = 0;
    sum = 0;
    for (i = 0;i<100;i++) {
        val = (stdv[i]-avg6);
        sum += pow(val,2);
    }
    st6 = (sqrtf(sum/100)); //MICRO

    printf("\n");
    for (i = 0; i<60;i++) {printf("-");} // Just Separates Extra Credit
    printf("\nEXTRA CREDIT: ");
    if (proc_thread()==0) {printf("PROCESS");} else {printf("THREAD");}
    printf("\nAVERAGE TIME TO SWITCH BETWEEN ");
    if (proc_thread()==0) {printf("PROCESSES");} else {printf("THREADS");}
    printf("\n\tTest 1: %f microseconds\n",mean1);
    printf("\tTest 2: %f microseconds\n",mean2);
    printf("\tTest 3: %f microseconds\n",mean3);
    printf("\tTest 4: %f microseconds\n",mean4);
    printf("\tTest 5: %f microseconds\n",mean5);
    printf("\tTest 6: %f microseconds\n",mean6);
    for (i = 0; i<60;i++) {printf("-");} // Just Separates Extra Credit
 
    // Average Test Time
    printf("\nTEST CASE CALCULATIONS: ");
    if (proc_thread()==0) {printf("PROCESS");} else {printf("THREAD");}
    printf("\n\nTest1 Average Time: %f microseconds\n\tTest1 Min Time: %f microseconds\n\tTest1 Max Time: %f microseconds\n\tTest1 Standard Deviation: %f microseconds\n", time1/100,min1,max1,st1); 
    printf("\nTest2 Average Time: %f microseconds\n\tTest2 Min Time: %f microseconds\n\tTest2 Max Time: %f microseconds\n\tTest2 Standard Deviation: %f microseconds\n", time2/100,min2,max2,st2);
    printf("\nTest3 Average Time: %f microseconds\n\tTest3 Min Time: %f microseconds\n\tTest3 Max Time: %f microseconds\n\tTest3 Standard Deviation: %f microseconds\n", time3/100,min3,max3,st3);
    printf("\nTest4 Average Time: %f microseconds\n\tTest4 Min Time: %f microseconds\n\tTest4 Max Time: %f microseconds\n\tTest4 Standard Deviation: %f microseconds\n", time4/100,min4,max4,st4);
    printf("\nTest5 Average Time: %f microseconds\n\tTest5 Min Time: %f microseconds\n\tTest5 Max Time: %f microseconds\n\tTest5 Standard Deviation: %f microseconds\n", time5/100,min5,max5,st5);
    printf("\nTest6 Average Time: %f microseconds\n\tTest6 Min Time: %f microseconds\n\tTest6 Max Time: %f microseconds\n\tTest6 Standard Deviation: %f microseconds\n\n", time6/100,min6,max6,st6);

}

void tradeOff() { // This function Shows the trade off points depending on make call or make proc
    int i;
    
    for (i=250;i<=20000;i+=250) {
        struct timeval tv1, tv2;

        int size = i;
        int * randArray = randomGenerator(size);
        int target = 100;
        int block = 250;

        gettimeofday(&tv1, NULL);
        int index = find(randArray,size,target,block);
        gettimeofday(&tv2, NULL);

        float time = ((float) (tv2.tv_usec - tv1.tv_usec) + (float) (tv2.tv_sec - tv1.tv_sec)* 1000000);
        printf("\nArray Size: %d\n",i);
        printf("\tLooking For: %d\n",target);
        printf("\tTarget found in index: %d\n",index);
        printf("\tCheck: randArray[%d] = %d\n", index,randArray[index]);
        printf("\tTime Taken: %f microseconds\n",time);
    }
    // CHECK SMALLER SEGMENTS
}

int main (int argc, char** argv) {
    if (proc_thread() == 0) { printf("PROCESS\n\n"); } else { printf("THREAD\n\n"); }
    
    //tradeOff();   // UNCOMMENT THIS TO TEST TRADEOFF POINTS 
    allTests();
   
    return 0;
}
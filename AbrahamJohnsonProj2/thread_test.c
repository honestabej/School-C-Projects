// Driver program
#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

int globalVar = 0;    // One global variable
int threadID = 1;
int threadNum;
int timesRun;

void function(){
    int localCount = 1;
    while (localCount <= timesRun){
        if (threadID > threadNum){
            threadID = 1; // Reset threadID after passing threadNum
        }
        globalVar = globalVar + threadID;   // Update global variable before printing
        printf("\n This is %d th execution of thread %d with global var value %d \n", localCount, threadID, globalVar);
        localCount++; // Increment the localCount
        threadID++;   // Increment the threadID
        yield();
    }
}

int main(){
    // Read in numbers from file
    scanf("%d,%d", &threadNum, &timesRun);

    // Initialize a Queue
    InitQueue(&RunQ);

    if (threadNum == 0){
        printf("No Threads\n");
    } else {
        // Start threads
        for (int i = 0; i < threadNum; i++){
            start_thread(function);
        }
        run();
    }
}

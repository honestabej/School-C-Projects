#include "threads.h"
#include "sem.h"
#include <stdio.h>

// Global variables
int i = 0;
int wwc = 0;
int rwc = 0;
int wc = 0;
int rc = 0;

// Variables for main
int readers;
int writers;
int lineAmount;

// Declare semaphores
struct semaphore R_Sem;
struct semaphore W_Sem;

void reader(int readerID){
    // Entry
    if (wwc > 0 || wc > 0){     // If any writer waiting or writers inside
        rwc++;                  // Increment readers wait count
        P(&R_Sem);              // Decrement R_Sem->value then block once at 0
        rwc--;                  // Decrement readers wait count
    }
    rc++;

    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

    // Exit
    rc--;
    if (rc == 0 && wwc > 0){
        V(&W_Sem);
    }
    // Delete Reader from RunQ
    TCB_t *temp = DelQueue(&RunQ);
    // swapcontext to the next process/process
    swapcontext(&(temp->context), &(RunQ->context));
}

void writer(int writerID){
    // Entry
    if ( rc > 0 || wc > 0 || rwc > 0 || wwc > 0){
        wwc++;                  // Increment writers wait count
        P(&W_Sem);              // Decrement W_Sem->value then block once at 0
        wwc--;                  // Decrement writers wait count
    }
    wc++;

    i++;
    printf("\n This is the %d th writer writing value i = %d \n", writerID, i);
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n", writerID, i);

    // Exit
    wc--;
    if (rwc > 0){
        for (int j = 0; j < rwc; j++){
            V(&R_Sem);
        }
    } else if (wwc > 0){
        V(&W_Sem);
    }
    // Delete Reader from RunQ
    TCB_t *temp = DelQueue(&RunQ);
    // swapcontext to the next process/process
    swapcontext(&(temp->context), &(RunQ->context));
}

int main(){
    scanf("%d,%d",&readers,&writers);
    lineAmount = readers + writers;

    RunQ = (TCB_t*)malloc(sizeof(TCB_t));

    InitQueue(&RunQ);
    InitSem(&R_Sem, 0);
    InitSem(&W_Sem, 0);

    int j = 0;
    int input;
    while(j < lineAmount){
        scanf("%d",&input);
        if(input >= 0){
            start_thread(reader, input);
        } else {
            input = input * -1;
            start_thread(writer, input);
        }
        j++;
    }
    run();
    return 0;
}
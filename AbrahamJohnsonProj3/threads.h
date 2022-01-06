// Implement start_thread(), run(), yield()
#include "q.h"

struct TCB_t *ReadyQ;

void start_thread(void (*function) (int), int arg1){
    void *newStack = malloc(8192);                  // Allocate stack of size 8192
    TCB_t *newTCB = (TCB_t*)malloc(sizeof(TCB_t));  // Allocate a TCB
    init_TCB(newTCB, function, newStack, 8192, arg1);  // Call init_TCB
    AddQueue(&ReadyQ, newTCB);                      // Call AddQueue
    
}

void run(){
    ucontext_t parent;                       // Get a place to store the main context, for faking
    getcontext(&parent);                     // Magic sauce
    swapcontext(&parent, &(ReadyQ->context));  // Start the first thread
}

// Similar to run()
void yield(){
    struct TCB_t *temp = ReadyQ;                        // Create a copy of RunQ before we rotate it
    RotateQ(&ReadyQ);                                   // Rotate the RunQ
    swapcontext(&(temp->context), &(ReadyQ->context));  // Swap the context, from previous thread to the thread pointed to by RunQ
}

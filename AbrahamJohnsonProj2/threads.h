// Implement start_thread(), run(), yield()
#include "q.h"

struct TCB_t *RunQ;

void start_thread(void (*function) (void)){
    void *newStack = malloc(8192);                  // Allocate stack of size 8192
    TCB_t *newTCB = (TCB_t*)malloc(sizeof(TCB_t));  // Allocate a TCB
    init_TCB(newTCB, function, newStack, 8192);     // Call init_TCB
    AddQueue(&RunQ, newTCB);                        // Call AddQueue
}

void run(){
    ucontext_t parent;                       // Get a place to store the main context, for faking
    getcontext(&parent);                     // Magic sauce
    swapcontext(&parent, &(RunQ->context));  // Start the first thread
}

// Similar to run()
void yield(){
    struct TCB_t *temp = RunQ;                        // Create a copy of RunQ before we rotate it
    RotateQ(&RunQ);                                   // Rotate the RunQ
    swapcontext(&(temp->context), &(RunQ->context));  // Swap the context, from previous thread to the thread pointed to by RunQ
}

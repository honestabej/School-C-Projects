// Implement sephamore data structure
// Implement InitSem(semaphore, value)
// Implement P(sephamore)
// Implement V(sephamore)

typedef struct semaphore{
    int value;
    TCB_t *semQ;
} semaphore;

void InitSem(struct semaphore *S, int specValue){
    InitQueue(&(S->semQ));
    S->value = specValue;     // Initialize value field with specified value
}

// Decrements and blocks
void P(struct semaphore *S){
    if(S->value > 0){
        // Decrement process
        int decrement = S->value;
        decrement--;
        S->value = decrement;
    }else if (S->value <= 0){
        // Block process
        struct TCB_t *temp = DelQueue(&ReadyQ);   // Delete TCB of the thread from ReadyQ and store in temp
        AddQueue(&(S->semQ), temp);               // Insert temp at the end of the semQ
        
        // We dont yield() because we dont need it to rotate
        swapcontext(&(temp->context), &(ReadyQ->context));  // Swap the context, from previous thread to the thread pointed to by RunQ
        
    }
}

// Increments and unblocks
void V(struct semaphore *S, int numRun, int timesRun){
    // Increment process
    int increment = S->value;
    increment++;
    S->value = increment;

    if (S->semQ != NULL){
        // Unblock process
        struct TCB_t *temp = DelQueue(&(S->semQ));     // Delete the head of semQ and store in temp
        AddQueue(&ReadyQ, temp);                       // Insert temp at the end of ReadyQ
    }

    if(timesRun != numRun){
        yield();
    } else {
        // Removes process from ReadyQ after its last while loop
        TCB_t *temp = DelQueue(&ReadyQ);
        swapcontext(&(temp->context), &(ReadyQ->context));
    }
}
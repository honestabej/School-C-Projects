// This file will include all of the function implementations and data structures
#include "TCB.h"
#include <stdlib.h>

// Returns pointer to new element
struct TCB_t *NewItem(){
    struct TCB_t *newElement = (struct TCB_t*)malloc(sizeof(struct TCB_t)); // Make a pointer to a new element
    return newElement;
}

// Make a new queue and set the head to NULL
void InitQueue(struct TCB_t **head){
    *head = NULL;
}

// Add an item (pointed to by *item) to the queue (pointed to by *head)
void AddQueue(struct TCB_t **head, struct TCB_t *item){ 
    // If queue is empty
    if (*head == NULL){        
        // Set the head of linked list to point to item and have item point to itself
        *head = item;           
        (*head)->next = *head;  
        (*head)->prev = *head;  

    // If queue has only one item
    } else if ((*head)->next == *head){     
        // Insert item at the end of the linked list and make them point them to each other
        (*head)->next = item;       
        (*head)->prev = item;
        item->next = (*head);
        item->prev = (*head);

    // If queue has more than two items
    } else {
        TCB_t *temp = *head;     // Create new pointer pointing to head
        // Traverse the linked list to find the end 
        while (temp->next != *head){
            temp = temp->next;
        }
        // Set the item at the end of the linked list
        item->next = temp->next;
        item->prev = temp;
        // Adjust the old end of the linked list to point to item and the head of the linked list's prev to point to the new end
        temp->next = item;
        (*head)->prev = item;
    }
}

// Deletes an item from the head and returns a pointer to the deleted item
struct TCB_t *DelQueue(struct TCB_t **head){
    // If queue is empty
    if (*head == NULL){
        return *head;

    // If only one item in queue
    } else if ((*head)->next == *head){
        TCB_t *temp = *head;
        *head = NULL;
        return temp;

    // If multiple items in the queue
    } else {
        TCB_t *temp = *head;
        *head = (*head)->next; // Make head point to second item
        // Remove any pointers to the first node
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        // Make temp pointer point to itself
        temp->next = temp;
        temp->prev = temp;
        return temp;
    }
}

// Moves the header pointer to the next element in the queue. 
// This is equivalent to AddQ(&head, DeleteQ(&head)), 
// but is simpler to use and more efficient to implement.
void RotateQ(struct TCB_t **head){
    AddQueue(head, DelQueue(head));
}

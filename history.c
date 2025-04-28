#include "history.h"

/* ****************************** */
/* Stack Functions Implementation */
/* ****************************** */

Location *history[MaxLocations];
int top = -1;

// Function to push things to the stack (movement history)
void push(Location *prev)
{ // Argument is the pointer to the location of a node
    if (top == MaxLocations - 1)
        //printf("Stack is full\n");
        return;
    else
    {
        top++;                      // Increment top
        history[top] = prev;        // Assign the given pointer to location
    }
}

// Function to pop things from the stack (movement history)
Location *pop()
{                                   // Arguments include the stack (movement history) itself
    if (top == -1)                  // If the stack is empty
        //printf("Stack is empty\n"); // Print error
        return NULL;
    else
    {
        Location *temp = history[top]; // Create a temprary pointer to store the top of the stack (movement history)
        top--;                      // Decrement Top
        return temp;                // Return the pointer to the location of what was popped
    }
}

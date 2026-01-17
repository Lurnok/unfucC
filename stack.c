#include <stdlib.h>
#include <limits.h>
#include "stack.h"

// LIFO stack implementation found i don't even remember where but it's good

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        return NULL; 
    }
    stack->capacity = capacity;
    stack->top = -1; 
    
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    if (!stack->array) {
        free(stack); 
        return NULL;
    }
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        return;
    }
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top--];
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }
    return stack->array[stack->top];
}

void freeStack(struct Stack* stack) {
    if (stack) {
        free(stack->array);
        free(stack); 
    }
}
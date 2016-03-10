//
// Created by Ben Goodspeed on 2016-03-10.
//
#include <stdlib.h>
#include "acstack.h"

ACStack *ACStack_new(int maxSize) {
    ACStack *stack = malloc(sizeof(ACStack));
    stack->bottom = malloc(maxSize * sizeof(int));
    stack->maxSize = maxSize;
    stack->currentSize = 0;

    return stack;
}

int ACStack_maxSize(ACStack *stack) {
    if (!stack) return -1;

    return stack->maxSize;
}
int ACStack_currentSize(ACStack *stack) {
    if (!stack) return -1;

    return stack->currentSize;
}
void ACStack_free(ACStack *stack) {

    if(!stack) return;

    if(stack->bottom) free(stack->bottom);

    free(stack);
}


void ACStack_push(ACStack *stack, int value) {
    stack->bottom[stack->currentSize] = value;

    stack->currentSize++;
}

int ACStack_peek(ACStack *stack) {
    return stack->bottom[stack->currentSize - 1];
}

int ACStack_pop(ACStack *stack) {
    stack->currentSize--;
    return stack->bottom[(stack->currentSize)];
}

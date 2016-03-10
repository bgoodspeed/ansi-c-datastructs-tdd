//
// Created by Ben Goodspeed on 2016-03-10.
//

#ifndef ANSIC_STACK_H
#define ANSIC_STACK_H

typedef struct ACStack_t {
    int *bottom;
    int maxSize;
    int currentSize;
} ACStack;


ACStack *ACStack_new(int maxSize);
void ACStack_free(ACStack *stack);

int ACStack_maxSize(ACStack *stack);
int ACStack_currentSize(ACStack *stack);



void ACStack_push(ACStack *stack, int value);
int ACStack_peek(ACStack *stack);
int ACStack_pop(ACStack *stack);


#endif //ANSIC_STACK_H

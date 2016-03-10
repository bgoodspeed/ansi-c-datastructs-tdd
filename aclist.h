//
// Created by Ben Goodspeed on 2016-03-10.
//

#ifndef ANSIC_LIST_H
#define ANSIC_LIST_H

typedef void *ACListContent;

typedef struct ACListNode_t {
    struct ACListNode_t *next;
    ACListContent value;
} ACListNode;

typedef struct ACList_t {
    ACListNode *head;
} ACList;



ACList *ACList_new();


void ACList_free(ACList *list);

ACListNode *ACListNode_new(ACListContent v);

int ACList_length(ACList *list);

ACListNode *ACList_insert(ACList *list, int value);

ACListContent ACList_get(ACList *list, int index);
ACListNode *ACList_get_at(ACList *list, int index);


int ACList_index_of(ACList *list, ACListNode *node);
void ACList_remove(ACList *list, ACListNode *node);

void ACList_map_in_place(ACList *list, ACListContent (*fp)(ACListContent));

void ACList_filter_in_place(ACList *list, ACListContent (*fp)(ACListContent));
#endif //ANSIC_LIST_H

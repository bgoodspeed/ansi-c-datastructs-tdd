#include <stdlib.h>
#include "aclist.h"




ACList *ACList_new() {
    ACList *list = malloc(sizeof(ACList));
    list->head = NULL;
    return list;
}


// TODO how to test this?
void ACList_free(ACList *list) {
    ACListNode *node, *old;
    if(!list) return;

    node = list->head;
    old = list->head;
    while(node) {
        node = node->next;

        free(old);
        old = node;
    }

    free(list);
}

ACListNode *ACListNode_new(ACListContent v) {
    ACListNode *node = malloc(sizeof(ACListNode));
    node->next = NULL;
    node->value = v;

    return node;
}

int ACList_length(ACList *list) {
    ACListNode *node;
    int length = 0;

    if (!list) return -1;

    if (!list->head) return 0;
    node = list->head;
    while(node) {
        length++;
        node = node->next;
    }

    return length;
}

void ACList_insert(ACList *list, int value) {
    ACListNode *node;
    if (!list->head) {
        list->head = ACListNode_new(value);
        return;
    }

    node =  list->head;


    while(node->next) {
        node = node->next;
    }

    node->next = ACListNode_new(value);


}

ACListContent ACList_get(ACList *list, int index) {
    ACListNode *node;

    if (!list) return -1;
    if (!list->head) return -1; // TODO Sentinel

    node = list->head;

    for(int i = 0; i < index; i++) {
        if (!node) return -1;
        node = node->next;
    }


    if (!node) return -1;
    return node->value;

}

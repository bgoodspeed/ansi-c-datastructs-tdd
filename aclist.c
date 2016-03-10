#include <stdlib.h>
#include "aclist.h"

#include <stdio.h>



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

ACListNode *ACList_insert(ACList *list, int value) {
    ACListNode *node;
    if (!list->head) {
        list->head = ACListNode_new(value);
        return list->head;
    }

    node =  list->head;


    while(node->next) {
        node = node->next;
    }

    node->next = ACListNode_new(value);

    return node->next;

}


int ACList_index_of(ACList *list, ACListNode *target) {
    if (!list || !list->head) return -1;

    for (int i = 0; i < ACList_length(list); i++) {
        if (target == ACList_get_at(list, i)) return i;
    }

    return -1;

}

ACListNode * ACList_get_at(ACList *list, int index) {
    ACListNode *node;

    if (!list) return NULL;
    if (!list->head) return NULL; // TODO Sentinel

    node = list->head;

    for(int i = 0; i < index; i++) {
        if (!node) return NULL;
        node = node->next;
    }

    return node;

}

ACListContent ACList_get(ACList *list, int index) {
    ACListNode *node = ACList_get_at(list, index);

    if (!node) return -1;

    return node->value;
}

void ACList_remove(ACList *list, ACListNode *deletee) {
    ACListNode *node, *prev, *next;
    int len = 0, idx = 0, p, n;
    if (!list || !list->head) return;


    len = ACList_length(list);
    idx = ACList_index_of(list, deletee);

    p = idx - 1;
    n = idx + 1;

    // node = ACList_get_at(list, idx);

    if (p < 0) {  // deleting head
        list->head = deletee->next;
        free(deletee);
        return;
    }
    prev = ACList_get_at(list, p);
    prev->next = deletee->next;


    free(deletee);
}


void ACList_map_in_place(ACList *list, ACListContent (*fp)(ACListContent)) {
    ACListNode *node;
    if (!list) return;
    if (!list->head) return;
    node = list->head;

    while(node) {
        node->value = fp(node->value);
        node = node->next;
    }

}

void ACList_filter_in_place(ACList *list, ACListContent (*fp)(ACListContent)) {
    ACListNode *node, *prev;
    if (!list) return;
    if (!list->head) return;
    node = list->head;

    while(node) {
        if (!fp(node->value)) {
            ACList_remove(list, node);
        }
        node = node->next;
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

void insert(dlist *list, item* thing, bool atTail) {

    node* refNode = NULL;
    struct node_ *new_node = (struct node_ *) malloc (sizeof (struct node_));

    if (!atTail) {
        refNode = list->head;
        list->head = new_node;   
    }
    else {
        refNode = list->tail;
        list->tail = new_node;
    }

    new_node->thing = thing;
    new_node->ptr = refNode;

    if (refNode != NULL) {
        struct node_ *next = refNode->ptr;
        refNode->ptr = (node*) ((uintptr_t)new_node ^ (uintptr_t)next);
    }
}

item* search(dlist *list, bool (*matches)(item *)) {

    node *current_item = list->head;
    node *prev = NULL;

    while (current_item != NULL) {
        if (current_item->thing == matches) {
            return current_item->thing;
        }
        node* temp = current_item;
        current_item = (node*) ((uintptr_t)(current_item->ptr) ^ (uintptr_t)prev);
        prev = temp;
    }

    return NULL;
}
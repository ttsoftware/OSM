#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

node* xor(node* ptr1, node* ptr2) {
    return (node*) ((uintptr_t)ptr1 ^ (uintptr_t)ptr2);
}

void insert(dlist *list, item* thing, bool atTail) {
    node* refNode = NULL;
    struct node_ *new_node = (struct node_ *) malloc (sizeof (struct node_));

    if (!atTail) {
        refNode = list->head;
        list->head = new_node;
        if (list->tail == NULL) {
            list->tail = refNode;
        }
    }
    else {
        refNode = list->tail;
        list->tail = new_node;
        if (list->head == NULL) {
            list->head = refNode;
        }
    }

    new_node->thing = thing;
    new_node->ptr = refNode;

    if (refNode != NULL) {
        struct node_ *next = refNode->ptr;
        refNode->ptr = xor(new_node, next);
    }
}

item* extract(dlist *list, bool atTail) {
    if (atTail) {
        node *tail = list->tail;
        node *new_tail = tail->ptr;
        new_tail->ptr = xor(tail, new_tail->ptr);
        list->tail = new_tail;
        return tail->thing;
    }
    node *head = list->head;
    node *new_head = head->ptr;
    new_head->ptr = xor(head, new_head->ptr);
    list->head = new_head;
    return head->thing;
}

item* search(dlist *list, bool (*matches)(item *)) {
    node *current_item = list->head;
    node *prev = NULL;

    while (current_item != NULL) {
        if (matches(current_item->thing)) {
            return current_item->thing;
        }
        node* temp = current_item;
        current_item = xor(current_item->ptr, prev);
        prev = temp;
    }
    return NULL;
}

void reverse(dlist *list) {
    node *head = list->head;
    node *tail = list->tail;

    list->head = tail;
    list->tail = head;
}
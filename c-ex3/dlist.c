#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

/*
 * Custom XOR function for more clean code.
 **/
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
        struct node_ *sibling = refNode->ptr;
        refNode->ptr = xor(new_node, sibling);
    }
}

/*
 * We use the fact that due to the associativity of xor,
 *   (a = b xor c) = (b = a xor c)
 * and the fact that 
 *   b xor 0 = b
 * to update the pointers stored in the outer nodes.
 **/
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

/*
 * Simply iterate over the elements, and use the input function.
 **/
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

/*
 * The head points to the 2nd element, while the tail points to the 2nd-last element.
 * The 2nd element points to the 3rd element, and so forth.
 * By swapping the head and tail, the list appears to be reversed, 
 * since the head now points to the 2nd-last element.
 **/
void reverse(dlist *list) {
    node *head = list->head;
    node *tail = list->tail;

    list->head = tail;
    list->tail = head;
}

/*
 * Double-linked list implementation
 */

#include "lib/dlist.h"
#include "kernel/kmalloc.h"

void insert(dlist *this, item* thing, bool atTail) {
    
    dlist list = *this;

    node head = *list.head;
    //node tail = *list.tail;

    struct node_ *new_node = (struct node_ *) kmalloc (sizeof (struct node_));
    
    new_node->thing = thing; 
    new_node->ptr = (node*)((int)&head ^ 0);

    //if (&head != NULL) {
        struct node_* next = (node*) ((int)head.ptr ^ 0);
        head.ptr = (node*) ((int)new_node ^ (int)next);
    //}
 
    if (!atTail) {
        list.head = new_node;   
    }
}
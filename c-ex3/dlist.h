#ifndef DLIST_H
#define DLIST_H

typedef int bool;
typedef void item; /* we store pointers */

typedef struct node_ {
    item         *thing;
    struct node_ *ptr;
} node;

typedef struct dlist_ {
    node *head;
    node *tail;
} dlist;

void insert(dlist *this, item* thing, bool atTail);
item* extract(dlist *this, bool atTail);
void reverse(dlist *this);
item* search(dlist *this, bool (*matches)(item *));

#endif /* DLIST_H */

#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct NODE {
        struct NODE *prev;
        struct NODE *next;
        void *data;
}NODE;

typedef struct LIST {
    size_t count;
    NODE *first;
    NODE *last;
}LIST;


LIST *list_create(void (*callback_list_create)(LIST **lst));
void list_destroy(LIST *lst, void (*callback_func)(void *data));
void  list_push(LIST *lst, void *data, void (*callback_func)(void *data));
void *list_pop(LIST *lst);

#endif // LIST_H

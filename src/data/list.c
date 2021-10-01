#include "list.h"

LIST *list_create(void (*callback_list_create)(LIST **))
{
    LIST *lst = NULL;

    lst = calloc(1, sizeof(LIST));

    if(!lst){
        return NULL;
    }

    if(callback_list_create){
        callback_list_create(&lst);
        return lst;
    }

    return lst;
}

void list_destroy(LIST *lst, void (*callback_func)(void *))
{

    NODE *current = NULL;


    while(lst->last){
        current = lst->last;

        if(current->prev){
            current->prev->next = NULL;
            lst->last = current->prev;
        }else {
            lst->first = NULL;
            lst->last = NULL;
        }

        lst->count--;

        if(callback_func){
            callback_func(current->data);
        }else {
            free(current->data);
        }

        free(current);
    }

    assert(lst->count == 0);
    assert(lst->first == 0);
    assert(lst->last == 0);
    free(lst);

}

void list_push(LIST *lst, void *data, void (*callback_func)(void *))
{
    NODE *new_node = NULL;

    new_node = calloc(1,sizeof(NODE));

    if(!new_node){
        return;
    }

    new_node->data = data;

    if(!lst->first)
    {
        lst->first = new_node;
        lst->last = new_node;

        if(callback_func){
            callback_func((LIST*)lst);
        }
        lst->count++;
        return;
    }

    new_node->prev = lst->last;
    new_node->next = new_node;
    lst->last  = new_node;
    if(callback_func){
        callback_func((LIST*)lst);
    }
    lst->count++;

}

void* list_pop(LIST *lst)
{

    NODE *current = NULL;
    void* data = NULL;

    current = lst->last;
    data = current->data;

    if(current->prev)
    {
        current->prev->next = NULL;
        lst->last = current->prev;
        lst->count--;
        free(current);
        return data;
    }

    lst->first = NULL;
    lst->last  = NULL;
    lst->count--;
    free(current);

    return data;


}

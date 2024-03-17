#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

enum StackStatus
{
    OK = 1,

    PUSH_ERR = 0,

    ALLOCATE_ERR,
    EMPTY_STK,



    INVALID_SIZE,
};

struct List_Elem
{
    struct List_Elem* prev_elem;
    void*             data;
};

struct Stack
{
    size_t            size;
    size_t            elem_size;
    struct List_Elem* top_elem;
};

struct Stack* stack_ctr(size_t size, size_t element_size);
int           push(struct Stack* st, void* buffer);
int           top(struct Stack* st, void* buffer);
int           pop(struct Stack* st);
struct Stack* stack_dtr(struct Stack* st);

#endif

#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>

struct List_Elem
{
    struct List_Elem* prev_elem;
    int               data;
};

struct Stack
{
    size_t            size;
    struct List_Elem* top_elem;
};

struct Stack* stack_ctr(size_t size);
int           push(struct Stack* st, int buffer);
int           top(struct Stack* st, int* buffer);
int           pop(struct Stack* st);
struct Stack* stack_dtr(struct Stack* st);

#endif

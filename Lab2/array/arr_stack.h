#ifndef _ARR_H_
#define _ARR_H_

#include <stdio.h>

enum StackStatus
{
    OK = 1,

    PUSH_ERR = 0,

    REALLOC_ERR,
    EMPTY_STK,

    INVALID_SIZE,

};

struct Stack
{
    size_t size;
    size_t capacity;
    size_t elem_size;

    void*  array;
};

int StackRealloc(struct Stack* stk, size_t new_capacity);

struct Stack* stack_ctr(size_t size, size_t element_size);
int           push(struct Stack* st, void* buffer);
int           top(struct Stack* st, void* buffer);
int           pop(struct Stack* st);
struct Stack* stack_dtr(struct Stack* st);

#endif

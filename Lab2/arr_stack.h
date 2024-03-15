#ifndef _ARR_H_
#define _ARR_H_

#include <stdio.h>

struct Stack
{
    size_t size;
    size_t capacity;
    int*   array;
};

void StackRealloc(struct Stack* stk, size_t new_capacity);

struct Stack* stack_ctr(size_t size);
int           push(struct Stack* st, int buffer);
int           top(struct Stack* st, int* buffer);
int           pop(struct Stack* st);
struct Stack* stack_dtr(struct Stack* st);

#endif

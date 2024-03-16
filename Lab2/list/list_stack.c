#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list_stack.h"

#include "constants.h"

#define LIST_STACK 1

#if LIST_STACK

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct Stack* stack_ctr(size_t size, size_t element_size)
{
    struct Stack* stk = (struct Stack*) calloc(1, sizeof(struct Stack));
    assert(stk);

    stk->size      = 0;
    stk->top_elem  = NULL;
    stk->elem_size = element_size;

    return stk;
}

// ---------------------------------------------------------------------

int push(struct Stack* st, void* buffer)
{
    assert(st);
    assert(buffer);

    struct List_Elem* new_elem = (struct List_Elem*) calloc(1, sizeof(struct List_Elem));

    if (!new_elem)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR LISTED STACK\n");
        return PUSH_ERR;
    }

    void* elem = (void*) calloc(1, st->elem_size);
    memcpy(elem, buffer, st->elem_size);

    if (!elem)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR ELEMENT\n");
        return PUSH_ERR;
    }

    new_elem->prev_elem = st->top_elem;
    new_elem->data      = elem;

    st->top_elem = new_elem;
    st->size++;

    return OK;
}

// ---------------------------------------------------------------------

int top(struct Stack* st, void* buffer)
{
    assert(st);

    void* data = st->top_elem->data;

    memcpy(buffer, data, st->elem_size);
    if (!buffer)
    {
        fprintf(stderr, "FAILED TO COPY MEMORY FOR ELEMENT\n");
        return ALLOCATE_ERR;
    }

    return OK;
}

// ---------------------------------------------------------------------

int pop(struct Stack* st)
{
    assert(st);

    if (st->top_elem == NULL)
    {
        fprintf(stderr, "CAN NOT POP FROM EMPTY STACK\n");
        return EMPTY_STK;
    }

    struct List_Elem* prev_elem = st->top_elem->prev_elem;

    free(st->top_elem);

    st->top_elem = prev_elem;
    st->size--;

    return OK;
}

// ---------------------------------------------------------------------

struct Stack* stack_dtr(struct Stack* st)
{
    assert(st);

    size_t size = st->size;

    while (size--)
        pop(st);

    free(st);

    return NULL;
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#endif

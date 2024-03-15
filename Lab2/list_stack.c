#include <stdlib.h>
#include <assert.h>

#include "list_stack.h"

#include "constants.h"

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct Stack* stack_ctr(size_t size)
{
    struct Stack* stk = (struct Stack*) calloc(1, sizeof(struct Stack));
    assert(stk);

    stk->size     = 0;
    stk->top_elem = NULL;

    return stk;
}

// ---------------------------------------------------------------------

int push(struct Stack* st, int buffer)
{
    assert(st);
    assert(buffer);

    struct List_Elem* new_elem = (struct List_Elem*) calloc(1, sizeof(struct List_Elem));

    if (!new_elem)
    {
        fprintf(stderr, "FAILED TO ALLOCATE MEMORY FOR LISTED STACK\n");
        return 0;
    }

    new_elem->prev_elem = st->top_elem;
    new_elem->data      = buffer;

    st->top_elem = new_elem;
    st->size++;

    return 1;
}

// ---------------------------------------------------------------------

int top(struct Stack* st, int* buffer)
{
    assert(st);

    int data = st->top_elem->data;

    *buffer = data;

    return data;
}

// ---------------------------------------------------------------------

int pop(struct Stack* st)
{
    assert(st);

    if (st->top_elem == NULL)
    {
        fprintf(stderr, "CAN NOT POP FROM EMPTY STACK\n");
        return 0;
    }

    struct List_Elem* prev_elem = st->top_elem->prev_elem;

    free(st->top_elem);

    st->top_elem = prev_elem;
    st->size--;

    return 1;
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

#include <stdlib.h>
#include <assert.h>

#include "arr_stack.h"

#include "constants.h"

#if ARR_STACK

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct Stack* stack_ctr(size_t size)
{
    struct Stack* st    = (struct Stack*) calloc(1, sizeof(struct Stack));
    int*          array = calloc(size, sizeof(int));

    assert(st);
    assert(array);

    st->array    = array;
    st->size     = 0;
    st->capacity = size;

    return st;
}

// ---------------------------------------------------------------------

int push(struct Stack* st, int buffer)
{
    assert(st);
    assert(buffer);

    if (st->capacity == st->size)
        StackRealloc(st, 2 * st->capacity);

    st->array[st->size++] = buffer;

    return 1;
}

//-----------------------------------------------------------------------------------------------------

void StackRealloc(struct Stack* stk, size_t new_capacity)
{
    assert(stk);

    if (new_capacity <= MIN_CAPACITY)
        new_capacity = MIN_CAPACITY;

    int* array    = stk->array;
    size_t new_size = new_capacity * sizeof(int);

    int* temp = (int*) realloc(array, new_size);

    if (temp == NULL)
        abort();
    else
        array = temp;

    stk->array    = array;
    stk->capacity = new_capacity;
}

// ---------------------------------------------------------------------

int top(struct Stack* st, int* buffer)
{
    assert(st);
    assert(buffer);

    int data = st->array[st->size - 1];

    *buffer = data;

    return data;
}

// ---------------------------------------------------------------------

int pop(struct Stack* st)
{
    assert(st);

    if (st->size == 0)
    {
        fprintf(stderr, "CAN NOT POP FROM EMPTY STACK\n");
        return 0;
    };

    int last_elem = (st->array)[--(st->size)];

    (st->array)[(st->size)] = 0;

    // FOR NEXT IF ---v
    // if we will divide capacity by 2, we will have situations like:
    //   pop when (size == 0.5 * capacity) cause realloc
    //   push after that pop will also cause realloc (size == capacity)
    //   so, let's divide by 4, to avoid two reallocs

    if (st->size <= st->capacity / 4)
        StackRealloc(st, st->capacity / 2);

    return 1;
}

// ---------------------------------------------------------------------

struct Stack* stack_dtr(struct Stack* st)
{
    assert(st);

    free(st->array);
    free(st);

    return NULL;
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#endif

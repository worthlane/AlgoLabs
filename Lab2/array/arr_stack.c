#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "arr_stack.h"

#include "constants.h"

#define ARR_STACK 0

#if ARR_STACK

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

struct Stack* stack_ctr(size_t size, size_t element_size)
{
    struct Stack* st    = (struct Stack*) calloc(1, sizeof(struct Stack));
    void*         array = calloc(size, element_size);

    if (!st || !array)
    {
        printf("CAN NOT ALLOCATE MEM FOR STACK\n");
        return NULL;
    }

    assert(st);
    assert(array);

    st->array     = array;
    st->size      = 0;
    st->capacity  = size;
    st->elem_size = element_size;

    return st;
}

// ---------------------------------------------------------------------

int push(struct Stack* st, void* buffer)
{
    assert(st);
    assert(buffer);

    if (st->size > st->capacity || st->size < 0)
    {
        fprintf(stderr, "INVALID SIZE\n");
        return INVALID_SIZE;
    };

    if (st->capacity == st->size)
    {
        int realloc_status = StackRealloc(st, 2 * st->capacity);
        if (realloc_status != OK)
            return realloc_status;
    }

    void* elem = st->array + st->elem_size * st->size;
    memcpy(elem, buffer, st->elem_size);

    if (!elem)
    {
        printf("CAN NOT ALLOCATE MEMORY FOR ELEMENT\n");
        return PUSH_ERR;
    }

    st->size++;

    return OK;
}

//-----------------------------------------------------------------------------------------------------

int StackRealloc(struct Stack* stk, size_t new_capacity)
{
    assert(stk);

    if (new_capacity <= MIN_CAPACITY)
        new_capacity = MIN_CAPACITY;

    void* array    = stk->array;
    size_t new_size = new_capacity * stk->elem_size;

    void* temp = (void**) realloc(array, new_size);

    if (temp == NULL)
    {
        return REALLOC_ERR;
    }
    else
        array = temp;

    stk->array    = array;
    stk->capacity = new_capacity;

    return OK;
}

// ---------------------------------------------------------------------

int top(struct Stack* st, void* buffer)
{
    assert(st);
    assert(buffer);

    memcpy(buffer, st->array + (st->size - 1) * st->elem_size, st->elem_size);

    return OK;
}

// ---------------------------------------------------------------------

int pop(struct Stack* st)
{
    assert(st);

    if (st->size == 0)
    {
        fprintf(stderr, "CAN NOT POP FROM EMPTY STACK\n");
        return EMPTY_STK;
    };

    st->size--;

    if (st->size > st->capacity || st->size < 0)
    {
        fprintf(stderr, "INVALID SIZE\n");
        return INVALID_SIZE;
    };

    // FOR NEXT IF ---v
    // if we will divide capacity by 2, we will have situations like:
    //   pop when (size == 0.5 * capacity) cause realloc
    //   push after that pop will also cause realloc (size == capacity)
    //   so, let's divide by 4, to avoid two reallocs
    //   In this case, the amortization cost of each operation will be O(1).
    //   

    if (st->size <= st->capacity / 4)
    {
        int realloc_status = StackRealloc(st, st->capacity / 2);
        if (realloc_status != OK)
            return realloc_status;
    }

    return OK;
}

// ---------------------------------------------------------------------

struct Stack* stack_dtr(struct Stack* st)
{
    assert(st);

    while (st->size > 0)
    {
        pop(st);
    }

    free(st->array);
    free(st);

    return NULL;
}

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#endif

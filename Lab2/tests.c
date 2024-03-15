#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "tests.h"

#include "constants.h"

// ---------------------------------------------------------------------

double first_test()
{
    clock_t duration = 0;

    for (size_t i = 0; i < TEST_AMT; i++)
    {
         struct Stack* st = stack_ctr(MIN_CAPACITY);

        clock_t start = clock();
        RunFirstAlgo(st);
        clock_t end   = clock();

        duration += end - start;

        stack_dtr(st);
    }

    return ((double) duration) / (CLOCKS_PER_SEC);
}

// ---------------------------------------------------------------------

void RunFirstAlgo(struct Stack* st)
{
    assert(st);

    for (int i = 0; i < 1000000; i++)           // pushing 10^6 elems in stack
    {
        push(st, PUSHING_DATA);
    }

    while (st->size > 100000)                   // doing iterations while size > 100000
    {
        int size = st->size;

        for (int i = 0; i < size / 2; i++)
            pop(st);

        for (int i = 0; i < size / 4; i++)
            push(st, PUSHING_DATA);
    }
}

// ---------------------------------------------------------------------

double second_test()
{
    clock_t duration = 0;

    for (size_t i = 0; i < TEST_AMT; i++)
    {
         struct Stack* st = stack_ctr(MIN_CAPACITY);

        clock_t start = clock();
        RunSecondAlgo(st);
        clock_t end   = clock();

        duration += end - start;

        stack_dtr(st);
    }

    return ((double) duration) / (CLOCKS_PER_SEC);
}

// ---------------------------------------------------------------------

void RunSecondAlgo(struct Stack* st)
{
    assert(st);

    for (int i = 0; i < 1000000; i++)               // pushing 10^6 elems in stack
        push(st, PUSHING_DATA);

    for (int i = 0; i < 100; i++)                   // for 100 times pop and push 10000 elements from stack
    {
        for (int j = 0; j < 10000; j++)
            pop(st);

        for (int j = 0; j < 10000; j++)
            push(st, PUSHING_DATA);
    }

    while (st->size > 100000)                       // do iterations while size > 10^5
    {
        int size = st->size;

        for (int i = 0; i < size / 2; i++)
            pop(st);

        for (int i = 0; i < size / 4; i++)
            push(st, PUSHING_DATA);
    }

    for (int i = 0; i < 100; i++)                   // for 100 times pop and push 10000 elements from stack
    {
        for (int j = 0; j < 10000; j++)
            pop(st);

        for (int j = 0; j < 10000; j++)
            push(st, PUSHING_DATA);
    }
}

// ---------------------------------------------------------------------

double third_test()
{
    srand(time(0));

    clock_t duration = 0;

    for (size_t i = 0; i < TEST_AMT; i++)
    {
        struct Stack* st = stack_ctr(MIN_CAPACITY);

        for (int i = 0; i < 1000000; i++)               // pushing 10^6 elems in stack
            push(st, PUSHING_DATA);

        clock_t start = clock();
        RunThirdAlgo(st);
        clock_t end   = clock();

        duration += end - start;

        stack_dtr(st);
    }

    return ((double) duration) / (CLOCKS_PER_SEC);
}

// ---------------------------------------------------------------------

void RunThirdAlgo(struct Stack* st)
{
    assert(st);

    for (int i = 0; i < 1000000; i++)               // for 10^6 times we generate random number {1,2}
    {
        int num = (rand() % 2) + 1;
        if (num == 1)                               // push if generated 1
            push(st, PUSHING_DATA);
        else                                        // pop if generated 2
            pop(st);
    }
}

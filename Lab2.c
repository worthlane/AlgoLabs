#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define LIST_STACK 1

#define ARR_STACK 0

static const size_t MIN_CAPACITY = 16;
static const int    PUSHING_DATA = 228;
static const size_t TEST_AMT     = 20;

static const size_t POINTS_SHIFT = 1000;
static const size_t MAX_POINTS   = 1000000;
static const size_t POINTS_AMT   = MAX_POINTS / POINTS_SHIFT;

static const char*  DEFAULT_OUT  = "data.txt";

#if LIST_STACK

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

#endif

#if ARR_STACK

struct Stack
{
    size_t size;
    size_t capacity;
    int*   array;
};

void StackRealloc(struct Stack* stk, size_t new_capacity);

#endif

struct Stack* stack_ctr(size_t size);
int           push(struct Stack* st, int buffer);
int           top(struct Stack* st, int* buffer);
int           pop(struct Stack* st);
struct Stack* stack_dtr(struct Stack* st);

double first_test();
void   RunFirstAlgo(struct Stack* st);

double second_test();
void   RunSecondAlgo(struct Stack* st);

double third_test();
void   RunThirdAlgo(struct Stack* st);


double  GetPushTime(const int push_amt);
void    GetGraphData(double* graph_points);

// =====================================================================

int main(const int argc, const char* argv[])
{
    const char* output_file = DEFAULT_OUT;
    if (argc >= 2)
        output_file = argv[1];

    double graph_points[POINTS_AMT + 1] = {};            //  time(n) = graph_points[n / 1000]
                                                         //  we add 1 because of we include n = 0 and n = 10^6

    GetGraphData(graph_points);

    FILE* out = fopen(output_file, "w");
    if (!out)
    {
        fprintf(stderr, "CAN NOT OPEN \"%s\"\n", output_file);
        return 1;
    }

    for (int i = 0; i <= POINTS_AMT; i++)
        fprintf(out, "%zu %lf\n", i * POINTS_SHIFT, graph_points[i]);

    return 0;
}

// ---------------------------------------------------------------------

void GetGraphData(double* graph_points)
{
    for (int i = 0; i <= POINTS_AMT; i++)
    {
        printf("COUNTING %zu:\n", i * POINTS_SHIFT);

        double time = GetPushTime(i * POINTS_SHIFT);

        graph_points[i] = time;
    }
}

// ---------------------------------------------------------------------

double GetPushTime(const int push_amt)
{
    clock_t duration = 0;

    for (size_t i = 0; i < TEST_AMT; i++)
    {
        struct Stack* st = stack_ctr(MIN_CAPACITY);

        clock_t start = clock();

        for (size_t j = 0; j < push_amt; j++)
            push(st, PUSHING_DATA);

        clock_t end   = clock();

        duration += end - start;

        stack_dtr(st);
    }

    return ((double) duration) / (CLOCKS_PER_SEC * TEST_AMT);
}

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

#if LIST_STACK

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

#endif

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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

#endif

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

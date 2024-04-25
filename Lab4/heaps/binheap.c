#include <assert.h>
#include <stdio.h>

#include "binheap.h"

static void SiftUp(int* heap_array, size_t index, size_t n);
static void SiftDown(int* heap_array, size_t index, size_t size);

static inline void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ---------------------------------------------------------------------

static void SiftUp(int* heap_array, size_t index, size_t n)
{
    assert(heap_array);

    while (index != 0)
    {
        size_t parent = (index - 1) / 2;

        if (heap_array[parent] < heap_array[index])
        {
            Swap(&heap_array[parent], &heap_array[index]);
            index = parent;
        }
        else
            return;
    }
}

// ---------------------------------------------------------------------

static void SiftDown(int* heap_array, size_t index, size_t size)
{
    assert(heap_array);

    int left_child = 2 * index + 1;

    while (left_child < size)
    {
        int max_child   = left_child;
        int right_child = left_child + 1;

        if (right_child < size && heap_array[right_child] > heap_array[max_child])
            max_child = right_child;

        if (heap_array[index] >= heap_array[max_child])
            break;

        Swap(&heap_array[index], &heap_array[max_child]);
        index = max_child;

        left_child = 2 * index + 1;
    }
}

// ---------------------------------------------------------------------

void LinearHeapify(int* arr, size_t n)
{
    assert(arr);

    for (size_t i = n / 2; i + 1 > 0; i--)
    {
        SiftDown(arr, i, n);
    }
}

// ---------------------------------------------------------------------

void StdHeapify(int* arr, size_t n)
{
    assert(arr);

    for (size_t i = 1; i < n; i++)
    {
        SiftUp(arr, i, n);
    }
}


#include <assert.h>
#include <stdio.h>

#include "common.h"
#include "pyramid_sorts.h"

static void SiftUp(int* heap_array, size_t index, const size_t n, const int k);
static void SiftDown(int* heap_array, size_t index, const size_t size, const int k);
static void HeapExtractMax(int* heap_array, const size_t size, const int k);

static inline size_t GetParent(const size_t index, const int k)
{
    return (index - 1) / k;
}

static inline size_t GetChild(const size_t index, const int k)
{
    return index * k + 1;
}

// ---------------------------------------------------------------------

static void SiftUp(int* heap_array, size_t index, const size_t n, const int k)
{
    assert(heap_array);

    while (index != 0)
    {
        size_t parent = GetParent(index, k);

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

static void SiftDown(int* heap_array, size_t index, const size_t size, const int k)
{
    assert(heap_array);

    int max_child = GetChild(index, k);

    while (max_child < size)
    {
        size_t child = 0;
        for (size_t i = 2; i <= k; i++)                            // index with maximum value
        {
            child = GetChild(index, k);
            if (child < size && heap_array[child] > heap_array[max_child])
                max_child = child;
        }

        if (heap_array[index] >= heap_array[max_child])
            break;

        Swap(&heap_array[index], &heap_array[max_child]);
        index = max_child;

        max_child  = GetChild(index, k);
    }
}

// ---------------------------------------------------------------------

static void HeapExtractMax(int* heap_array, const size_t size, const int k)
{
    assert(heap_array);

    Swap(&heap_array[0], &heap_array[size - 1]);

    SiftDown(heap_array, 0, size - 1, k);
}

// ---------------------------------------------------------------------

void Pyramid_sort(int* arr, const size_t n, const int k)
{
    assert(arr);

    for (size_t i = n / k; i >= 0; i--)
    {
        SiftDown(arr, i, n, k);
    }

    for (size_t i = n; i > 0; i--)
    {
        HeapExtractMax(arr, i, k);
    }
}

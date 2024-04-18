#include <assert.h>
#include <stdio.h>

#include "common.h"
#include "binheap.h"

static void SiftUp(int* heap_array, size_t index, size_t n);
static void SiftDown(int* heap_array, size_t index, size_t size);

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

void LinearHeapify(int* arr, size_t n)
{
    assert(arr);

    for (int i = n / 2; i >= 0; i--)
    {
		SiftDown(arr, i, n);
    }
}

// ---------------------------------------------------------------------

void StdHeapify(int* arr, size_t n)
{
    assert(arr);

    for (int i = 1; i < n; i++)
    {
        SiftUp(arr, i, n);
    }
}


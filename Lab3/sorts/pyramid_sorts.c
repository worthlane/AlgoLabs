#include <assert.h>
#include <stdio.h>

#include "common.h"
#include "pyramid_sorts.h"

static void SiftUp(int* heap_array, size_t index, const size_t n, const int k);
static void SiftDown(int* heap_array, size_t index, const size_t size, const int k);
static void HeapExtractMax(int* heap_array, const size_t size, const int k);

// ---------------------------------------------------------------------

static void SiftUp(int* heap_array, size_t index, const size_t n, const int k)
{
	assert(heap_array);

	while (index != 0)
	{
		size_t parent = (index - 1) / k;

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

	while (k * index + 1 < size)
	{
		int max_child = index * k + 1;


        for (size_t i = 2; i <= k; i++)                            // index with maximum value
        {
            if ((index * k + i) < size && heap_array[index * k + i] > heap_array[max_child])
                max_child = index * k + i;
        }

		if (heap_array[index] >= heap_array[max_child])
			break;

		Swap(&heap_array[index], &heap_array[max_child]);
		index = max_child;
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

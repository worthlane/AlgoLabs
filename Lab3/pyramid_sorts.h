#ifndef __PYRAMID_H
#define __PYRAMID_H

#include <assert.h>
#include <stdio.h>

#include "common.h"

// ---------------------------------------------------------------------

void SiftUp(int* heap_array, size_t index, size_t n, const int k)
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

void SiftDown(int* heap_array, size_t index, size_t size, const int k)
{
	assert(heap_array);

	while (k * index + 1 < size)
	{
		int max_child = index * k + 1;


        for (int i = 2; i <= k; i++)                            // index with maximum value
        {
            if ((index * k + i) < size)
            {
                if (heap_array[index * k + i] > heap_array[max_child])
                    max_child = index * k + i;
            }
        }

		if (heap_array[index] >= heap_array[max_child])
			break;

		Swap(&heap_array[index], &heap_array[max_child]);
		index = max_child;
	}
}

// ---------------------------------------------------------------------

void HeapExtractMax(int* heap_array, size_t size, const int k)
{
	assert(heap_array);

	Swap(&heap_array[0], &heap_array[size - 1]);

	SiftDown(heap_array, 0, size - 1, k);
}

// ---------------------------------------------------------------------

void Pyramid_sort(int* arr, size_t n, const int k)
{
    assert(arr);

    for (int i = 1; i < n; i++)
    {
        SiftUp(arr, i, i, k);
    }

    for (int i = n; i > 0; i--)
    {
        HeapExtractMax(arr, i, k);
    }
}

#endif

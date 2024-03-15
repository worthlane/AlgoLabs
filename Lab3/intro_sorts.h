#ifndef __INTRO_H
#define __INTRO_H

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common.h"

#include "quadratic_sorts.h"
#include "pyramid_sorts.h"


static const size_t SHELL_BLOCK = 100;           // experimental value from 6th point

static const int    OPTIMAL_COEF = 1;            // experimental value

// ---------------------------------------------------------------------

int Partition(int* array, int l, int r)
{
	int piv_idx = l + (r - l) / 2;
	int pivot   = array[piv_idx];                   // Central pivot strategy
	int i = l;
	int j = r;

	while (i <= j)
	{
		while (array[i] < pivot) { i++; }
		while (array[j] > pivot) { j--; }
		if (i >= j)
			break;

		Swap(&array[i++], &array[j--]);
	}

	return j;
}

//-------------------------------------------------------------------------------------------

void IntroQuickSort(int* array, const size_t left, const size_t right, const size_t heap_size)
{
	assert(array);

    if (right - left <= SHELL_BLOCK)
        Shell_sort(array + left, right - left);

    if (right - left <= heap_size)
        Pyramid_sort(array + left, right - left, 2);            // heapsort with multiplicity 2 is the fastest

	if (left < right)
	{
		int mid = Partition(array, left, right);

		IntroQuickSort(array, left, mid, heap_size);
		IntroQuickSort(array, mid + 1, right, heap_size);
	}
}

//-------------------------------------------------------------------------------------------

void TestCoefIntro_sort(int* arr, size_t n, const int C)
{
    if (n == 0)
        return;

    int start_heap = C * log((double) n);

    IntroQuickSort(arr, 0, n - 1, start_heap);                    // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void OptimalIntro_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    int start_heap = OPTIMAL_COEF * log((double) n);

    IntroQuickSort(arr, 0, n - 1, start_heap);                    // n-1 because of last element index in array
}



#endif

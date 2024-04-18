#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common.h"

#include "quadratic_sorts.h"
#include "pyramid_sorts.h"

#include "intro_sorts.h"

static int Partition(int* array, const int l, const int r);
static void IntroQuickSort(int* array, const size_t left, const size_t right, const size_t depth);


// ---------------------------------------------------------------------

static int Partition(int* array, const int l, const int r)
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

static void IntroQuickSort(int* array, const size_t left, const size_t right, const size_t depth)
{
	assert(array);

	if (right <= left)		return;

    size_t size = right - left;

    if (size <= SHELL_BLOCK)
        Shell_sort(array + left, size);

    if (depth == 0)
        Pyramid_sort(array + left, size, OPTIMAL_HEAP_K);            // heapsort with multiplicity 2 is the fastest

	int mid = Partition(array, left, right);

	IntroQuickSort(array, left, mid, depth - 1);
	IntroQuickSort(array, mid + 1, right, depth - 1);
}

//-------------------------------------------------------------------------------------------

void TestCoefIntro_sort(int* arr, const size_t n, const int C)
{
    if (n == 0)
        return;

    int max_depth = C * log2((double) n);

    IntroQuickSort(arr, 0, n - 1, max_depth);                    // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void OptimalIntro_sort(int* arr, const size_t n)
{
    if (n == 0)
        return;

    int max_depth = OPTIMAL_COEF * log2((double) n);

    IntroQuickSort(arr, 0, n - 1, max_depth);                    // n-1 because of last element index in array
}

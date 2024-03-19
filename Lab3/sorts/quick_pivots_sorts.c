#include <assert.h>
#include <stdlib.h>

#include "quick_pivots_sorts.h"

#include "common.h"

static int PivotsPartition(int* array, int l, int r, int take_pivot(int*, int, int));

static void PivotsQSort(int* array, const size_t left, const size_t right, int take_pivot(int*, int, int));

static int CentralPivot(int* array, int l, int r);
static int MedianThreePivot(int* array, int l, int r);
static int RandPivot(int* array, int l, int r);
static int RandMedianPivot(int* array, int l, int r);

static int Median(int* array, int a, int b, int c);

// USING HOARE PARTITION AS DEFAULT (BECAUSE IT IS FASTEST IN 4th POINT)

static int Median(int* array, int a, int b, int c)
{
    assert(array);

    int A = array[a];
    int B = array[b];
    int C = array[c];

    if ((A >= B && A <= C) || (A >= C && A <= B))
        return a;
    else if ((B >= A && B <= C) || (B >= C && B <= A))
        return b;
    else
        return c;
}

// ---------------------------------------------------------------------

static int PivotsPartition(int* array, int l, int r, int take_pivot(int*, int, int))
{
	int pivot   = take_pivot(array, l, r);
	int i = l;
	int j = r;

	while (i <= j)
	{
		while (array[i] < pivot) { i++; }
		while (array[j] > pivot) { j--; }
		if (i >= j)
			return j;

		Swap(&array[i++], &array[j--]);
	}

	return j;
}

//-------------------------------------------------------------------------------------------

static void PivotsQSort(int* array, const size_t left, const size_t right, int take_pivot(int*, int, int))
{
	assert(array);

	if (left < right)
	{
		if (right - left == 1)
		{
			if (array[right] < array[left])
				Swap(&array[right], &array[left]);
		}
		else
		{
			int mid = PivotsPartition(array, left, right, take_pivot);

			PivotsQSort(array, left, mid, take_pivot);
			PivotsQSort(array, mid + 1, right, take_pivot);
		}
	}
}

//-------------------------------------------------------------------------------------------

static int CentralPivot(int* array, int l, int r)
{
    assert(array);

    int piv_idx = l + (r - l) / 2;
	return array[piv_idx];
}

//-------------------------------------------------------------------------------------------

static int MedianThreePivot(int* array, int l, int r)
{
    assert(array);

    int mid = l + (r - l) / 2;

    int piv_idx = Median(array, l, mid, r);

	return array[piv_idx];
}

//-------------------------------------------------------------------------------------------

static int RandPivot(int* array, int l, int r)
{
    assert(array);

    int piv_idx = (rand() % (r - l)) + l;

	return array[piv_idx];
}

//-------------------------------------------------------------------------------------------

static int RandMedianPivot(int* array, int l, int r)
{
    assert(array);

    int elem1 = (rand() % (r - l)) + l;
    int elem2 = (rand() % (r - l)) + l;
    int elem3 = (rand() % (r - l)) + l;

    int piv_idx = Median(array, elem1, elem2, elem3);

	return array[piv_idx];
}

//-------------------------------------------------------------------------------------------

void CentralPivot_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    PivotsQSort(arr, 0, n - 1, CentralPivot);                       // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void MedianThreePivot_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    PivotsQSort(arr, 0, n - 1, MedianThreePivot);                   // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void RandPivot_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    PivotsQSort(arr, 0, n - 1, RandPivot);                          // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void RandMedianPivot_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    PivotsQSort(arr, 0, n - 1, RandMedianPivot);                    // n-1 because of last element index in array
}


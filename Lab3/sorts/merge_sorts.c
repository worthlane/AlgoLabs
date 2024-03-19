#include <stdlib.h>
#include <assert.h>

#include "merge_sorts.h"

static int 	Min(int a, int b);
static void Merge(int* array, const int left, const int mid, const int right);
static void RecursiveMergeSort(int* array, const int left, const int right);

static int Min(int a, int b)
{
    return (a < b) ? a : b;
}

// ---------------------------------------------------------------------

static void Merge(int* array, const int left, const int mid, const int right)
{
	assert(array);

	int ptr1 = 0;
	int ptr2 = 0;

	int* ans = (int*) calloc(right - left, sizeof(int));

	while ((left + ptr1 < mid) && (mid + ptr2 < right))
			// Repeat while left array and right array still have numbers
	{
		if (array[left + ptr1] < array[mid + ptr2])
		{
			ans[ptr1 + ptr2] = array[left + ptr1];
			ptr1++;
		}
		else
		{
			ans[ptr1 + ptr2] = array[mid + ptr2];
			ptr2++;
		}
	}

	while (left + ptr1 < mid)                       // Save last part of left array
	{
		ans[ptr1 + ptr2] = array[left + ptr1];
		ptr1++;
	}

	while (mid + ptr2 < right)                        // Save last part of right array
	{
		ans[ptr1 + ptr2] = array[mid + ptr2];
		ptr2++;
	}

	assert(ptr1 + ptr2 <= right - left);

	for (int i = 0; i < ptr1 + ptr2; i++)           // Copy "ans" array to the main array
		array[left + i] = ans[i];

	free(ans);
}

// ---------------------------------------------------------------------

static void RecursiveMergeSort(int* array, const int left, const int right)
{
	assert(array);

	if (right - left <= 1)      { return; }

	int mid = (left + right) / 2;
	RecursiveMergeSort(array, left, mid);
	RecursiveMergeSort(array, mid, right);
	Merge(array, left, mid, right);
}

// ---------------------------------------------------------------------

void IterativeMerge_sort(int* array, size_t n)
{
    if (n == 0)
        return;

	for (int i = 1; i < n; i *= 2)
	{
		for (int j = 0; j < n - i; j += 2 * i)
		{
			int r = Min(j + 2 * i, n);
			int l = j;
			int mid = j + i;

			Merge(array, l, mid, r);
		}
	}


}

// ---------------------------------------------------------------------

void RecursiveMerge_sort(int* arr, size_t n)
{
    RecursiveMergeSort(arr, 0, n);
}

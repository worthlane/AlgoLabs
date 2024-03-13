#ifndef __QUICK_PART_H
#define __QUICK_PART_H

#include <stdio.h>
#include <assert.h>

#include "common.h"

// ---------------------------------------------------------------------

void HoarePartition(int* array, int l, int r, int* mid1, int* mid2)
// We return values through two parameters to standardize the Partition function (due to fat partitioning)
{
	int piv_idx = l + (r - l) / 2;
	int pivot   = array[piv_idx];
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

	*mid1 = j;
    *mid2 = j + 1;
}

// ---------------------------------------------------------------------

void FatPartition(int* array, int l, int r, int* eq_from, int* eq_to)
{
	int piv_idx = l + (r - l) / 2;
	int pivot   = array[piv_idx];

    int mid = l;

    while (mid <= r)
    {
        if (array[mid] < pivot)
            Swap(&array[l++], &array[mid++]);
        else if (array[mid] == pivot)
            mid++;
        else
            Swap(&array[mid], &array[r--]);
    }

    *eq_from    = l;
    *eq_to      = r;
}

// ---------------------------------------------------------------------

void LomutoPartition(int* array, int l, int r, int* mid1, int* mid2)
// We return values through two parameters to standardize the Partition function (due to fat partitioning)
{
	int piv_idx = l + (r - l) / 2;
	int pivot   = array[piv_idx];

    Swap(&array[r], &array[piv_idx]);

	int i = l;

    for (int j = l; j <= r; j++)
    {
        if (array[j] < pivot)
            Swap(&array[i++], &array[j]);
    }

    Swap(&array[i], &array[r]);

    *mid1 = i;
    *mid2 = i + 1;
}


//-------------------------------------------------------------------------------------------

void OneBranchQSort(int* array, size_t left, size_t right,
                    void partition(int* array, int l, int r, int* eq_from, int* eq_to))
{
	assert(array);

    while (left < right)
    {
        int eq_from = 0;
        int eq_to   = 0;

        partition(array, left, right, &eq_from, &eq_to);

        OneBranchQSort(array, left, eq_from, partition);
        left = eq_to;
    }
}

//-------------------------------------------------------------------------------------------

void QSort(int* array, const size_t left, const size_t right,
           void partition(int* array, int l, int r, int* eq_from, int* eq_to))
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
			int eq_from = 0;
            int eq_to   = 0;

			partition(array, left, right, &eq_from, &eq_to);

			QSort(array, left, eq_from, partition);
			QSort(array, eq_to, right, partition);
		}
	}
}

//-------------------------------------------------------------------------------------------

void HoareQuick_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    QSort(arr, 0, n - 1, HoarePartition);                   // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void LomutoQuick_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    QSort(arr, 0, n - 1, LomutoPartition);                 // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void FatQuick_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    QSort(arr, 0, n - 1, FatPartition);                    // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void OneBranchHoareQuick_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    OneBranchQSort(arr, 0, n - 1, HoarePartition);                   // n-1 because of last element index in array
}

//-------------------------------------------------------------------------------------------

void OneBranchLomutoQuick_sort(int* arr, size_t n)
{
    if (n == 0)
        return;

    OneBranchQSort(arr, 0, n - 1, LomutoPartition);                 // n-1 because of last element index in array
}


#endif

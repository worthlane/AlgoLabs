#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

static inline void GetArray(int* array, const int size);
static inline void PrintArray(int* array, const int size);

void QSort(int* array, const size_t left, const size_t right);
int Partition(int* array, int l, int r);

void Swap(int* num1, int* num2);

// =====================================================================

int main()
{
	size_t N = 0;
	scanf("%d", &N);

	int* array = (int*) calloc(N, sizeof(int));

	GetArray(array, N);

	QSort(array, 0, N - 1);

	PrintArray(array, N);

	free(array);
}

// ---------------------------------------------------------------------

static inline void GetArray(int* array, const int size)
{
	assert(array);

	for (int i = 0; i < size; i++)
	{
		int number = 0;
		scanf("%d", &number);

		array[i] = number;
	}
}

// ---------------------------------------------------------------------

static inline void PrintArray(int* array, const int size)
{
	assert(array);

	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
}

// ---------------------------------------------------------------------

int Partition(int* array, int l, int r)
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
			return j;

		Swap(&array[i++], &array[j--]);
	}

	return j;
}

// ---------------------------------------------------------------------

void Swap(int* num1, int* num2)
{
	assert(num1);
	assert(num2);

	int temp = 0;

	temp  = *num1;
	*num1 = *num2;
	*num2 = temp;
}

//-------------------------------------------------------------------------------------------

void QSort(int* array, const size_t left, const size_t right)
{
	assert(array);
	assert(left <= right);

	if (left < right)
	{
		if (right - left == 1)
		{
			if (array[right] < array[left])
				Swap(&array[right], &array[left]);
		}
		else
		{
			size_t mid = Partition(array, left, right);

			QSort(array, left, mid);
			QSort(array, mid + 1, right);
		}
	}
}

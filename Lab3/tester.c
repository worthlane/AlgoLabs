#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "testing.h"

#include "quadratic_sorts.h"
#include "quick_part_sorts.h"
#include "quick_pivots_sorts.h"


int Comparator(const void* a, const void* b) {
    return (*(unsigned int*) a - *(unsigned int*) b);
}

void StdQuick_sort(int* arr, size_t n);

int main(const int argc, const char* argv[])
{
    srand(clock());

    double* times = TestSort(1, 150, 1, "very_small_tests/",
                            "6_point_results/Shell_sort.txt", Shell_sort);

    free(times);

    /*int array[10] = {1, 5, 7, 2, 9, 20, 7, 8, 9, 11};

    //int array[0] = {};

    RandPivot_sort(array, 10);

    for (size_t i = 0; i < 10; i++)
        printf("%d ", array[i]);*/

    return 0;
}

void StdQuick_sort(int* arr, size_t n)
{
    qsort(arr, n, sizeof(int), Comparator);
}

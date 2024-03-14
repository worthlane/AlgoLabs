#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "testing.h"

#include "quadratic_sorts.h"
#include "quick_part_sorts.h"
#include "quick_pivots_sorts.h"
#include "MLSD_sorts.h"
#include "merge_sorts.h"
#include "pyramid_sorts.h"


int Comparator(const void* a, const void* b) {
    return (*(unsigned int*) a - *(unsigned int*) b);
}

void StdQuick_sort(int* arr, size_t n);

int main(const int argc, const char* argv[])
{
    srand(clock());

    double* times = TestPyramidSort(0, 1000000, 10000, "big_tests/",
                            "2_point_results/10_Pyramid_sort.txt", Pyramid_sort, 10);

    free(times);

    //int array[10] = {2147483639, 2047483640, 2147483647, 1947483638, 47483641, 1547483644, 47483643, 47483642, 483645, 3646};

    /*int array[10] = {4, 1, 7, 9, 4, 10, 25, 18, 3, 11};

    //int array[0] = {};

    Pyramid_sort(array, 10);

    for (size_t i = 0; i < 10; i++)
        printf("%d ", array[i]);

    return 0;*/
}

void StdQuick_sort(int* arr, size_t n)
{
    qsort(arr, n, sizeof(int), Comparator);
}

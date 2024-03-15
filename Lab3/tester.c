#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "testing.h"

#include "quadratic_sorts.h"
#include "quick_part_sorts.h"
#include "quick_pivots_sorts.h"
#include "MLSD_sorts.h"
#include "merge_sorts.h"
#include "pyramid_sorts.h"
#include "intro_sorts.h"

int Comparator(const void* a, const void* b) {
    return (*(unsigned int*) a - *(unsigned int*) b);
}

void StdQuick_sort(int* arr, size_t n);

int main(const int argc, const char* argv[])
{
    srand(clock());

    /*double* times = TestIntroSortCoeff(1000000, "big_tests/",
                                       "7_point_results/OptimalIntroCoef.txt", TestCoefIntro_sort, 0, (int) log(1000000));

    free(times);*/

    double* times = TestSort(0, 1000000, 10000, "big_tests/",
                            "9_point_results/StdQuick_sort.txt", StdQuick_sort);

    free(times);

    return 0;
}

void StdQuick_sort(int* arr, size_t n)
{
    qsort(arr, n, sizeof(int), Comparator);
}

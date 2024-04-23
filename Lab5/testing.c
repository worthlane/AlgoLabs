#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "testing.h"
#include "heaps/binheap.h"


static const size_t MAX_PATH_LEN = 200;

static const size_t STD_TESTS_FROM = 100000;
static const size_t STD_TESTS_TO   = 1000000;
static const size_t STD_TESTS_STEP = 100000;
static const char*  STD_TESTS_PATH = "tests/std_tests/";

void GetFirstPointData();

// ==========================================================================

int main(const int argc, const char* argv[])
{

    GetFirstPointData();

    /*int array[] = {5, 1, 7, 10, 2, 3, 123, 43, 76, 345, 76576, 2, 464, 345, 687};

    int size = 14;

    StdHeapify(array, size);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    printf("\n");

    LinearHeapify(array, size);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);*/

    return 0;
}

// -----------------------------------------------------------------

void GetFirstPointData()
{
    double* times = NULL;

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                     "results/1_point/LinearHeapify.txt",
                     LinearHeapify);

    free(times);

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                     "results/1_point/StdHeapify.txt",
                     StdHeapify);

    free(times);
}

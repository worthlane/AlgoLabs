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
}

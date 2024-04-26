#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#define SHOW_PROGRESS

#include "testing.h"
#include "heaps/binheap.h"

static const size_t FILE_REPEAT     = 5;
static const size_t MAX_FILE_NAME   = 64;

static const size_t MAX_PATH_LEN = 200;

static const size_t STD_TESTS_FROM = 100000;
static const size_t STD_TESTS_TO   = 1000000;
static const size_t STD_TESTS_STEP = 100000;
static const char*  STD_TESTS_PATH = "tests/std_tests/";

static const char*  LINEAR_HEAP_PATH = "results/1_point/LinearHeapify.txt";
static const char*  STD_HEAP_PATH    = "results/1_point/StdHeapify.txt";

static double* TestHeapify(const int from, const int to, const int step,
                 const char* src_path, const char* dest_path, void heapify(int*, size_t));

static bool ValidateArray(int* arr, size_t array_size);

static int* GetArray(const char* input_file);

// -------------------------------------------------------------------------

static inline int GetLeftSon(int* arr, size_t size, size_t parent)
{
    size_t index = 2 * parent + 1;

    if (index >= size)
        return INT_MIN;
    else
        return arr[index];
}

// -------------------------------------------------------------------------

static inline int GetRightSon(int* arr, size_t size, size_t parent)
{
    size_t index = 2 * parent + 2;

    if (index >= size)
        return INT_MIN;
    else
        return arr[index];
}

// -----------------------------------------------------------------

void GetFirstPointData()
{
    double* times = NULL;

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                        LINEAR_HEAP_PATH, LinearHeapify);

    assert(times);

    free(times);

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                     STD_HEAP_PATH, StdHeapify);

    assert(times);

    free(times);
}

// -------------------------------------------------------------------------

static int* GetArray(const char* input_file)
{
    assert(input_file);

    FILE* fp = fopen(input_file, "r");
    if (!fp)
        return NULL;

    size_t size = 0;
    fscanf(fp, "%zu", &size);

    int* array = (int*) calloc(size, sizeof(int));
    assert(array);

    for (size_t i = 0; i < size; i++)
        fscanf(fp, "%d", &array[i]);

    fclose(fp);

    return array;
}

// -------------------------------------------------------------------------

static bool ValidateArray(int* arr, size_t array_size)
{
    assert(arr);

    for (size_t i = 0; i < array_size; i++)
    {
        int left_kid  = GetLeftSon(arr, array_size, i);
        int right_kid = GetRightSon(arr, array_size, i);

        if (left_kid > arr[i] || right_kid > arr[i])
            return false;
    }

    return true;
}

// -------------------------------------------------------------------------

static double* TestHeapify(const int from, const int to, const int step,
                 const char* src_path, const char* dest_path, void heapify(int*, size_t))
{
    assert(src_path);
    assert(dest_path);
    assert(heapify);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
        return NULL;

    size_t test_amt = (to - from + 1) / step;

    double* times = (double*) calloc(test_amt, sizeof(double));
    size_t  test_index = 0;

    assert(times);

    for (size_t size = from; size <= to; size += step)
    {
        #ifdef SHOW_PROGRESS
            printf("[%zu]\n", size);
        #endif

        clock_t duration = 0;

        for (size_t i = 1; i <= FILE_REPEAT; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, size, i);      // creating array file name

            int* arr = GetArray(input);
            assert(arr);

            clock_t start = clock();
            heapify(arr, size);
            clock_t end   = clock();

            assert(ValidateArray(arr, size));

            duration += end - start;
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * FILE_REPEAT);

        fprintf(fp, "%zu %.7lf\n", size, avg_time);

        times[test_index++] = avg_time;
    }

    fclose(fp);

    return times;
}

#ifndef __TESTING_H
#define __TESTING_H

#include <stdio.h>
#include <assert.h>
#include <time.h>

static const size_t K               = 5;
static const size_t MAX_FILE_NAME   = 64;

// -------------------------------------------------------------------------

int* GetArray(const char* input_file)
{
    assert(input_file);

    FILE* fp = fopen(input_file, "r");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", input_file);
        abort();
    }

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

void ValidateArray(const char* answer_file, int* arr, size_t array_size)
{
    assert(answer_file);
    assert(arr);

    FILE* fp = fopen(answer_file, "r");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", answer_file);
        abort();
    }

    for (size_t i = 0; i < array_size; i++)
    {
        int num = 0;
        assert(fscanf(fp, "%d", &num));

        if (num != arr[i])
        {
            printf("expected: %s\nprinted:\n", answer_file);

            for (size_t j = 0; j < array_size; j++)
            printf("%d ", arr[j]);

            abort();
        }
    }

    fclose(fp);
}

// -------------------------------------------------------------------------

double* TestSort(const int from, const int to, const int step,
                 const char* src_path, const char* dest_path, void sort(int*, size_t))
{
    assert(src_path);
    assert(dest_path);
    assert(sort);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", dest_path);
        abort();
    }

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

        for (size_t i = 1; i <= K; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, size, i);      // creating array file name

            int* arr = GetArray(input);

            clock_t start = clock();
            sort(arr, size);
            clock_t end   = clock();

            char ans[MAX_FILE_NAME] = {};
            snprintf(ans, MAX_FILE_NAME, "%s%zu_%zu.out", src_path, size, i);       // creating answer file name

            ValidateArray(ans, arr, size);

            duration += end - start;
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * K);

        fprintf(fp, "%zu %.7lf\n", size, avg_time);

        times[test_index++] = avg_time;
    }

    fclose(fp);

    return times;
}

// -------------------------------------------------------------------------

double* TestPyramidSort(const int from, const int to, const int step,
                 const char* src_path, const char* dest_path, void sort(int*, size_t, const int), int k)
{
    assert(src_path);
    assert(dest_path);
    assert(sort);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", dest_path);
        abort();
    }

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

        for (size_t i = 1; i <= K; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, size, i);      // creating array file name

            int* arr = GetArray(input);

            clock_t start = clock();
            sort(arr, size, k);
            clock_t end   = clock();

            char ans[MAX_FILE_NAME] = {};
            snprintf(ans, MAX_FILE_NAME, "%s%zu_%zu.out", src_path, size, i);       // creating answer file name

            ValidateArray(ans, arr, size);

            duration += end - start;
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * K);

        fprintf(fp, "%zu %.7lf\n", size, avg_time);

        times[test_index++] = avg_time;
    }

    fclose(fp);

    return times;
}

// -------------------------------------------------------------------------

double* TestIntroSortCoeff(const size_t test_size, const char* src_path,
                           const char* dest_path, void sort(int*, size_t, const int), int C_min, int C_max)
{
    assert(src_path);
    assert(dest_path);
    assert(sort);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", dest_path);
        abort();
    }

    size_t test_amt = C_max - C_min;

    double* times = (double*) calloc(test_amt, sizeof(double));
    size_t  test_index = 0;

    assert(times);

    for (size_t C = C_min; C <= C_max; C++)
    {
        #ifdef SHOW_PROGRESS
            printf("[%zu]\n", C);
        #endif

        clock_t duration = 0;

        for (size_t i = 1; i <= K; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, test_size, i);      // creating array file name

            int* arr = GetArray(input);

            clock_t start = clock();
            sort(arr, test_size, C);
            clock_t end   = clock();

            char ans[MAX_FILE_NAME] = {};
            snprintf(ans, MAX_FILE_NAME, "%s%zu_%zu.out", src_path, test_size, i);       // creating answer file name

            ValidateArray(ans, arr, test_size);

            duration += end - start;
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * K);

        fprintf(fp, "%zu %.7lf\n", C, avg_time);

        times[test_index++] = avg_time;
    }

    fclose(fp);

    return times;
}




#endif

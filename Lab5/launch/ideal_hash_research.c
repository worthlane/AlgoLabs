#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_INFO

#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "hashtable/ideal_map.h"

static const double OPENED_LF = 0.35;
static const double LISTED_LF = 0.7;

static const size_t TESTING_SIZE = 1000000;
static const size_t REQUESTS_AMT = 10000000;

static const size_t SHOWING_STEP = 500000;

static int* GenerateArray(const size_t size);

static inline void FillListedMap(listed_map_t* map, const int* array, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        ListedMapInsert(map, array[i]);
}

static inline void FillOpenedMap(opened_map_t* map, const int* array, const size_t size)
{
    for (size_t i = 0; i < size; i++)
        OpenedMapInsert(map, array[i]);
}

// --------------------------------------------------

static int* GenerateArray(const size_t size)
{
    int* array = calloc(size, sizeof(size));
    assert(array);

    listed_map_t* map = ListedMapCtor(size, LISTED_LF);

    size_t index = 0;
    int    num   = 0;

    while (index < size)
    {
        num = rand();

        if (!IsInListedMap(map, num))
        {
            array[index++] = num;
            ListedMapInsert(map, num);
        }
    }

    ListedMapDtor(map);

    return array;
}

// --------------------------------------------------

void CompareMaps()
{
    int* keys = GenerateArray(TESTING_SIZE);

    listed_map_t* listed_map = ListedMapCtor(TESTING_SIZE, LISTED_LF);
    opened_map_t* opened_map = OpenedMapCtor(TESTING_SIZE, DOUBLE, OPENED_LF);
    ideal_map_t*  ideal_map  = IdealMapCtor(keys, TESTING_SIZE);

    FillListedMap(listed_map, keys, TESTING_SIZE);
    FillOpenedMap(opened_map, keys, TESTING_SIZE);

    clock_t start = 0;
    clock_t end   = 0;
    clock_t dur   = 0;

    int num = 0;

    for (size_t i = 0; i < REQUESTS_AMT; i++)
    {
        num = rand();
        start = clock();
        IsInListedMap(listed_map, num);
        end   = clock();
        dur += end - start;

        #ifdef SHOW_INFO
        if (i % SHOWING_STEP == 0)
            printf("TESTING LISTED: %lu/%lu\n", i, REQUESTS_AMT);
        #endif
    }

    double listed_time = ((double) dur) / (CLOCKS_PER_SEC);
    dur = 0;

    for (size_t i = 0; i < REQUESTS_AMT; i++)
    {
        num = rand();
        start = clock();
        IsInOpenedMap(opened_map, num);
        end   = clock();
        dur += end - start;

        #ifdef SHOW_INFO
        if (i % SHOWING_STEP == 0)
            printf("TESTING OPENED: %lu/%lu\n", i, REQUESTS_AMT);
        #endif
    }

    double opened_time = ((double) dur) / (CLOCKS_PER_SEC);
    dur = 0;

    for (size_t i = 0; i < REQUESTS_AMT; i++)
    {
        num = rand();
        start = clock();
        IsInIdealMap(ideal_map, num);
        end   = clock();
        dur += end - start;
        #ifdef SHOW_INFO
        if (i % SHOWING_STEP == 0)
            printf("TESTING IDEAL: %lu/%lu\n", i, REQUESTS_AMT);
        #endif
    }

    double ideal_time = ((double) dur) / (CLOCKS_PER_SEC);

    printf("LISTED MAP: %.7lf (s)\n"
           "OPENED MAP: %.7lf (s)\n"
           "IDEAL  MAP: %.7lf (s)\n", listed_time, opened_time, ideal_time);

    free(keys);
    ListedMapDtor(listed_map);
    OpenedMapDtor(opened_map);
    IdealMapDtor(ideal_map);

}

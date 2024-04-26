#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "testing.h"
#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "research_func.h"

static const char* LIST_MAP_PATH      = "results/load_factor/ListedMap.txt";
static const char* LIN_OPEN_MAP_PATH  = "results/load_factor/LinearOpenedMap.txt";
static const char* QUAD_OPEN_MAP_PATH = "results/load_factor/QuadraticOpenedMap.txt";
static const char* DBL_OPEN_MAP_PATH  = "results/load_factor/DoubleOpenedMap.txt";

static const size_t LOAD_FACTOR_TESTS = 1000000;
static const size_t LOAD_FACTOR_STEP  = 10000;
static const size_t TABLE_SIZE        = LOAD_FACTOR_TESTS;

static void ResearchListedLoadFactor(const char* path);
static void ResearchOpenedLoadFactor(const char* path, address_t address);

void ResearchLoadFactor();

// ==========================================================================

int main(const int argc, const char* argv[])
{
    srand(time(NULL));
    //printf("%lu\n", KnuthHash(442342000));

    /*opened_map_t* map = OpenedMapCtor(2, DOUBLE, 1);

    printf("1 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 50);
    printf("2 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 20);
    printf("3 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 30);
    printf("4 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 33);
    printf("5 {%d} %d\n", map->cap, map->size);


    OpenedMapInsert(map, 70);


    printf("6 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 51);
    printf("7 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 21);
    printf("8 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 31);
    printf("9 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 31);
    printf("10 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 71);*/

    /*printf("%d %d\n", IsInOpenedMap(map, 50), IsInOpenedMap(map, 22));

    OpenedMapErase(map, 22);

    printf("%d %d\n", IsInOpenedMap(map, 50), IsInOpenedMap(map, 22));*/

    //ResearchLoadFactor();

    ResearchHashFuncs();

    return 0;
}

// -----------------------------------------------------------------

void GetFirstPointData()
{
    /*double* times = NULL;

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                     "results/1_point/LinearHeapify.txt",
                     LinearHeapify);

    free(times);

    times = TestHeapify(STD_TESTS_FROM, STD_TESTS_TO, STD_TESTS_STEP, STD_TESTS_PATH,
                     "results/1_point/StdHeapify.txt",
                     StdHeapify);

    free(times);*/
}

// -----------------------------------------------------------------

void ResearchLoadFactor()
{
    //ResearchListedLoadFactor(LIST_MAP_PATH);
    ResearchOpenedLoadFactor(DBL_OPEN_MAP_PATH, DOUBLE);
    //ResearchOpenedLoadFactor(LIN_OPEN_MAP_PATH, LINEAR);
    //ResearchOpenedLoadFactor(QUAD_OPEN_MAP_PATH, QUADRATIC);
}

// -----------------------------------------------------------------

static void ResearchOpenedLoadFactor(const char* path, address_t address)
{
    FILE* fp = fopen(path, "w");
    assert(fp);

    opened_map_t* map = OpenedMapCtor(TABLE_SIZE, address, 100); // TODO

    size_t step = 0;

    clock_t duration = 0;

    for (size_t i = 0; i < LOAD_FACTOR_TESTS; i++)
    {
        int num = rand();

        printf("%lu %d\n", i, num);

        clock_t start = clock();
        OpenedMapInsert(map, num);
        clock_t end   = clock();

        duration += end - start;
        step++;

        if (step >= LOAD_FACTOR_STEP)
        {
            fprintf(fp, "%.7lf %.7lf\n", (double) map->size / (double) map->cap,
                                        ((double) duration) / (CLOCKS_PER_SEC * step));
            step = 0;
            duration = 0;   // TODO не обнулять dur, а сделать типо прямой с изгибами
        }
    }

    OpenedMapDtor(map);
    fclose(fp);
}

// -----------------------------------------------------------------

static void ResearchListedLoadFactor(const char* path)
{
    FILE* fp = fopen(path, "w");
    assert(fp);

    listed_map_t* map = ListedMapCtor(TABLE_SIZE, 0.6);

    size_t step = 0;
    clock_t duration = 0;

    for (size_t i = 0; i < LOAD_FACTOR_TESTS; i++)
    {
        int num = rand();

        clock_t start = clock();
        ListedMapInsert(map, num);
        clock_t end   = clock();

        duration += end - start;
        step++;

        if (step >= LOAD_FACTOR_STEP)
        {
            fprintf(fp, "%.7lf %.7lf\n", (double) map->size / (double) map->cap,
                                        ((double) duration) / (CLOCKS_PER_SEC * step));
            step = 0;
            duration = 0;
        }
    }

    ListedMapDtor(map);
    fclose(fp);
}

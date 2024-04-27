#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "load_factor_test.h"
#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "research_func.h"

static const char* LIST_MAP_PATH      = "results/load_factor/ListedMap.txt";
static const char* LIN_OPEN_MAP_PATH  = "results/load_factor/LinearOpenedMap.txt";
static const char* QUAD_OPEN_MAP_PATH = "results/load_factor/QuadraticOpenedMap.txt";
static const char* DBL_OPEN_MAP_PATH  = "results/load_factor/DoubleOpenedMap.txt";

static const size_t LOAD_FACTOR_TESTS = 1000000;

static const size_t LIN_OPENED_LF  = -1; // TODO
static const size_t QUAD_OPENED_LF = -1;
static const size_t DBL_OPENED_LF  = -1;
static const size_t LISTED_LF      = 0.7;

static const size_t MIN_TABLE_SIZE    = 1;

static double ResearchOpenedLoadFactor(const address_t address, const double load_factor);
static double ResearchListedLoadFactor(const double load_factor);

static void ResearchListedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step);
static void ResearchOpenedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step,
                                        const address_t address);

// -----------------------------------------------------------------

void LoadFactorsFirstPointData()
{
    static const double OPENED_MIN  = 0.1;
    static const double OPENED_MAX  = 1;
    static const double OPENED_STEP = 0.01;

    ResearchOpenedLoadFactors(LIN_OPEN_MAP_PATH, OPENED_MIN, OPENED_MAX, OPENED_STEP, LINEAR);
    ResearchOpenedLoadFactors(DBL_OPEN_MAP_PATH, OPENED_MIN, OPENED_MAX, OPENED_STEP, DOUBLE);
    ResearchOpenedLoadFactors(QUAD_OPEN_MAP_PATH, OPENED_MIN, OPENED_MAX, OPENED_STEP, QUADRATIC);

    static const double LISTED_MIN  = 0.1;
    static const double LISTED_MAX  = 25;
    static const double LISTED_STEP = 0.1;

    ResearchListedLoadFactors(LIST_MAP_PATH, LISTED_MIN, LISTED_MAX, LISTED_STEP);
}

// -----------------------------------------------------------------

static void ResearchOpenedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step,
                                        const address_t address)
{
    #ifdef SHOW_PROGRESS
        printf("FILE: \"%s\"\n", path);
    #endif

    FILE* fp = fopen(path, "w");
    assert(fp);

    double cur_lf = min_lf;
    double time   = 0;

    while (cur_lf < max_lf)
    {
        time = ResearchOpenedLoadFactor(address, cur_lf);

        fprintf(fp, "%.7lf %.7lf\n", cur_lf, time);

        cur_lf += step;

        #ifdef SHOW_PROGRESS
            printf("cur_lf: %lf\n", cur_lf);
        #endif
    }

    fclose(fp);
}

// -----------------------------------------------------------------

static void ResearchListedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step)
{
    #ifdef SHOW_PROGRESS
        printf("FILE: \"%s\"\n", path);
    #endif

    FILE* fp = fopen(path, "w");
    assert(fp);

    double cur_lf = min_lf;
    double time   = 0;

    while (cur_lf < max_lf)
    {
        time = ResearchListedLoadFactor(cur_lf);

        fprintf(fp, "%.7lf %.7lf\n", cur_lf, time);

        cur_lf += step;

        #ifdef SHOW_PROGRESS
            printf("cur_lf: %lf\n", cur_lf);
        #endif
    }

    fclose(fp);
}

// -----------------------------------------------------------------

static double ResearchOpenedLoadFactor(const address_t address, const double load_factor)
{
    opened_map_t* map = OpenedMapCtor(MIN_TABLE_SIZE, address, load_factor);

    clock_t duration = 0;

    for (size_t i = 0; i < LOAD_FACTOR_TESTS; i++)
    {
        int num = rand();

        clock_t start = clock();
        OpenedMapInsert(map, num);
        clock_t end   = clock();

        duration += end - start;
    }

    OpenedMapDtor(map);

    return ((double) duration) / (CLOCKS_PER_SEC);
}

// -----------------------------------------------------------------

static double ResearchListedLoadFactor(const double load_factor)
{
    listed_map_t* map = ListedMapCtor(MIN_TABLE_SIZE, load_factor);

    clock_t duration = 0;

    for (size_t i = 0; i < LOAD_FACTOR_TESTS; i++)
    {
        int num = rand();

        clock_t start = clock();
        ListedMapInsert(map, num);
        clock_t end   = clock();

        duration += end - start;
    }

    ListedMapDtor(map);

    return ((double) duration) / (CLOCKS_PER_SEC);
}

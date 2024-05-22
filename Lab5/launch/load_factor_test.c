#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "load_factor_test.h"
#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "research_func.h"

static const size_t MAX_FILE_NAME   = 64;

static const char* ADD = "add";
static const char* DEL = "del";
static const char* FIND = "find";

static const char* LIST_MAP_PATH      = "results/load_factor/ListedMap.txt";
static const char* LIN_OPEN_MAP_PATH  = "results/load_factor/LinearOpenedMap.txt";
static const char* QUAD_OPEN_MAP_PATH = "results/load_factor/QuadraticOpenedMap.txt";
static const char* DBL_OPEN_MAP_PATH  = "results/load_factor/DoubleOpenedMap.txt";

static const size_t LOAD_FACTOR_TESTS = 1000000;

static const double OPENED_LF = 0.35;
static const double LISTED_LF = 0.7;

static const size_t MIN_TABLE_SIZE = 16;

static const size_t REQUESTS_FROM = 10000;
static const size_t REQUESTS_TO   = 1000000;
static const size_t REQUESTS_STEP = 10000;

static const char* EQUAL_PROB_TESTS = "tests/equal_requests/";
static const char* NOT_EQUAL_PROB_TESTS = "tests/not_equal_requests/";

static const char* EQU_LIST_MAP_PATH      = "results/equ_requests/ListedMap.txt";
static const char* EQU_LIN_OPEN_MAP_PATH  = "results/equ_requests/LinearOpenedMap.txt";
static const char* EQU_QUAD_OPEN_MAP_PATH = "results/equ_requests/QuadraticOpenedMap.txt";
static const char* EQU_DBL_OPEN_MAP_PATH  = "results/equ_requests/DoubleOpenedMap.txt";

static const char* NOT_EQU_LIST_MAP_PATH      = "results/not_equ_requests/ListedMap.txt";
static const char* NOT_EQU_LIN_OPEN_MAP_PATH  = "results/not_equ_requests/LinearOpenedMap.txt";
static const char* NOT_EQU_QUAD_OPEN_MAP_PATH = "results/not_equ_requests/QuadraticOpenedMap.txt";
static const char* NOT_EQU_DBL_OPEN_MAP_PATH  = "results/not_equ_requests/DoubleOpenedMap.txt";

static const size_t TEST_REPEAT = 5;

static double ResearchOpenedLoadFactor(const address_t address, const double load_factor);
static double ResearchListedLoadFactor(const double load_factor);

static void ResearchListedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step);
static void ResearchOpenedLoadFactors(const char* path, const double min_lf, const double max_lf, const double step,
                                        const address_t address);

static clock_t DoListedMapRequests(const char* src);
static clock_t DoOpenedMapRequests(const char* src, const address_t address);

static void TestListedMap(const int from, const int to, const int step,
                   const char* src_path, const char* dest_path);

static void TestOpenedMap(const int from, const int to, const int step,
                   const char* src_path, const char* dest_path, const address_t address);

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

void LoadFactorsSecondPointData()
{
    TestListedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, EQUAL_PROB_TESTS, EQU_LIST_MAP_PATH);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, EQUAL_PROB_TESTS, EQU_LIN_OPEN_MAP_PATH, LINEAR);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, EQUAL_PROB_TESTS, EQU_QUAD_OPEN_MAP_PATH, QUADRATIC);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, EQUAL_PROB_TESTS, EQU_DBL_OPEN_MAP_PATH, DOUBLE);
}

// -----------------------------------------------------------------

void LoadFactorsThirdPointData()
{
    TestListedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, NOT_EQUAL_PROB_TESTS, NOT_EQU_LIST_MAP_PATH);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, NOT_EQUAL_PROB_TESTS, NOT_EQU_LIN_OPEN_MAP_PATH, LINEAR);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, NOT_EQUAL_PROB_TESTS, NOT_EQU_QUAD_OPEN_MAP_PATH, QUADRATIC);
    TestOpenedMap(REQUESTS_FROM, REQUESTS_TO, REQUESTS_STEP, NOT_EQUAL_PROB_TESTS, NOT_EQU_DBL_OPEN_MAP_PATH, DOUBLE);
}

// -------------------------------------------------------------------------

static void TestListedMap(const int from, const int to, const int step,
                   const char* src_path, const char* dest_path)
{
    assert(src_path);
    assert(dest_path);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", dest_path);
        return;
    }

    size_t test_amt = (to - from + 1) / step;

    size_t  test_index = 0;

    for (size_t size = from; size <= to; size += step)
    {
        #ifdef SHOW_PROGRESS
            printf("[%zu]\n", size);
        #endif

        clock_t duration = 0;

        for (size_t i = 1; i <= TEST_REPEAT; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, size, i);      // creating array file name

            duration += DoListedMapRequests(input);
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * TEST_REPEAT);

        fprintf(fp, "%zu %.7lf\n", size, avg_time);
    }

    fclose(fp);
}

// -------------------------------------------------------------------------

static void TestOpenedMap(const int from, const int to, const int step,
                   const char* src_path, const char* dest_path, const address_t address)
{
    assert(src_path);
    assert(dest_path);

    FILE* fp = fopen(dest_path, "w");
    if (!fp)
    {
        printf("CAN NOT OPEN \"%s\"\n", dest_path);
        return;
    }

    size_t test_amt = (to - from + 1) / step;

    size_t  test_index = 0;

    for (size_t size = from; size <= to; size += step)
    {
        #ifdef SHOW_PROGRESS
            printf("[%zu]\n", size);
        #endif

        clock_t duration = 0;

        for (size_t i = 1; i <= TEST_REPEAT; i++)
        {
            char input[MAX_FILE_NAME] = {};
            snprintf(input, MAX_FILE_NAME, "%s%zu_%zu.in", src_path, size, i);      // creating array file name

            duration += DoOpenedMapRequests(input, address);
        }

        double avg_time = ((double) duration) / (CLOCKS_PER_SEC * TEST_REPEAT);

        fprintf(fp, "%zu %.7lf\n", size, avg_time);
    }

    fclose(fp);
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

// --------------------------------------------------------------

static clock_t DoListedMapRequests(const char* src)
{
	FILE* fp = fopen(src, "r");
	assert(fp);

	listed_map_t* map = ListedMapCtor(MIN_TABLE_SIZE, LISTED_LF);

	size_t amt = 0;
	fscanf(fp, "%lu", &amt);

	char cmd[10] = "";
	int  num     = 0;

    clock_t start = 0;
    clock_t end   = 0;
    clock_t dur   = 0;

	while (amt--)
	{
		fscanf(fp, "%9s", cmd);
		fscanf(fp, "%d", &num);

		if (!strncmp(cmd, ADD, 10))
        {
            start = clock();
            ListedMapInsert(map, num);
            end = clock();
        }
        else if (!strncmp(cmd, DEL, 10))
        {
            start = clock();
            ListedMapErase(map, num);
            end = clock();
        }
        else if (!strncmp(cmd, FIND, 10))
        {
            start = clock();
            IsInListedMap(map, num);
            end = clock();
        }

        dur += end - start;
	}

    ListedMapDtor(map);

	fclose(fp);

    return dur;
}

// --------------------------------------------------------------

static clock_t DoOpenedMapRequests(const char* src, const address_t address)
{
	FILE* fp = fopen(src, "r");
	assert(fp);

	opened_map_t* map = OpenedMapCtor(MIN_TABLE_SIZE, address, OPENED_LF);

	size_t amt = 0;
	fscanf(fp, "%lu", &amt);

	char cmd[10] = "";
	int  num     = 0;

    clock_t start = 0;
    clock_t end   = 0;
    clock_t dur   = 0;

	while (amt--)
	{
		fscanf(fp, "%9s", cmd);
		fscanf(fp, "%d", &num);

		if (!strncmp(cmd, ADD, 10))
        {
            start = clock();
            OpenedMapInsert(map, num);
            end = clock();
        }
        else if (!strncmp(cmd, DEL, 10))
        {
            start = clock();
            OpenedMapErase(map, num);
            end = clock();
        }
        else if (!strncmp(cmd, FIND, 10))
        {
            start = clock();
            IsInOpenedMap(map, num);
            end = clock();
        }

        dur += end - start;
	}

    OpenedMapDtor(map);

	fclose(fp);

    return dur;
}

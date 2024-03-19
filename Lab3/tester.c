#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define SHOW_PROGRESS

#include "testing.h"

#include "sorts/quadratic_sorts.h"
#include "sorts/quick_part_sorts.h"
#include "sorts/quick_pivots_sorts.h"
#include "sorts/MLSD_sorts.h"
#include "sorts/merge_sorts.h"
#include "sorts/pyramid_sorts.h"
#include "sorts/intro_sorts.h"

static const size_t MAX_PATH_LEN = 200;

static const size_t VERY_SMALL_TESTS_FROM = 1;
static const size_t VERY_SMALL_TESTS_TO   = 150;
static const size_t VERY_SMALL_TESTS_STEP = 1;
static const char*  VERY_SMALL_TESTS_PATH = "tests/very_small_tests/";

static const size_t SMALL_TESTS_FROM = 0;
static const size_t SMALL_TESTS_TO   = 1000;
static const size_t SMALL_TESTS_STEP = 50;
static const char*  SMALL_TESTS_PATH = "tests/small_tests/";

static const size_t BIG_TESTS_FROM = 0;
static const size_t BIG_TESTS_TO   = 1000000;
static const size_t BIG_TESTS_STEP = 10000;
static const char*  BIG_TESTS_PATH = "tests/big_tests/";

static const size_t TESTS_MOST_DUBLICATES_FROM = 0;
static const size_t TESTS_MOST_DUBLICATES_TO   = 1000000;
static const size_t TESTS_MOST_DUBLICATES_STEP = 10000;
static const char*  TESTS_MOST_DUBLICATES_PATH = "tests/tests_most_dublicates/";

void GetFirstPointData();
void GetSecondPointData();
void GetThirdPointData();
void GetFourthPointData();
void GetFivthPointData();
void GetSixthPointData();
void GetSeventhPointData();
void GetEightsPointData();
void GetNinethPointData();

static void TestQuickPartitions(const int from, const int to, const int step,
                                const char* src_path, const char* out_folder);

// ==========================================================================

int main(const int argc, const char* argv[])
{
    srand(clock());

    /*double* times = TestIntroSortCoeff(1000000, "big_tests/",
                                       "7_point_results/OptimalIntroCoef.txt", TestCoefIntro_sort, 0, (int) log(1000000));

    free(times);*/

    /*double* times = TestSort(0, 1000000, 10000, "big_tests/",
                            "results/7_point_results/Introtest_sort.txt", OptimalIntro_sort);

    free(times);*/

    /*int array[20] = {342, 21, 3532, 435, 2342, 324, 1231, 453, 876, 234, 3242, 465, 12, 2, 664, 576, 898, 123123, 302, 4363};

    OneBranchHoareQuick_sort(array, 20);

    for(int i = 0; i < 20; i++)
    {
        printf("%d ", array[i]);
    }*/

    GetNinethPointData();

    return 0;
}

// -----------------------------------------------------------------

void GetFirstPointData()
{
    double* times = NULL;

    times = TestSort(SMALL_TESTS_FROM, SMALL_TESTS_TO, SMALL_TESTS_STEP, SMALL_TESTS_PATH,
                     "results/1_point_results/Bubble_sort.txt",
                     Bubble_sort);

    free(times);

    times = TestSort(SMALL_TESTS_FROM, SMALL_TESTS_TO, SMALL_TESTS_STEP, SMALL_TESTS_PATH,
                     "results/1_point_results/Insertion_sort.txt",
                     Insertion_sort);

    free(times);

    times = TestSort(SMALL_TESTS_FROM, SMALL_TESTS_TO, SMALL_TESTS_STEP, SMALL_TESTS_PATH,
                     "results/1_point_results/Selection_sort.txt",
                     Selection_sort);

    free(times);

    times = TestSort(SMALL_TESTS_FROM, SMALL_TESTS_TO, SMALL_TESTS_STEP, SMALL_TESTS_PATH,
                     "results/1_point_results/Shell_sort.txt",
                     Shell_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetSecondPointData()
{
    for (int k = 2; k < 11; k++)
    {
        char dest_path[MAX_PATH_LEN] = "";
        snprintf(dest_path, MAX_PATH_LEN, "results/2_point_results/%d_Pyramid_sort.txt", k);

        double* times = TestPyramidSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP,
                                        BIG_TESTS_PATH,
                                        dest_path,
                                        Pyramid_sort, k);
        free(times);
    }
}

// -----------------------------------------------------------------

void GetThirdPointData()
{
    double* times = NULL;

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/3_point_results/IterativeMerge_sort.txt",
                     IterativeMerge_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/3_point_results/RecursiveMerge_sort.txt",
                     RecursiveMerge_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetFourthPointData()
{
    TestQuickPartitions(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                        "results/4_point_results/big/");

    TestQuickPartitions(TESTS_MOST_DUBLICATES_FROM, TESTS_MOST_DUBLICATES_TO,
                        TESTS_MOST_DUBLICATES_STEP, TESTS_MOST_DUBLICATES_PATH,
                        "results/4_point_results/dublicates/");
}

// -----------------------------------------------------------------

static void TestQuickPartitions(const int from, const int to, const int step,
                                const char* src_path, const char* out_folder)
{
    assert(src_path);
    assert(out_folder);

    double* times = NULL;
    char dest_path[MAX_PATH_LEN] = "";

    snprintf(dest_path, MAX_PATH_LEN, "%sOneBranchHoareQuick_sort.txt", out_folder);

    times = TestSort(from, to, step, src_path,
                     dest_path,
                     OneBranchHoareQuick_sort);

    free(times);

    snprintf(dest_path, MAX_PATH_LEN, "%sOneBranchLomutoQuick_sort.txt", out_folder);

    times = TestSort(from, to, step, src_path,
                     dest_path,
                     OneBranchLomutoQuick_sort);

    free(times);

    snprintf(dest_path, MAX_PATH_LEN, "%sHoareQuick_sort.txt", out_folder);

    times = TestSort(from, to, step, src_path,
                     dest_path,
                     HoareQuick_sort);

    free(times);

    snprintf(dest_path, MAX_PATH_LEN, "%sLomutoQuick_sort.txt", out_folder);

    times = TestSort(from, to, step, src_path,
                     dest_path,
                     LomutoQuick_sort);

    free(times);

    snprintf(dest_path, MAX_PATH_LEN, "%sFatQuick_sort.txt", out_folder);

    times = TestSort(from, to, step, src_path,
                     dest_path,
                     FatQuick_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetFivthPointData()
{
    double* times = NULL;

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/5_point_results/CentralPivot_sort.txt",
                     CentralPivot_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/5_point_results/MedianThreePivot_sort.txt",
                     MedianThreePivot_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/5_point_results/RandMedianPivot_sort.txt",
                     RandMedianPivot_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/5_point_results/RandPivot_sort.txt",
                     RandPivot_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetSixthPointData()
{
    double* times = NULL;

    times = TestSort(VERY_SMALL_TESTS_FROM, VERY_SMALL_TESTS_TO,
                     VERY_SMALL_TESTS_STEP, VERY_SMALL_TESTS_PATH,
                     "results/6_point_results/Quick_sort.txt",
                     CentralPivot_sort);                            // The fastest qsort

    free(times);

    times = TestSort(VERY_SMALL_TESTS_FROM, VERY_SMALL_TESTS_TO,
                     VERY_SMALL_TESTS_STEP, VERY_SMALL_TESTS_PATH,
                     "results/6_point_results/Shell_sort.txt",
                     Shell_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetSeventhPointData()
{
    double* times = NULL;

    times = TestIntroSortCoeff(BIG_TESTS_TO, BIG_TESTS_PATH,
                               "results/7_point_results/OptimalIntroCoef.txt", TestCoefIntro_sort,
                               0, 50);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/7_point_results/Intro_sort.txt", OptimalIntro_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/7_point_results/Quick_sort.txt", HoareQuick_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetEightsPointData()
{
    double* times = NULL;

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/8_point_results/MSD_sort.txt",
                     MSD_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/8_point_results/LSD_sort.txt",
                     LSD_sort);

    free(times);
}

// -----------------------------------------------------------------

void GetNinethPointData()
{
    double* times = NULL;

    times = TestPyramidSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                            "results/9_point_results/Heap_sort.txt",
                            Pyramid_sort, OPTIMAL_HEAP_K);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/HoareCentralPivot_sort.txt",
                     CentralPivot_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/Intro_sort.txt",
                     OptimalIntro_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/OneBranchHoare_sort.txt",
                     OneBranchHoareQuick_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/StdQuick_sort.txt",
                     StdQuick_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/MSD_sort.txt",
                     MSD_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/LSD_sort.txt",
                     LSD_sort);

    free(times);

    times = TestSort(BIG_TESTS_FROM, BIG_TESTS_TO, BIG_TESTS_STEP, BIG_TESTS_PATH,
                     "results/9_point_results/IterativeMerge_sort.txt",
                     IterativeMerge_sort);

    free(times);
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "tests.h"

#include "constants.h"

static const char*  DEFAULT_OUT  = "data.txt";

double  GetPushTime(const int push_amt);
void    GetGraphData(double* graph_points);

// =====================================================================

int main(const int argc, const char* argv[])
{
    const char* output_file = DEFAULT_OUT;
    if (argc >= 2)
        output_file = argv[1];

    double graph_points[POINTS_AMT + 1] = {};            //  time(n) = graph_points[n / 1000]
                                                         //  we add 1 because of we include n = 0 and n = 10^6

    GetGraphData(graph_points);

    FILE* out = fopen(output_file, "w");
    if (!out)
    {
        fprintf(stderr, "CAN NOT OPEN \"%s\"\n", output_file);
        return 1;
    }

    for (int i = 0; i <= POINTS_AMT; i++)
        fprintf(out, "%zu %lf\n", i * POINTS_SHIFT, graph_points[i]);

    return 0;
}

// ---------------------------------------------------------------------

void GetGraphData(double* graph_points)
{
    for (int i = 0; i <= POINTS_AMT; i++)
    {
        printf("COUNTING %zu:\n", i * POINTS_SHIFT);

        double time = GetPushTime(i * POINTS_SHIFT);

        graph_points[i] = time;
    }
}

// ---------------------------------------------------------------------

double GetPushTime(const int push_amt)
{
    clock_t duration = 0;

    for (size_t i = 0; i < TEST_AMT; i++)
    {
        struct Stack* st = stack_ctr(MIN_CAPACITY);

        clock_t start = clock();

        for (size_t j = 0; j < push_amt; j++)
            push(st, PUSHING_DATA);

        clock_t end   = clock();

        duration += end - start;

        stack_dtr(st);
    }

    return ((double) duration) / (CLOCKS_PER_SEC * TEST_AMT);
}



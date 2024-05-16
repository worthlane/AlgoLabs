#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include "trees/avl.h"
#include "trees/treap.h"
#include "trees/splay.h"
#include "trees/bst.h"

#include "testing.h"

#define SHOW_PROGRESS

static const size_t REPEAT_TEST   = 5;
static const size_t MAX_FILE_NAME = 256;

static void OnePoint(FILE* ins_out, FILE* del_out, const char* src_path, const size_t size,
                        ctor_t ctor, dtor_t dtor, operation_t insert, operation_t remove);

static inline void TestOperation(FILE* fp, void* tree, clock_t* dur, operation_t operation)
{
    int    num = 0;
    size_t amt = 0;

    clock_t start = 0;
    clock_t end   = 0;

    fscanf(fp, "%d", &amt);

    while (amt--)
    {
        fscanf(fp, "%d", &num);

        start = clock();
        operation(tree, num);
        end   = clock();

        *dur += end - start;
    }
}

// -------------------------------------------------------------------------

bool TestTree(const int from, const int to, const int step,
             const char* src_path, const char* dest_path, const char* name,
             ctor_t ctor, dtor_t dtor, operation_t insert, operation_t remove)
{
    assert(src_path);
    assert(dest_path);

    char ins_data[MAX_FILE_NAME] = {};
    snprintf(ins_data, MAX_FILE_NAME, "%s%s_ins.txt", dest_path, name);
    FILE* ins_out = fopen(ins_data, "w");
    assert(ins_out);

    char del_data[MAX_FILE_NAME] = {};
    snprintf(del_data, MAX_FILE_NAME, "%s%s_del.txt", dest_path, name);
    FILE* del_out = fopen(del_data, "w");
    assert(del_out);

    for (size_t size = from; size <= to; size += step)
    {
        #ifdef SHOW_PROGRESS
            printf("[%zu]\n", size);
        #endif

        OnePoint(ins_out, del_out, src_path, size, ctor, dtor, insert, remove);
    }

    fclose(ins_out);
    fclose(del_out);

    return true;
}

// -------------------------------------------------------------------------

static void OnePoint(FILE* ins_out, FILE* del_out, const char* src_path, const size_t size,
                        ctor_t ctor, dtor_t dtor, operation_t insert, operation_t remove)
{
    clock_t ins_dur = 0;
    clock_t del_dur = 0;

    char ins_file[MAX_FILE_NAME] = {};
    char del_file[MAX_FILE_NAME] = {};

    for (size_t i = 1; i <= REPEAT_TEST; i++)
    {
        void* tree = ctor();

        snprintf(ins_file, MAX_FILE_NAME, "%s%zu_%zu_ins.in", src_path, size, i);
        FILE* ins_test = fopen(ins_file, "r");
        assert(ins_test);

        TestOperation(ins_test, tree, &ins_dur, insert);

        snprintf(del_file, MAX_FILE_NAME, "%s%zu_%zu_del.in", src_path, size, i);
        FILE* del_test = fopen(del_file, "r");
        assert(del_test);

        TestOperation(del_test, tree, &del_dur, remove);

        dtor(tree);

        fclose(ins_test);
        fclose(del_test);
    }

    double ins_avg_time = ((double) ins_dur) / (CLOCKS_PER_SEC * REPEAT_TEST);
    double del_avg_time = ((double) del_dur) / (CLOCKS_PER_SEC * REPEAT_TEST);

    fprintf(ins_out, "%zu %.7lf\n", size, ins_avg_time);
    fprintf(del_out, "%zu %.7lf\n", size / 2, del_avg_time);
}

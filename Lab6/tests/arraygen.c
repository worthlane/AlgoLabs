#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

static const int SORT_ON = 1;

int Comparator(const void* a, const void* b) {
    return (*(int*)a - *(int*) b);
}

int main(const int argc, const char* argv[])
{
    if (argc < 3)
    {
        printf("ARRAY LEN AND SORT FLAG (%d -> sort) REQUIRED IN COMMAND LINE\n", SORT_ON);
        return 1;
    }

    srand(42);

    size_t array_len  = atoi(argv[1]);
    int    sort_flag  = atoi(argv[2]);

    int* array = calloc(array_len, sizeof(int));
    assert(array);

    for (size_t i = 0; i < array_len; i++)
        array[i] = rand();

    if (sort_flag == SORT_ON)
        qsort(array, array_len, sizeof(int), Comparator);

    printf("%zu\n", array_len);

    for (size_t i = 0; i < array_len; i++)
        printf("%d\n", array[i]);

    free(array);
}


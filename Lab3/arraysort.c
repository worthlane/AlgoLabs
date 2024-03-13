#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int Comparator(const void* a, const void* b) {
    return (*(unsigned int*)a - *(unsigned int*) b);
}

int main(const int argc, const char* argv[])
{
    size_t array_len = 0;
    assert(scanf("%zu", &array_len));

    unsigned int* array = (unsigned int*) calloc(array_len, sizeof(unsigned int));

    for (size_t i = 0; i < array_len; i++)
        scanf("%i", &array[i]);

    qsort(array, array_len, sizeof(unsigned int), Comparator);

    for (size_t i = 0; i < array_len; i++)
        printf("%i ", array[i]);

    free(array);

    return 0;
}

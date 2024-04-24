#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(const int argc, const char* argv[])
{
    if (argc < 3)
    {
        perror("ARRAY LEN AND BORDERS LEN REQUIRED IN COMMAND LINE\n");
        return 1;
    }

    srand(42);

    size_t array_len   = atoi(argv[1]);
    int    border      = atoi(argv[2]);

    printf("%lu\n", array_len);

    for (size_t i = 0; i < array_len; i++)
    {
        float non_int_part = (float) rand() / RAND_MAX;
        int   int_part     = -border + (rand() % (2 * border));

        float num = (float) int_part + non_int_part;

        printf("%f\n", num);
    }

}


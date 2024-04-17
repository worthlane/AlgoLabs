#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(const int argc, const char* argv[])
{
    if (argc < 3)
    {
        perror("ARRAY LEN AND MAX NUMBER REQUIRED IN COMMAND LINE\n");
        return 1;
    }

    srand(42);

    size_t       array_len  = atoi(argv[1]);
    int          max_num    = atoi(argv[2]);

    if (max_num < 0)
        max_num = RAND_MAX;

    printf("%zu ", array_len);

    for (size_t i = 0; i < array_len; i++)
    {
        unsigned int rand_num = ((unsigned) rand()) % (max_num + 1);

        printf("%i ", rand_num);
    }

}


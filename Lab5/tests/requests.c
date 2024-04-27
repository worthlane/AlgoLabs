#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(const int argc, const char* argv[])
{
    if (argc < 3)
    {
        perror("GENERATION MODE REQIRED (1 for equal probabilities, else for 0.50/0.25/0.25)\n");
        return 1;
    }

    srand(42);

    size_t  array_len  = atoi(argv[1]);
    int     mode       = atoi(argv[2]);

    printf("%lu\n", array_len);

    if (mode == 1)
    {
        for (size_t i = 0; i < array_len; i++)
        {
            int opt = rand() % 3;
            int num = rand();

            if (opt == 0)
                printf("add %d\n", num);
            else if (opt == 1)
                printf("del %d\n", num);
            else
                printf("find %d\n", num);
        }
    }
    else
    {
        for (size_t i = 0; i < array_len; i++)
        {
            int opt = rand() % 4;
            int num = rand();

            if (opt == 0 || opt == 1)
                printf("add %d\n", num);
            else if (opt == 2)
                printf("del %d\n", num);
            else
                printf("find %d\n", num);
        }
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

static const char MIN_ASCII = 'a';
static const char MAX_ASCII = 'z';

int main(const int argc, const char* argv[])
{
    if (argc < 3)
    {
        perror("ARRAY LEN AND BORDERS REQUIRED IN COMMAND LINE\n");
        return 1;
    }

    srand(42);

    size_t array_len  = atoi(argv[1]);
    size_t min_word   = atoi(argv[2]);
    size_t max_word   = atoi(argv[3]);

    if (max_word < 0)
        max_word = RAND_MAX;

    if (min_word < 0)
        min_word = 0;

    printf("%lu\n", array_len);

    for (size_t i = 0; i < array_len; i++)
    {
        size_t rand_len = min_word + ((unsigned) rand()) % (max_word - min_word + 1);

        for (size_t j = 0; j < rand_len; j++)
        {
            char rand_letter = MIN_ASCII + ((unsigned) rand()) % (MAX_ASCII - MIN_ASCII + 1);

            printf("%c", rand_letter);
        }

        printf("\n");
    }

}


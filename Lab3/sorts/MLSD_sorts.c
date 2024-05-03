#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "MLSD_sorts.h"

static unsigned int GetByte(const unsigned int num, const int byte_num);
static void         RecursiveMSD(int* array, int* temp, const int l, const int r, const int byte);


static const size_t MAX_AMT = 256;   // max array size

// ------------------------------------------------------------------------------

static unsigned int GetByte(const unsigned int num, const int byte_num)
{
    unsigned int mask = 0xff;

    mask <<= (byte_num * 8);

    unsigned int val = (num & mask) >> (8 * byte_num);

    return val;
}

// ------------------------------------------------------------------------------

void LSD_sort(int* array, const size_t N)
{
    assert(array);

    int* temp = (int*) calloc(N, sizeof(int));
    assert(temp);

    for (size_t byte = 0; byte < 4; byte++)
    {
        unsigned int pref_cnt[MAX_AMT] = {};
        memset(pref_cnt, 0, sizeof(pref_cnt));

        for (size_t i = 0; i < N; i++)
            pref_cnt[GetByte(array[i], byte)]++;

        for (size_t i = 1; i < MAX_AMT; i++)
            pref_cnt[i] += pref_cnt[i - 1];

        for (size_t i = N - 1; i >= 0; i--)
            temp[--pref_cnt[GetByte(array[i], byte)]] = array[i];

        memcpy(array, temp, sizeof(int) * N);
    }
    free(temp);
}

// ------------------------------------------------------------------------------

static void RecursiveMSD(int* array, int* temp, const int l, const int r, const int byte)
{
    assert(array);
    assert(temp);

    size_t size = r - l;

    if (size <= 1 || byte < 0)
        return;

    unsigned int pref_cnt[MAX_AMT] = {};

    for (size_t i = l; i < r; i++)
        pref_cnt[GetByte(array[i], byte)]++;

    for (size_t i = 1; i < MAX_AMT; i++)
        pref_cnt[i] += pref_cnt[i - 1];

    for (size_t i = l; i < r; i++)
    {
        unsigned int byte_val = GetByte(array[i], byte);

        pref_cnt[byte_val]--;

        temp[pref_cnt[byte_val] + l] = array[i];
    }

    memcpy(array + l, temp + l, sizeof(int) * (size));

    for (size_t i = 0; i < MAX_AMT - 1; i++)
        RecursiveMSD(array, temp, l + pref_cnt[i], l + pref_cnt[i + 1], byte - 1);

    RecursiveMSD(array, temp, l + pref_cnt[MAX_AMT - 1], r, byte - 1);
}

// ------------------------------------------------------------------------------

void MSD_sort(int* array, const size_t N)
{
    assert(array);

    int* temp = (int*) calloc(N, sizeof(int));
    assert(temp);

    RecursiveMSD(array, temp, 0, N, 3);

    free(temp);
}

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "MLSD_sorts.h"

static unsigned int GetByte(unsigned int num, int byte_num);
static void 		RecursiveMSD(int* array, int* temp, int l, int r, int byte);


static const size_t MAX_AMT = 256;   // max array size

// ------------------------------------------------------------------------------

static unsigned int GetByte(unsigned int num, int byte_num)
{
	unsigned int mask = 0xff;

	mask <<= (byte_num * 8);

	unsigned int val = (num & mask) >> (8 * byte_num);

	return val;
}

// ------------------------------------------------------------------------------

void LSD_sort(int* array, size_t N)
{
	assert(array);

    int* temp = (int*) calloc(N, sizeof(int));
	assert(temp);

	for (int byte = 0; byte < 4; byte++)
	{
		unsigned int pref_cnt[MAX_AMT] = {};
		memset(pref_cnt, 0, sizeof(pref_cnt));

		for (int i = 0; i < N; i++)
			pref_cnt[GetByte(array[i], byte)]++;

		for (int i = 1; i < MAX_AMT; i++)
			pref_cnt[i] += pref_cnt[i - 1];

		for (int i = N - 1; i >= 0; i--)
			temp[--pref_cnt[GetByte(array[i], byte)]] = array[i];

		memcpy(array, temp, sizeof(int) * N);
	}
    free(temp);
}

// ------------------------------------------------------------------------------

static void RecursiveMSD(int* array, int* temp, int l, int r, int byte)
{
	assert(array);
	assert(temp);

	size_t size = r - l;

	if (size <= 1 || byte < 0)
		return;

	unsigned int pref_cnt[MAX_AMT] = {};

	for (int i = l; i < r; i++)
		pref_cnt[GetByte(array[i], byte)]++;

	for (int i = 1; i < MAX_AMT; i++)
		pref_cnt[i] += pref_cnt[i - 1];

	for (int i = l; i < r; i++)
	{
		unsigned int byte_val = GetByte(array[i], byte);

		pref_cnt[byte_val]--;

		temp[pref_cnt[byte_val] + l] = array[i];
	}

	memcpy(array + l, temp + l, sizeof(int) * (size));

	for (int i = 0; i < MAX_AMT - 1; i++)
		RecursiveMSD(array, temp, l + pref_cnt[i], l + pref_cnt[i + 1], byte - 1);

	RecursiveMSD(array, temp, l + pref_cnt[MAX_AMT - 1], r, byte - 1);
}

// ------------------------------------------------------------------------------

void MSD_sort(int* array, size_t N)
{
	assert(array);

	int* temp = (int*) calloc(N, sizeof(int));

	RecursiveMSD(array, temp, 0, N, 3);

	free(temp);
}

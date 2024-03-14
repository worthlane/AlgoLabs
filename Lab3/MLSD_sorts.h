#ifndef __MLSD_H
#define __MLSD_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>

static const size_t MAX_AMT = 256;   // max array size

void LSD_sort(int* array, size_t N)
{
	assert(array);

    int* sorted_arr = (int*) calloc(N, sizeof(int));
	assert(sorted_arr);

	for (unsigned int mask = 0xff, shift = 0; mask > 0; mask <<= 8, shift += 8)
	{
		unsigned int pref_cnt[MAX_AMT] = {};
		memset(pref_cnt, 0, sizeof(pref_cnt));

		for (int i = 0; i < N; i++)
			pref_cnt[(array[i] & mask) >> shift]++;

		for (int i = 1; i < MAX_AMT; i++)
			pref_cnt[i] += pref_cnt[i - 1];

		for (int i = N - 1; i >= 0; i--)
			sorted_arr[--pref_cnt[(array[i] & mask) >> shift]] = array[i];

		memcpy(array, sorted_arr, sizeof(int) * N);
	}
    free(sorted_arr);
}

// ------------------------------------------------------------------------------

int GetByte(unsigned int num, int byte_num)
{
	unsigned int mask = 0xff;

	mask <<= (byte_num * 8);

	int val = (num & mask) >> (8 * byte_num);

	return val;
}

// ------------------------------------------------------------------------------

int GetBit(unsigned int num, int bit_num)
{
	unsigned int mask = 1;

	mask <<= bit_num;

	int val = (num & mask) >> bit_num;

	return ((num & mask) == mask) ? 1 : 0;
}

// ------------------------------------------------------------------------------

void RecursiveMSDByte(int* array, int* temp, int l, int r, int k)
{
	assert(array);
	assert(temp);

	if (l >= r || k < 0)
		return;

	int bytes[MAX_AMT] = {};

	for (int i = 0; i < MAX_AMT; i++)
		bytes[i] = 0;

	for (int i = l; i < r; i++)
		bytes[GetByte(array[i], k)]++;

	int indexes[MAX_AMT] = {};

	int count = 0; 						// counting array, that will contain amount of numbers before each byte value.
    for (int i = 0; i < MAX_AMT; i++)
	{
        int delta = bytes[i];
        indexes[i] = count;
        count += delta;
    }

	for (int i = l; i < r; i++)
	{
		int byte_val = GetByte(array[i], k);
		temp[indexes[byte_val] + l] = array[i];
		indexes[byte_val]++;
	}

	memcpy(array + l, temp + l, sizeof(int) * (r - l));

	int pref_cnt[MAX_AMT] = {bytes[0]};				// counting prefix sum array
	for (int i = 1; i < MAX_AMT; i++)
		pref_cnt[i] = pref_cnt[i - 1] + bytes[i];

	if (k > 0)
	{
		for (int i = 0; i < MAX_AMT; i++)
		{
			int delta = pref_cnt[i];

			RecursiveMSDByte(array, temp, l + delta - bytes[i], l + delta, k - 1);
		}
	}
}

// ------------------------------------------------------------------------------

void RecursiveMSDBit(int* array, int* temp, int l, int r, int k)
{
	assert(array);
	assert(temp);

	if (l >= r || k < 0)
		return;

	int bits[2] = {};

	for (int i = 0; i < 2; i++)
		bits[i] = 0;

	for (int i = l; i < r; i++)
		bits[GetBit(array[i], k)]++;

	int indexes[2] = {};

	int count = 0; 						// counting array, that will contain amount of numbers before each byte value.
    for (int i = 0; i < 2; i++)
	{
        int delta = bits[i];
        indexes[i] = count;
        count += delta;
    }

	for (int i = l; i < r; i++)
	{
		int byte_val = GetBit(array[i], k);
		temp[indexes[byte_val] + l] = array[i];
		indexes[byte_val]++;
	}

	memcpy(array + l, temp + l, sizeof(int) * (r - l));

	if (k > 0)
	{
		RecursiveMSDBit(array, temp, l, l + bits[0], k - 1);
		RecursiveMSDBit(array, temp, l + bits[0], l + bits[0] + bits[1], k - 1);
	}
}

// ------------------------------------------------------------------------------

void MSDByte_sort(int* array, size_t N)
{
	assert(array);

	int* temp = (int*) calloc(N, sizeof(int));

	RecursiveMSDByte(array, temp, 0, N, 3);

	free(temp);
}

// ------------------------------------------------------------------------------

void MSDBit_sort(int* array, size_t N)
{
	assert(array);

	int* temp = (int*) calloc(N, sizeof(int));

	RecursiveMSDBit(array, temp, 0, N, 31);

	free(temp);
}


#endif

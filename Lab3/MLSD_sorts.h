#ifndef __MLSD_H
#define __MLSD_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>

static const size_t MAX_AMT = 1000000;   // max array size

void LSD_sort(int* array, int* sorted_array, size_t N)
{
	assert(array);

    int* sorted_arr = (int*) calloc(N, sizeof(int));
    
	assert(sorted_array);
	for (int mask = 0xff, shift = 0; mask > 0; mask <<= 8, shift += 8)
	{
		int pref_cnt[MAX_AMT] = {};
		memset(pref_cnt, 0, sizeof(pref_cnt));

		for (int i = 0; i < N; i++)
			pref_cnt[(array[i] & mask) >> shift]++;

		for (int i = 1; i < MAX_AMT; i++)
			pref_cnt[i] += pref_cnt[i - 1];

		for (int i = N - 1; i >= 0; i--)
			sorted_array[--pref_cnt[(array[i] & mask) >> shift]] = array[i];

		memcpy(array, sorted_array, sizeof(unsigned long long) * N);
	}

}

#endif

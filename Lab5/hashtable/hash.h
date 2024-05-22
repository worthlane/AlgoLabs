#ifndef __HASH_H
#define __HASH_H

#include <stdio.h>
#include <stdint.h>

static const size_t MAX_KEY_LEN = 32;

static const size_t PRIME_NUMBERS[]   =
    {
        7, 19, 37, 61, 127, 271, 331, 397, 547, 631,
        919, 1657, 1801, 1951, 2269, 2437, 2791, 3169,
        3571, 4219, 4447, 5167, 5419, 6211, 7057, 7351, 8269,
        9241, 10267, 11719, 12097, 13267, 13669, 16651, 19441,
        19927, 22447, 23497, 24571, 25117, 26227, 27361, 33391, 35317,
        37633, 43201, 47629, 60493, 63949, 65713, 69313, 73009, 76801,
        84673, 106033, 108301, 112909, 115249, 196613,
        393241, 786433, 1572869, 3145739, 6291469, 1000003, 12582917, 2000003
    };
static const size_t PRIME_NUMBERS_AMT = sizeof(PRIME_NUMBERS) / sizeof(*PRIME_NUMBERS);

typedef uint32_t (*strhash_t)(const char* key, const size_t arr_size);

uint32_t ASCII_SumHash(const char* key, const size_t arr_size);
uint32_t StrLenHash(const char* key, const size_t arr_size);
uint32_t PolynomialHash(const char* key, const size_t arr_size);
uint32_t CRC32_Hash(const char* key, const size_t arr_size);

typedef uint32_t (*inthash_t)(const unsigned int key, const size_t arr_size);

uint32_t RemainHash(const unsigned int key, const size_t arr_size);
uint32_t BitHash(const unsigned int key, const size_t arr_size);
uint32_t KnuthHash(const unsigned int key, const size_t arr_size);

typedef uint32_t (*floathash_t)(const float key, const size_t arr_size);

uint32_t IntBitHash(const float key, const size_t arr_size);
uint32_t FloatBitHash(const float key, const size_t arr_size);
uint32_t MantissaHash(const float key, const size_t arr_size);
uint32_t ExponentHash(const float key, const size_t arr_size);
uint32_t MantissaMulExponentHash(const float key, const size_t arr_size);

#endif

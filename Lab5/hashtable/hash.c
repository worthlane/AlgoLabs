#include <assert.h>
#include <string.h>

#include "hash.h"

static const int MAX_BYTE = 31;

// ======================================
// STRING HASHES
// ======================================

uint32_t ASCII_SumHash(const char* key)
{
    assert(key);

    size_t len = strlen(key);

    uint32_t sum = 0;

    for (size_t i = 0; i < len; i++)
        sum += key[i];

    return sum;
}

// --------------------------------------

uint32_t StrLenHash(const char* key)
{
    assert(key);

    uint32_t len = strnlen(key, MAX_KEY_LEN);

    return len;
}

// --------------------------------------

uint32_t CRC32_Hash(const char* key)
{
    assert(key);

    uint32_t crc = -1;

    int i = 0;

    while (key[i] != 0)
    {
        crc = crc ^ (key[i] << 24);
        for (int bit = 0; bit < 8; bit++)
        {
            if (crc & (1L << MAX_BYTE))
                crc = (crc << 1) ^ 0x04C11DB7;
            else
                crc = (crc << 1);
        }

        i++;
    }
    return ~crc;
}

// --------------------------------------

uint32_t PolynomialHash(const char* key)
{
    static const int P = 12582917;
    static const int K = 'z' - 'a' + 1;

    uint32_t hash = 0;

    size_t i = 0;

    while (key[i])
    {
        hash = (hash * K + key[i++]) % P;
    }

    return hash;
}

// ========================================
// INTEGERS HASHES
// ========================================

uint32_t RemainHash(const unsigned int key)
{
    static const int DENOMINATOR = 1000;

    //printf("%d %d\n", key, DENOMINATOR);

    return key % DENOMINATOR;
}

// --------------------------------------

uint32_t BitHash(const unsigned int key)
{
    uint32_t hash = 0;
    int      mask = 0;

    for (int i = MAX_BYTE; i >= 0; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key) >> i);
    }

    return hash;
}

// --------------------------------------

uint32_t KnuthHash(const unsigned int key)
{
    static const int    W = 31;
    static const double A = 0.6180339887;

    static const long long unsigned MULTIPLIER = (1 << W);

    uint64_t S = (A * MULTIPLIER);

    uint64_t hash = key * S;

    return (uint32_t) hash;
}

// ========================================
// FLOAT HASHES
// ========================================

uint32_t IntBitHash(const float key)
{
    return BitHash((unsigned int) key);
}

// --------------------------------------

uint32_t FloatBitHash(const float key)
{
    uint32_t hash = 0;
    int      mask = 0;

    unsigned int key_from_ptr = *((unsigned int*) &key);

    for (int i = MAX_BYTE; i >= 0; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key_from_ptr) >> i);
    }

    return hash;
}

// --------------------------------------

uint32_t MantissaHash(const float key)
{
    uint32_t hash = 0;
    int      mask = 0;

    unsigned int key_from_ptr = *((unsigned int*) &key);

    mask = 1 << 31;
    hash = (mask & key_from_ptr) >> 31;     // MANTISSA SIGN

    static const int MAX_MANTISSA_BYTE = 22;

    for (int i = MAX_MANTISSA_BYTE; i >= 0; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key_from_ptr) >> i);
    }

    return hash;
}

// --------------------------------------

uint32_t ExponentHash(const float key)
{
    uint32_t hash = 0;
    int      mask = 0;

    unsigned int key_from_ptr = *((unsigned int*) &key);

    static const int MIN_EXP_BYTE = 23;
    static const int MAX_EXP_BYTE = 30;

    for (int i = MAX_EXP_BYTE; i >= MIN_EXP_BYTE; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key_from_ptr) >> i);
    }

    return hash;
}

// --------------------------------------

uint32_t MantissaMulExponentHash(const float key)
{
    uint32_t mantissa = MantissaHash(key);
    uint32_t exponent = ExponentHash(key);

    return mantissa * exponent;
}

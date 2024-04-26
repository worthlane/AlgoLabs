#include <assert.h>
#include <string.h>

#include "hash.h"

static const int MAX_BYTE = 31;

// ======================================
// STRING HASHES
// ======================================

uint32_t ASCII_SumHash(const char* key, const size_t arr_size)
{
    assert(key);

    size_t len = strlen(key);

    uint32_t sum = 0;

    for (size_t i = 0; i < len; i++)
        sum += key[i];

    return sum % arr_size;
}

// --------------------------------------

uint32_t StrLenHash(const char* key, const size_t arr_size)
{
    assert(key);

    uint32_t len = strnlen(key, MAX_KEY_LEN);

    return len % arr_size;
}

// --------------------------------------

uint32_t CRC32_Hash(const char* key, const size_t arr_size)
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
    return ~crc % arr_size;
}

// --------------------------------------

uint32_t PolynomialHash(const char* key, const size_t arr_size)
{
    static const int P = 12582917;
    static const int K = 'z' - 'a' + 1;

    uint32_t hash = 0;

    size_t i = 0;

    while (key[i])
    {
        hash = (hash * K + key[i++]) % P;
    }

    return hash % arr_size;
}

// ========================================
// INTEGERS HASHES
// ========================================

uint32_t RemainHash(const unsigned int key, const size_t arr_size)
{
    return key % arr_size;
}

// --------------------------------------

uint32_t BitHash(const unsigned int key, const size_t arr_size)
{
    uint32_t hash = 0;
    int      mask = 0;

    for (int i = MAX_BYTE; i >= 0; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key) >> i);
    }

    return hash % arr_size;
}

// --------------------------------------

uint32_t KnuthHash(const unsigned int key, const size_t arr_size)
{
    static const double A = 0.6180339887;

    return (uint32_t) ((double) arr_size * ((double) key * A - (uint32_t) ((double) key * A)));
}

// ========================================
// FLOAT HASHES
// ========================================

uint32_t IntBitHash(const float key, const size_t arr_size)
{
    return BitHash((unsigned int) key, arr_size);
}

// --------------------------------------

uint32_t FloatBitHash(const float key, const size_t arr_size)
{
    uint32_t hash = 0;
    int      mask = 0;

    unsigned int key_from_ptr = *((unsigned int*) &key);

    for (int i = MAX_BYTE; i >= 0; i--)
    {
        mask = 1 << i;

        hash = hash * 10 + ((mask & key_from_ptr) >> i);
    }

    return hash % arr_size;
}

// --------------------------------------

uint32_t MantissaHash(const float key, const size_t arr_size)
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

    return hash % arr_size;
}

// --------------------------------------

uint32_t ExponentHash(const float key, const size_t arr_size)
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

    return hash % arr_size;
}

// --------------------------------------

uint32_t MantissaMulExponentHash(const float key, const size_t arr_size)
{
    uint32_t mantissa = MantissaHash(key, arr_size);
    uint32_t exponent = ExponentHash(key, arr_size);

    return (mantissa * exponent) % arr_size;
}

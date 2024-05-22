#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "hashtable/hash.h"

static const int   TESTING_TABLE_SIZE = 1000;

static const char* INT_KEYS_PATH   = "tests/keys/int_keys.in";
static const char* FLOAT_KEYS_PATH = "tests/keys/float_keys.in";
static const char* WORD_KEYS_PATH  = "tests/keys/word_keys.in";

static void ResearchIntFuncs();
static void ResearchFloatFuncs();
static void ResearchWordFuncs();

static void DumpResults(const size_t* results, const size_t buf_size, const char* path);

void ResearchHashFuncs()
{
    ResearchIntFuncs();
    ResearchFloatFuncs();
    ResearchWordFuncs();
}

// ---------------------------------------------------------

static void ResearchIntFuncs()
{
    FILE* fp = fopen(INT_KEYS_PATH, "r");
    assert(fp);

    size_t buf_size = 0;
    assert(fscanf(fp, "%lu", &buf_size));

    size_t size = TESTING_TABLE_SIZE;

    size_t* RemainHashResults = calloc(size, sizeof(size_t));
    size_t* BitHashResults    = calloc(size, sizeof(size_t));
    size_t* KnuthHashResults  = calloc(size, sizeof(size_t));
    assert(RemainHashResults && BitHashResults && KnuthHashResults);

    for (size_t i = 0; i < buf_size; i++)
    {
        unsigned int key = 0;
        fscanf(fp, "%d", &key);

        RemainHashResults[RemainHash(key, size)]++;
        BitHashResults[BitHash(key, size)]++;
        KnuthHashResults[KnuthHash(key, size)]++;
    }

    DumpResults(RemainHashResults, size, "results/int_hash/RemainHash.txt");
    DumpResults(BitHashResults, size, "results/int_hash/BitHash.txt");
    DumpResults(KnuthHashResults, size, "results/int_hash/KnuthHash.txt");

    fclose(fp);
}

// ---------------------------------------------------------

static void ResearchFloatFuncs()
{
    FILE* fp = fopen(FLOAT_KEYS_PATH, "r");
    assert(fp);

    size_t buf_size = 0;
    assert(fscanf(fp, "%lu", &buf_size));

    size_t size = TESTING_TABLE_SIZE;

    size_t* IntBitHashResults              = calloc(size, sizeof(size_t));
    size_t* FloatBitHashResults            = calloc(size, sizeof(size_t));
    size_t* MantissaHashResults            = calloc(size, sizeof(size_t));
    size_t* ExponentHashResults            = calloc(size, sizeof(size_t));
    size_t* MantissaMulExponentHashResults = calloc(size, sizeof(size_t));
    assert(IntBitHashResults && FloatBitHashResults && MantissaHashResults &&
           ExponentHashResults && MantissaMulExponentHashResults);

    for (size_t i = 0; i < buf_size; i++)
    {
        float key = 0;
        assert(fscanf(fp, "%f", &key));

        IntBitHashResults[IntBitHash(key, size)]++;
        FloatBitHashResults[FloatBitHash(key, size)]++;
        MantissaHashResults[MantissaHash(key, size)]++;
        ExponentHashResults[ExponentHash(key, size)]++;
        MantissaMulExponentHashResults[MantissaMulExponentHash(key, size)]++;
    }

    DumpResults(IntBitHashResults, size, "results/float_hash/IntBitHash.txt");
    DumpResults(FloatBitHashResults, size, "results/float_hash/FloatBitHash.txt");
    DumpResults(MantissaHashResults, size, "results/float_hash/MantissaHash.txt");
    DumpResults(ExponentHashResults, size, "results/float_hash/ExponentHash.txt");
    DumpResults(MantissaMulExponentHashResults, size, "results/float_hash/MantissaMulExponentHash.txt");

    fclose(fp);
}

// ---------------------------------------------------------

static void ResearchWordFuncs()
{
    FILE* fp = fopen(WORD_KEYS_PATH, "r");
    assert(fp);

    size_t buf_size = 0;
    assert(fscanf(fp, "%lu", &buf_size));

    size_t size = TESTING_TABLE_SIZE;

    size_t* ASCII_SumHashResults  = calloc(size, sizeof(size_t));
    size_t* StrLenHashResults     = calloc(size, sizeof(size_t));
    size_t* PolynomialHashResults = calloc(size, sizeof(size_t));
    size_t* CRC32_HashResults     = calloc(size, sizeof(size_t));
    assert(ASCII_SumHashResults && StrLenHashResults && PolynomialHashResults && CRC32_HashResults);

    for (size_t i = 0; i < buf_size; i++)
    {
        char key[32] = "";
        assert(fscanf(fp, "%31s", key));

        ASCII_SumHashResults[ASCII_SumHash(key, size)]++;
        StrLenHashResults[StrLenHash(key, size)]++;
        PolynomialHashResults[PolynomialHash(key,  size)]++;
        CRC32_HashResults[CRC32_Hash(key, size)]++;
    }

    DumpResults(ASCII_SumHashResults, size, "results/word_hash/ASCII_SumHash.txt");
    DumpResults(StrLenHashResults, size, "results/word_hash/StrLenHash.txt");
    DumpResults(PolynomialHashResults, size, "results/word_hash/PolynomialHash.txt");
    DumpResults(CRC32_HashResults, size, "results/word_hash/CRC32_Hash.txt");

    fclose(fp);
}

// ---------------------------------------------------------

static void DumpResults(const size_t* results, const size_t buf_size, const char* path)
{
    assert(results);
    assert(path);

    FILE* fp = fopen(path, "w");
    assert(fp);

    for (size_t i = 0; i < buf_size; i++)
    {
        fprintf(fp, "%lu %lu\n", i, results[i]);
    }

    fclose(fp);
    free(results);
}

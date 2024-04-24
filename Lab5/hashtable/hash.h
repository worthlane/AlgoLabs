#ifndef __HASH_H
#define __HASH_H

#include <stdio.h>
#include <stdint.h>

static const size_t MAX_KEY_LEN = 32;

typedef uint32_t (*strhash_t)(const char* key);

uint32_t ASCII_SumHash(const char* key);
uint32_t StrLenHash(const char* key);
uint32_t PolynomialHash(const char* key);
uint32_t CRC32_Hash(const char* key);

typedef uint32_t (*inthash_t)(const unsigned int key);

uint32_t RemainHash(const unsigned int key);
uint32_t BitHash(const unsigned int key);
uint32_t KnuthHash(const unsigned int key);

typedef uint32_t (*floathash_t)(const float key);

uint32_t IntBitHash(const float key);
uint32_t FloatBitHash(const float key);
uint32_t MantissaHash(const float key);
uint32_t ExponentHash(const float key);
uint32_t MantissaMulExponentHash(const float key);

#endif

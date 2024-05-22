#ifndef __OPENED_HASHTABLE_H
#define __OPENED_HASHTABLE_H

#include <stdbool.h>

#include "hash.h"

typedef enum
{
    LINEAR,
    QUADRATIC,
    DOUBLE,

    UNKNOWN
} address_t;

typedef struct
{
    int data;
    bool is_full;
} map_elem_t;

typedef struct
{
    map_elem_t* array;

    size_t size;
    size_t cap;

    double load_factor;

    address_t address;
} opened_map_t;

opened_map_t*    OpenedMapCtor(size_t capacity, address_t address_type, const double load_factor_resize);
void             OpenedMapDtor(opened_map_t* table);
void             OpenedMapInsert(opened_map_t* table, int key);
void             OpenedMapErase(opened_map_t* table, int key);
int              IsInOpenedMap(opened_map_t* table, int key);

#endif

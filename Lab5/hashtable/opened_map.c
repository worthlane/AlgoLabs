#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "opened_map.h"

static size_t GetDoubleAddress(opened_map_t* table, const int key);
static size_t GetLinearAddress(opened_map_t* table, const int key);
static size_t GetQuadraticAddress(opened_map_t* table, const int key);

static void OpenedMapResize(opened_map_t* table);

typedef size_t (*address_func)(opened_map_t, const int);

static inline size_t GetAddress(opened_map_t* table, const int key)
{
    size_t index = 0;
    switch (table->address)
    {
        case (LINEAR):
            index = GetLinearAddress(table, key);
            break;
        case (QUADRATIC):
            index = GetQuadraticAddress(table, key);
            break;
        case (DOUBLE):
            index = GetDoubleAddress(table, key);
            break;
        default:
            printf("ADDRESSATION ERROR\n");
            return NULL - 1;
    }

    return index;
}

// --------------------------------------------------------------

opened_map_t* OpenedMapCtor(size_t size, address_t address_type, const double load_factor_resize)
{
    size_t table_size = 0;
    for (size_t i = 0; i < PRIME_NUMBERS_AMT; i++)
    {
        if (size <= PRIME_NUMBERS[i])
        {
            table_size = PRIME_NUMBERS[i];
            break;
        }
    }

    if (table_size == 0)
    {
        printf("TOO BIG TABLE\n");
        return NULL;
    }

    opened_map_t* table = calloc(1, sizeof(opened_map_t));
    assert(table);

    map_elem_t* data = calloc(table_size, sizeof(map_elem_t));
    assert(data);

    table->size        = 0;
    table->cap         = table_size;
    table->address     = address_type;
    table->load_factor = load_factor_resize;

    table->array = data;

    return table;
}

// --------------------------------------------------------------

void OpenedMapDtor(opened_map_t* table)
{
	assert(table);

	free(table->array);
	free(table);
}

// --------------------------------------------------------------

static size_t GetLinearAddress(opened_map_t* table, const int key)
{
    assert(table);

    size_t index = BitHash(key, table->cap);

    do
    {
        map_elem_t elem = table->array[index];

        if (elem.is_full == false)
            return index;

        if (elem.is_full && elem.data == key)
            return index;

        index = (index + 1) % (table->cap);
    }
    while (true);
}

// --------------------------------------------------------------

static size_t GetQuadraticAddress(opened_map_t* table, const int key)
{
    assert(table);

    size_t hash = BitHash(key, table->cap);
    int    i    = 0;

    size_t index = hash % table->cap;

    do
    {
        map_elem_t elem = table->array[index];

        if (elem.is_full == false)
            return index;

        if (elem.is_full && elem.data == key)
            return index;

        i++;

        index += i;

        index = index % (table->cap);
    }
    while (true);
}

// --------------------------------------------------------------

static size_t GetDoubleAddress(opened_map_t* table, const int key)
{
    assert(table);

    size_t index1 = BitHash(key, table->cap);
    size_t index2 = key % (table->cap - 1) + 1;

    size_t index = index1 % table->cap;

    do
    {
        map_elem_t elem = table->array[index];

        if (elem.is_full == false)
            return index;

        if (elem.is_full && elem.data == key)
            return index;

        index = (index + index2) % (table->cap);
    }
    while (true);
}

// --------------------------------------------------------------

void OpenedMapInsert(opened_map_t* table, int key)
{
    size_t index = GetAddress(table, key);

    map_elem_t elem = table->array[index];

    if (elem.data == key && elem.is_full)
        return;

    table->size++;
    table->array[index].data    = key;
    table->array[index].is_full = true;

    OpenedMapResize(table);
}

// --------------------------------------------------------------

static void OpenedMapResize(opened_map_t* table)
{
    double cur_load_factor = (double) table->size / (double) table->cap;

    if (cur_load_factor < table->load_factor && table->size < table->cap)
        return;

    size_t cur_table_cap = table->cap;

    opened_map_t* new_map = OpenedMapCtor(cur_table_cap * 2, table->address, table->load_factor);
    assert(new_map);

    map_elem_t elem = {};
    int        key  = 0;

    for (size_t i = 0; i < cur_table_cap; i++)
    {
        elem = table->array[i];
        key  = elem.data;

        if (elem.is_full)
            OpenedMapInsert(new_map, key);
    }

    free(table->array);

    table->array = new_map->array;
    table->cap   = new_map->cap;

    free(new_map);
}


// --------------------------------------------------------------

void OpenedMapErase(opened_map_t* table, int key)
{
    size_t index = GetAddress(table, key);

    map_elem_t elem = table->array[index];

    if (!elem.is_full)
        return;

    table->size--;
    table->array[index].data    = 0;
    table->array[index].is_full = false;
}

// --------------------------------------------------------------

int IsInOpenedMap(opened_map_t* table, int key)
{
    size_t index = GetAddress(table, key);

    map_elem_t elem = table->array[index];

    if (elem.is_full && elem.data == key)
        return true;
    else
        return false;
}

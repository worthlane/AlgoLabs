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

typedef size_t (*address_func)(opened_map_t, const int);

// --------------------------------------------------------------

opened_map_t* OpenedMapCtor(size_t size, address_t address_type)
{
	static const size_t prime_numbers[]   =
    {
        7, 19, 37, 61, 127, 271, 331, 397, 547, 631,
        919, 1657, 1801, 1951, 2269, 2437, 2791, 3169,
        3571, 4219, 4447, 5167, 5419, 6211, 7057, 7351, 8269,
        9241, 10267, 11719, 12097, 13267, 13669, 16651, 19441,
        19927, 22447, 23497, 24571, 25117, 26227, 27361, 33391, 35317,
        37633, 43201, 47629, 60493, 63949, 65713, 69313, 73009, 76801,
        84673, 106033, 108301, 112909, 115249, 196613,
        393241, 786433, 1572869, 3145739, 6291469, 1000003, 12582917
    };
    static const size_t prime_numbers_amt = sizeof(prime_numbers) / sizeof(*prime_numbers);

    size_t table_size = 0;
    for (size_t i = 0; i < prime_numbers_amt; i++)
    {
        if (size <= prime_numbers[i])
        {
            table_size = prime_numbers[i];
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

    table->size = 0;
    table->cap  = table_size;
    table->address = address_type;

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

    size_t index = BitHash(key) % (table->cap);

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

    size_t hash = BitHash(key);
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

        index = (hash + i + i*i) % (table->cap);
    }
    while (true);
}

// --------------------------------------------------------------

static size_t GetDoubleAddress(opened_map_t* table, const int key)
{
    assert(table);

    size_t index1 = BitHash(key);
    size_t index2 = key;

    size_t index = (index1 + index2) % table->cap;

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
            return;
    }

    map_elem_t elem = table->array[index];

    if (elem.data == key && elem.is_full)
        return;

    table->size++;
    table->array[index].data    = key;
    table->array[index].is_full = true;
}

// --------------------------------------------------------------

void OpenedMapErase(opened_map_t* table, int key)
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
            return;
    }

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
            return false;
    }

    map_elem_t elem = table->array[index];

    if (elem.is_full && elem.data == key)
        return true;
    else
        return false;
}

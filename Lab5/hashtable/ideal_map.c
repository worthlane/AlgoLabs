#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "ideal_map.h"

static const int A_STD = 0;
static const int B_STD = 0;

static inline int LinearHash(const int a, const int b, const int m, const int key)
{
	int index = 0;
	int p = PRIME_NUMBERS[index];
	while (p < m && index < PRIME_NUMBERS_AMT)
	{
		p = PRIME_NUMBERS[index++];
	}

	return abs(((a * key + b) % p) % m);
}

static inline long long int Min(long long int a, long long int b)
{
	return (a > b) ? b : a;
}

static inline long long int Max(long long int a, long long int b)
{
	return (a > b) ? a : b;
}

static table_t* TableCtor(const size_t size);
static void TableDtor(table_t* table);

static void FreezeTable(table_t* table, const size_t size);
static void ChooseMapHash(ideal_map_t* map, const int* keys, const size_t size);
static void FillMap(ideal_map_t* map, const int* keys, const size_t size);
static void FreezeTable(table_t* table, const size_t size);

// ---------------------------------------------------------------------

static table_t* TableCtor(const size_t size)
{
	static const size_t MIN_TABLE_SIZE = 1;

	size_t table_size = size * size;

	if (table_size < size)
		table_size = size;

	if (table_size < MIN_TABLE_SIZE)
		table_size = MIN_TABLE_SIZE;

	table_elem_t* data = calloc(table_size, sizeof(table_elem_t));
	assert(data);

	table_t* table = calloc(1, sizeof(table_t));
	assert(table);

	table->size   = table_size;
	table->a_hash = 0;
	table->b_hash = 0;
	table->data   = data;

	return table;
}

// ---------------------------------------------------------------------

static void TableDtor(table_t* table)
{
	if (table == NULL)
		return;

	free(table->data);
	free(table);
}

// ---------------------------------------------------------------------

ideal_map_t* IdealMapCtor(const int* keys, const size_t size)
{
	assert(keys);

	ideal_map_t* map = calloc(1, sizeof(ideal_map_t));
	assert(map);

	int index = 0;

	size_t map_size = size;

	table_t** tables = calloc(map_size, sizeof(table_t*));
	assert(tables);

	map->size = map_size;
	map->tables = tables;

	FillMap(map, keys, size);

	return map;
}

// ---------------------------------------------------------------------

static void ChooseMapHash(ideal_map_t* map, const int* keys, const size_t size)
{
	assert(map);
	assert(keys);

	int* amt = calloc(map->size, sizeof(int));
	assert(amt);

	while (true)
	{
		int a = PRIME_NUMBERS[rand() % PRIME_NUMBERS_AMT];
		int b = PRIME_NUMBERS[rand() % PRIME_NUMBERS_AMT] - 1;

		for (size_t i = 0; i < size; i++)
		{
			int hash = LinearHash(a, b, map->size, keys[i]);
			amt[hash]++;
		}

		int delta_sum = 0;

		for (size_t i = 0; i < map->size; i++)
		{
			delta_sum += amt[i] * amt[i];
		}

		if (delta_sum <= size * 4)
		{
			map->a_hash = a;
			map->b_hash = b;
			break;
		}

		memset(amt, 0, map->size * sizeof(int));
	}

	for (size_t i = 0; i < map->size; i++)
	{
		if (amt[i] != 0)
			map->tables[i] = TableCtor(amt[i] * amt[i]);
	}

	free(amt);
}

// ---------------------------------------------------------------------

static void FillMap(ideal_map_t* map, const int* keys, const size_t size)
{
	assert(map);
	assert(keys);

	ChooseMapHash(map, keys, size);

	int* last_indexes = calloc(map->size, sizeof(int));
	assert(last_indexes);

	for (size_t i = 0; i < size; i++)
	{
		int hash = LinearHash(map->a_hash, map->b_hash, map->size, keys[i]);
		table_t* target_table = map->tables[hash];
		target_table->data[last_indexes[hash]++].key = keys[i];      // we save keys in table, then we choose hash function and freeze table
	}

	for (size_t i = 0; i < map->size; i++)
	{
		FreezeTable(map->tables[i], last_indexes[i]);
	}

	free(last_indexes);
}

// ---------------------------------------------------------------------

void IdealMapDtor(ideal_map_t* map)
{
	for (size_t i = 0; i < map->size; i++)
	{
		TableDtor(map->tables[i]);
	}

	free(map->tables);

	free(map);
}

// ---------------------------------------------------------------------

static void FreezeTable(table_t* table, const size_t size)
{
	if (table == NULL)
		return;

	int* keys = calloc(size, sizeof(int));
	assert(keys);

	for (size_t i = 0; i < size; i++)
	{
		keys[i] = table->data[i].key;
	}

	while (true)
	{
		memset(table->data, 0, table->size * sizeof(table_elem_t));

		int a = PRIME_NUMBERS[rand() % PRIME_NUMBERS_AMT];
		int b = PRIME_NUMBERS[rand() % PRIME_NUMBERS_AMT] - 1;

		bool good_hash_flag = true;

		for (size_t i = 0; i < size; i++)
		{
			int hash = LinearHash(a, b, table->size, keys[i]);

			table->data[hash].key = keys[i];
			table->data[hash].amt++;

			if (table->data[hash].amt > 1)
				good_hash_flag = false;
		}

		if (good_hash_flag)
		{
			table->a_hash = a;
			table->b_hash = b;
			break;
		}
	}

	free(keys);
}

// ---------------------------------------------------------------------

bool IsInIdealMap(ideal_map_t* map, const int key)
{
	int hash = LinearHash(map->a_hash, map->b_hash, map->size, key);

	table_t* target_table = map->tables[hash];

	if (target_table == NULL)
		return false;

	int hash_in_table = LinearHash(target_table->a_hash, target_table->b_hash, target_table->size, key);

	table_elem_t elem = target_table->data[hash_in_table];

	if (elem.amt != 0 && elem.key == key)
		return true;
	else
		return false;

}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>


typedef struct {
	int key;
	int amt;
} elem_t;

typedef struct table_t
{
	elem_t* data;

	size_t size;
	int    a_hash ;
	int    b_hash;
} table_t;

typedef struct hashmap_t
{
	table_t** tables;

	size_t size;
	int    a_hash ;
	int    b_hash;
} hashmap_t;

hashmap_t* HashmapCtor(const int* keys, const size_t size);
void       HashmapDtor(hashmap_t* map);

void       FillMap(hashmap_t* map, const int* keys, const size_t size);

static const int A_STD = 0;
static const int B_STD = 0;

static const int PRIMES[] = { 	1, 7, 19, 37, 61, 127, 271, 331, 397, 547, 631,
								919, 1657, 1801, 1951, 2269, 2437, 2791, 3169,
								3571, 4219, 4447, 5167, 5419, 6211, 7057, 7351, 8269,
								9241, 10267, 11719, 12097, 13267, 13669, 16651, 19441,
								19927, 22447, 23497, 24571, 25117, 26227, 27361, 33391, 35317,
								37633, 43201, 47629, 60493, 63949, 65713, 69313, 73009, 76801,
								84673, 106033, 108301, 112909, 1152491,196613,
								393241,786433,1572869,3145739,6291469,12582917 };

static const int PRIMES_AMT = sizeof(PRIMES) / sizeof(*PRIMES);

static inline int LinearHash(const int a, const int b, const int m, const int key)
{
	int index = 0;
	int p = PRIMES[index];
	while (p < m && index < PRIMES_AMT)
	{
		p = PRIMES[index++];
	}

	return abs(((a * key + b) % p) % m);
}

table_t* TableCtor(const size_t size);
void     TableDtor(table_t* table);
void     FreezeTable(table_t* table, const size_t size);

static inline long long int Min(long long int a, long long int b)
{
	return (a > b) ? b : a;
}

static inline long long int Max(long long int a, long long int b)
{
	return (a > b) ? a : b;
}

static inline void SkipSpaces()
{
	char ch = getc(stdin);

	while (isspace(ch))
		ch = getc(stdin);

	ungetc(ch, stdin);
}

bool IsInMap(hashmap_t* map, const int key);

int* GetArray(const size_t size);

// =====================================================================

int main()
{
	srand(time(NULL));

	size_t N = 0;
	int read = scanf("%lu", &N);
	if (!read)
		return 1;

	int* keys = GetArray(N);
	assert(keys);

	hashmap_t* map = HashmapCtor(keys, N);

	int key = 0;

	while (true)
	{
		if (!scanf("%d", &key))
		{
			char ch = 0;

			int read_ch = scanf("%c", &ch);
			if (!read_ch)
				return 1;

			if (ch == '.')
				break;

			SkipSpaces();
		}
		else
		{
			if (IsInMap(map, key))
				printf("YES\n");
			else
				printf("NO\n");
		}

	}

	HashmapDtor(map);
	free(keys);

	return 0;
}

// ---------------------------------------------------------------------

int* GetArray(const size_t size)
{
	int* array = calloc(size, sizeof(int));
	assert(array);

	int read = 0;
	for (size_t i = 0; i < size; i++)
	{
		read = scanf("%d", &array[i]);
		if (!read)
			return NULL;
	}

	return array;
}

// ---------------------------------------------------------------------

table_t* TableCtor(const size_t size)
{
	static const size_t MIN_TABLE_SIZE = 1;

	size_t table_size = size * size;

	if (table_size < size)
		table_size = size;

	if (table_size < MIN_TABLE_SIZE)
		table_size = MIN_TABLE_SIZE;

	elem_t* data = calloc(table_size, sizeof(elem_t));
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

void TableDtor(table_t* table)
{
	if (table == NULL)
		return;

	free(table->data);
	free(table);
}

// ---------------------------------------------------------------------

hashmap_t* HashmapCtor(const int* keys, const size_t size)
{
	assert(keys);

	hashmap_t* map = calloc(1, sizeof(hashmap_t));
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

void ChooseMapHash(hashmap_t* map, const int* keys, const size_t size)
{
	assert(map);
	assert(keys);

	int* amt = calloc(map->size, sizeof(int));
	assert(amt);

	static const int MAX_FILLING_COEF = 4;

	while (true)
	{
		int a = PRIMES[rand() % PRIMES_AMT];
		int b = PRIMES[rand() % PRIMES_AMT] - 1;

		for (size_t i = 0; i < size; i++)
		{
			int hash = LinearHash(a, b, map->size, keys[i]);
			amt[hash]++;
		}

		int delta_sum = 0;

		for (size_t i = 0; i < map->size; i++)
		{
			delta_sum += amt[i];
		}

		if (delta_sum <= size * MAX_FILLING_COEF)
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
			map->tables[i] = TableCtor(amt[i]);
	}

	free(amt);
}

// ---------------------------------------------------------------------

void FillMap(hashmap_t* map, const int* keys, const size_t size)
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

void HashmapDtor(hashmap_t* map)
{
	for (size_t i = 0; i < map->size; i++)
	{
		TableDtor(map->tables[i]);
	}

	free(map->tables);

	free(map);
}

// ---------------------------------------------------------------------

void FreezeTable(table_t* table, const size_t size)
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
		memset(table->data, 0, table->size * sizeof(elem_t));

		int a = PRIMES[rand() % PRIMES_AMT];
		int b = PRIMES[rand() % PRIMES_AMT] - 1;

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

bool IsInMap(hashmap_t* map, const int key)
{
	int hash = LinearHash(map->a_hash, map->b_hash, map->size, key);

	table_t* target_table = map->tables[hash];

	if (target_table == NULL)
		return false;

	int hash_in_table = LinearHash(target_table->a_hash, target_table->b_hash, target_table->size, key);

	elem_t elem = target_table->data[hash_in_table];

	if (elem.amt != 0 && elem.key == key)
		return true;
	else
		return false;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "listed_map.h"

void FillListElem(list_elem_t* node, int key, const int is_end, list_elem_t* next, list_elem_t* prev);

// --------------------------------------------------------------

struct list_elem_t* ListElemCtor()
{
	struct list_elem_t* node = (struct list_elem_t*) calloc(1, sizeof(struct list_elem_t));

	node->next = node;
	node->prev = node;
	node->key  = 0;
	node->is_end = true;

	return node;
}

// --------------------------------------------------------------

void ListElemDtor(struct list_elem_t* node)
{
	assert(node);

	free(node);
}

// --------------------------------------------------------------

struct listed_map_t* ListedMapCtor(size_t size)
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

    listed_map_t* table = calloc(1, sizeof(listed_map_t));
    assert(table);

    list_elem_t** cells = calloc(table_size, sizeof(list_elem_t*));
    assert(cells);

    for (size_t i = 0; i < table_size; i++)
        cells[i] = ListElemCtor();

    table->cap = table_size;
	table->size = 0;
    table->cells = cells;

    return table;
}

// --------------------------------------------------------------

void ListedMapDtor(struct listed_map_t* table) // TODO
{
	assert(table);

	table->size = 0;
	free(table->cells);
	free(table);
}

// --------------------------------------------------------------

static size_t GetKeyIndex(struct listed_map_t* table, int key)
{
	assert(table);

	unsigned int hash = BitHash(key, table->cap);
	size_t    index = hash % table->cap;

	return index;
}

// --------------------------------------------------------------

struct list_elem_t* FindKeyInList(struct list_elem_t* root_cell, int key)
{
	assert(root_cell);

	struct list_elem_t* cell = root_cell;

	size_t error_cnt = 0;

	while (cell->is_end != true)
	{
		if (cell->key == key)
			return cell;

		cell = cell->next;

		error_cnt++;

		if (error_cnt >= MAX_LIST_LEN)
		{
			perror("INVALID LIST FORMAT\n");
			return NULL;
		}
	}

	return cell;
}

// --------------------------------------------------------------

void FillListElem(list_elem_t* node, int key, const int is_end, list_elem_t* next, list_elem_t* prev)
{
	assert(node);

	node->key  = key;
	node->next = next;
	node->prev = prev;
	node->is_end = is_end;
}


// --------------------------------------------------------------

void ListedMapInsert(struct listed_map_t* table, int key)
{
	assert(table);

	size_t index = GetKeyIndex(table, key);

	struct list_elem_t* root_cell = table->cells[index];

	struct list_elem_t* key_node = FindKeyInList(root_cell, key);

	if (key_node->is_end != true)
	{
		key_node->key = key;
		return;
	}

	assert(key_node);

	struct list_elem_t* new_cell = (struct list_elem_t*) calloc(1, sizeof(struct list_elem_t));
	assert(new_cell);

	FillListElem(new_cell, key, false, key_node, key_node->prev);
	(key_node->prev)->next = new_cell;
	key_node->prev         = new_cell;

	table->cells[index] = key_node->next;

	table->size++;
}

// --------------------------------------------------------------

void ListedMapErase(struct listed_map_t* table, int key)
{
	assert(table);

	size_t index = GetKeyIndex(table, key);
	struct list_elem_t* root_cell = table->cells[index];

	struct list_elem_t* key_node = FindKeyInList(root_cell, key);

	if (key_node->is_end == true)
		return;

	struct list_elem_t* end_node = table->cells[index]->prev;

	key_node->next->prev = key_node->prev;
	key_node->prev->next = key_node->next;

	table->cells[index] = end_node->next;

	table->size--;
}

// --------------------------------------------------------------

int IsInListedMap(struct listed_map_t* table, int key)
{
	assert(table);

	size_t index = GetKeyIndex(table, key);
	struct list_elem_t* root_cell = table->cells[index];

	struct list_elem_t* key_node = FindKeyInList(root_cell, key);

	if (key_node->is_end != true)
		return true;

	return false;
}

// --------------------------------------------------------------

static size_t GetListSize(struct list_elem_t* root_cell)
{
	assert(root_cell);

	size_t size = 0;

	struct list_elem_t* cell = root_cell;

	while (cell->is_end != true)
	{
		size++;

		if (size >= MAX_LIST_LEN)
		{
			printf("INVALID LIST FORMAT\n");
			return size;
		}

		cell = cell->next;
	}

	return size;
}


#ifndef __LISTED_HASHTABLE_H
#define __LISTED_HASHTABLE_H

#include "hash.h"

static const int UNKNOWN_VAL = -1337;

typedef struct list_elem_t
{
	int key;
	int is_end;

	struct list_elem_t* next;
	struct list_elem_t* prev;
} list_elem_t;

struct list_elem_t* ListElemCtor();
void                ListElemDtor(struct list_elem_t* node);
void 				ListDtor(struct list_elem_t* root);
struct list_elem_t*      FindKeyInList(struct list_elem_t* root_cell, int key);

typedef struct listed_map_t
{
	struct list_elem_t** cells;

	size_t   cap;
	size_t   size;

	double 	load_factor;
} listed_map_t;

struct listed_map_t*     ListedMapCtor(size_t size, const double load_factor);
void                    ListedMapDtor(struct listed_map_t* table);
void                    ListedMapInsert(struct listed_map_t* table, const int key);
void                    ListedMapErase(struct listed_map_t* table, const int key);
int                     IsInListedMap(struct listed_map_t* table, const int key);

static const size_t MAX_LIST_LEN = 1000000;

static size_t  GetKeyIndex(struct listed_map_t* table, const int key);
static size_t  GetListSize(struct list_elem_t* root_cell);


#endif

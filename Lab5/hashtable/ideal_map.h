#ifndef __IDEAL_HASHTABLE_H
#define __IDEAL_HASHTABLE_H

#include "hash.h"

typedef struct {
	int key;
	int amt;
} table_elem_t;

typedef struct table_t
{
	table_elem_t* data;

	size_t size;
	int    a_hash ;
	int    b_hash;
} table_t;

typedef struct ideal_map_t
{
	table_t** tables;

	size_t size;
	int    a_hash ;
	int    b_hash;
} ideal_map_t;

ideal_map_t* IdealMapCtor(const int* keys, const size_t size);
void         IdealMapDtor(ideal_map_t* map);

bool         IsInIdealMap(ideal_map_t* map, const int key);


#endif

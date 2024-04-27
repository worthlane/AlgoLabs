#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "launch/load_factor_test.h"
#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "launch/research_func.h"


int main(const int argc, const char* argv[])
{
    srand(time(NULL));
    //printf("%lu\n", KnuthHash(442342000));

    /*listed_map_t* map = ListedMapCtor(2, 0.3);

    printf("1 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 50);
    printf("2 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 20);
    printf("3 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 30);
    printf("4 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 33);
    printf("5 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 70);
    printf("6 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 51);

    printf("7 {%d} %d\n", map->cap, map->size);

    ListedMapInsert(map, 21);

    printf("8 {%d} %d\n", map->cap, map->size);

    ListedMapInsert(map, 31);
    printf("9 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 31);
    printf("10 {%d} %d\n", map->cap, map->size);
    ListedMapInsert(map, 71);

    ListedMapErase(map, 22);

    printf("%d %d\n", IsInListedMap(map, 50), IsInListedMap(map, 22));
    printf("%d %d\n", IsInListedMap(map, 31), IsInListedMap(map, 51));*/

    //ResearchLoadFactor();

    //ResearchHashFuncs();

    LoadFactorsFirstPointData();

    return 0;
}

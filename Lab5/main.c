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

    opened_map_t* map = OpenedMapCtor(2, DOUBLE, 1);

    printf("1 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 50);
    printf("2 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 20);
    printf("3 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 30);
    printf("4 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 33);
    printf("5 {%d} %d\n", map->cap, map->size);


    OpenedMapInsert(map, 70);


    printf("6 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 51);
    printf("7 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 21);
    printf("8 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 31);
    printf("9 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 31);
    printf("10 {%d} %d\n", map->cap, map->size);
    OpenedMapInsert(map, 71);

    /*printf("%d %d\n", IsInOpenedMap(map, 50), IsInOpenedMap(map, 22));

    OpenedMapErase(map, 22);

    printf("%d %d\n", IsInOpenedMap(map, 50), IsInOpenedMap(map, 22));*/

    //ResearchLoadFactor();

    //ResearchHashFuncs();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "launch/load_factor_test.h"
#include "launch/ideal_hash_research.h"
#include "hashtable/hash.h"
#include "hashtable/listed_map.h"
#include "hashtable/opened_map.h"
#include "launch/research_func.h"


int main(const int argc, const char* argv[])
{
    srand(time(NULL));

    //ResearchHashFuncs();

    LoadFactorsFirstPointData();

    //CompareMaps();

    return 0;
}

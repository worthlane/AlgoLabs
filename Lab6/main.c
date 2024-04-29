#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include "trees/avl.h"
#include "trees/treap.h"
#include "trees/splay.h"
#include "trees/bst.h"

#include "testing.h"

static const char* SORTED_TESTS   = "tests/sorted_keys/";
static const char* UNSORTED_TESTS = "tests/unsorted_keys/";

static const char* UNSORTED_RES = "results/unsorted/";
static const char* SORTED_RES   = "results/sorted/";

static const size_t TEST_BST_UNSORTED = 100000;
static const size_t TEST_BST_SORTED   = 100000;


static const size_t TEST_AVL_FROM = 100000;
static const size_t TEST_AVL_TO   = 1000000;
static const size_t TEST_AVL_STEP = 100000;

static const size_t TEST_TREAP_FROM = 100000;
static const size_t TEST_TREAP_TO   = 1000000;
static const size_t TEST_TREAP_STEP = 100000;

static const size_t TEST_SPLAY_FROM = 100000;
static const size_t TEST_SPLAY_TO   = 1000000;
static const size_t TEST_SPLAY_STEP = 100000;


int main(const int argc, const char* argv[])
{
    srand(time(NULL));

    /*TestTree(TEST_BST_UNSORTED, TEST_BST_UNSORTED, 1, UNSORTED_TESTS, UNSORTED_RES,
             "BST", BSTTreeCtor, BSTTreeDtor, BSTTreeInsert, BSTTreeRemove);

    TestTree(TEST_BST_SORTED, TEST_BST_SORTED, 1, SORTED_TESTS, SORTED_RES,
             "BST", BSTTreeCtor, BSTTreeDtor, BSTTreeInsert, BSTTreeRemove);*/

    /*TestTree(TEST_TREAP_FROM, TEST_TREAP_TO, TEST_TREAP_STEP, UNSORTED_TESTS, UNSORTED_RES,
             "TREAP", TreapCtor, TreapDtor, TreapInsert, TreapRemove);

    TestTree(TEST_TREAP_FROM, TEST_TREAP_TO, TEST_TREAP_STEP, SORTED_TESTS, SORTED_RES,
             "TREAP", TreapCtor, TreapDtor, TreapInsert, TreapRemove);*/

    /*TestTree(TEST_SPLAY_FROM, TEST_SPLAY_TO, TEST_SPLAY_STEP, UNSORTED_TESTS, UNSORTED_RES,
             "SPLAY", SplayTreeCtor, SplayTreeDtor, SplayTreeInsert, SplayTreeRemove);

    TestTree(TEST_SPLAY_FROM, TEST_SPLAY_TO, TEST_SPLAY_STEP, SORTED_TESTS, SORTED_RES,
             "SPLAY", SplayTreeCtor, SplayTreeDtor, SplayTreeInsert, SplayTreeRemove);*/

    TestTree(TEST_AVL_FROM, TEST_AVL_TO, TEST_AVL_STEP, UNSORTED_TESTS, UNSORTED_RES,
             "AVL", AVLTreeCtor, AVLTreeDtor, AVLTreeInsert, AVLTreeRemove);

    TestTree(TEST_AVL_FROM, TEST_AVL_TO, TEST_AVL_STEP, SORTED_TESTS, SORTED_RES,
             "AVL", AVLTreeCtor, AVLTreeDtor, AVLTreeInsert, AVLTreeRemove);

    return 0;
}

// -------------------------------------------------------------------------


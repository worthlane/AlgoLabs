#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "trees/avl.h"
#include "trees/treap.h"
#include "trees/splay.h"

int main(const int argc, const char* argv[])
{
    srand(time(NULL));

    avl_tree_t* tree = AVLTreeCtor();

    AVLTreeInsert(tree, 5);
    AVLTreeInsert(tree, 9);
    AVLTreeInsert(tree, 1);
    AVLTreeInsert(tree, 2);

    PrintAVLTree(tree->root);

    AVLTreeDtor(tree);

    return 0;
}

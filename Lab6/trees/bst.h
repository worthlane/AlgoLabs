#ifndef __BST_H
#define __BST_H

typedef struct bst_node_t {
	struct bst_node_t* upper;

	int key;

	struct bst_node_t* left;
	struct bst_node_t* right;
} bst_node_t;

typedef struct
{
	bst_node_t* root;
} bst_tree_t;

bst_tree_t* BSTTreeCtor();
void        BSTTreeInsert(bst_tree_t* tree, const int key);
void        BSTTreeRemove(bst_tree_t* tree, const int key);
void        BSTTreeDtor(bst_tree_t* tree);

void    PrintBSTTree(const bst_node_t* root);

#endif

#ifndef __AVL_H
#define __AVL_H

typedef struct avl_node_t {
	struct avl_node_t* upper;

	int key;
	int height;

	struct avl_node_t* left;
	struct avl_node_t* right;
} avl_node_t;

typedef struct
{
	avl_node_t* root;
} avl_tree_t;

avl_tree_t* AVLTreeCtor();
void        AVLTreeInsert(avl_tree_t* tree, const int key);
void        AVLTreeRemove(avl_tree_t* tree, const int key);
void        AVLTreeDtor(avl_tree_t* tree);

void    PrintAVLTree(const avl_node_t* root);

#endif

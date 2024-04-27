#ifndef __SPLAY_H
#define __SPLAY_H

typedef struct splay_node_t {
	struct splay_node_t* upper;

	int key;

	struct splay_node_t* left;
	struct splay_node_t* right;
} splay_node_t;

typedef struct
{
	splay_node_t* root;
} splay_tree_t;

typedef struct double_splay_node_t
{
	splay_node_t* first;
	splay_node_t* second;
} double_splay_node_t;

splay_tree_t*   SplayTreeCtor();
void            SplayTreeInsert(splay_tree_t* tree, const int key);
void            SplayTreeDtor(splay_tree_t* tree);

void            PrintSplayTree(const splay_node_t* root);

#endif

#ifndef __TREAP_H
#define __TREAP_H

typedef struct treap_node_t {
	struct treap_node_t* upper;

	int priority;
	int key;

	struct treap_node_t* left;
	struct treap_node_t* right;
} treap_node_t;

typedef struct treap_t
{
	treap_node_t* root;
} treap_t;

typedef struct double_treap_node_t
{
	treap_node_t* first;
	treap_node_t* second;
} double_treap_node_t;

treap_t* TreapCtor();
void     TreapDtor(treap_t* treap);
void     TreapInsert(treap_t* treap, const int key);
void     TreapRemove(treap_t* treap, const int key);
void     PrintTreap(treap_node_t* root);

#endif

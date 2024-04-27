#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "treap.h"

static treap_node_t* NodeCtor(int prior, int key, treap_node_t* left, treap_node_t* right, treap_node_t* upper);
static void          NodeFill(treap_node_t* node, int prior, int key, treap_node_t* left, treap_node_t* right, treap_node_t* upper);

static double_treap_node_t* Split(treap_node_t* treap, int x);
static treap_node_t*        Merge(treap_node_t* first, treap_node_t* second);
static treap_node_t*        FindNode(treap_t* treap, int x);

static enum Side
{
	RIGHT,
	LEFT,
};

static void ConnectNodes(treap_node_t* parent, treap_node_t* son, const enum Side side);
static void DestructTreap(treap_node_t* root);

static inline int Min(int a, int b)
{
	return (a > b) ? b : a;
}

static inline int Max(int a, int b)
{
	return (a > b) ? a : b;
}

// =====================================================================

static treap_node_t* NodeCtor(int prior, int key, treap_node_t* left, treap_node_t* right, treap_node_t* upper)
{
	treap_node_t* node = (treap_node_t*) calloc(1, sizeof(treap_node_t));
	assert(node);

	node->priority = prior;
	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;

	return node;
}

// ---------------------------------------------------------------------

static void NodeFill(treap_node_t* node, int prior, int key, treap_node_t* left, treap_node_t* right, treap_node_t* upper)
{
	assert(node);

	node->left     = left;
	node->right    = right;
	node->key      = key;
	node->priority = prior;
	node->upper    = upper;
}


// ---------------------------------------------------------------------

static void DestructTreap(treap_node_t* root)
{
	if (root == NULL)   return;

	DestructTreap(root->left);
	DestructTreap(root->right);

	free(root);
}

// ---------------------------------------------------------------------

treap_t* TreapCtor()
{
	treap_t* treap = calloc(1, sizeof(treap_t));
	assert(treap);

	return treap;
}

// ---------------------------------------------------------------------

void TreapInsert(treap_t* treap, int key)
{
	assert(treap);

	if (FindNode(treap, key))
		return;

	int prior = rand();

	treap_node_t* node = NodeCtor(prior, key, NULL, NULL, NULL);
	assert(node);

	if (treap->root == NULL)
	{
		treap->root = node;
		return;
	}

	double_treap_node_t* split = Split(treap->root, key);

	treap_node_t* merge = Merge(split->first, node);
	treap->root = Merge(merge, split->second);

	free(split);
}

// ---------------------------------------------------------------------

void TreapRemove(treap_t* treap, int key)
{
	assert(treap);

	treap_node_t* removing = FindNode(treap, key);

	if (removing == NULL)
		return;

	treap_node_t* replace = Merge(removing->left, removing->right);

	treap_node_t* parent = removing->upper;

	if (replace != NULL)
		replace->upper = parent;

	if (parent == NULL)
		treap->root = replace;
	else
	{
		if (parent->left == removing)
			ConnectNodes(parent, replace, LEFT);    //parent->left = replace;
		else if (parent->right == removing)
			ConnectNodes(parent, replace, RIGHT);   //parent->right = replace;
	}

	free(removing);
}

// ---------------------------------------------------------------------

static double_treap_node_t* Split(treap_node_t* treap, int x)
{
	double_treap_node_t* ans = calloc(1, sizeof(double_treap_node_t));
	assert(ans);

	if (treap == NULL)
	{
		ans->first = NULL;
		ans->second = NULL;
	}
	else if (x < treap->key)
	{
		double_treap_node_t* ans2 = Split(treap->left, x);
		ConnectNodes(treap, ans2->second, LEFT);

		ans->first  = ans2->first;
		ans->second = treap;

		free(ans2);
	}
	else
	{
		double_treap_node_t* ans2 = Split(treap->right, x);
		ConnectNodes(treap, ans2->first, RIGHT);

		ans->first  = treap;
		ans->second = ans2->second;

		free(ans2);
	}

	return ans;
}

// ---------------------------------------------------------------------

static treap_node_t* Merge(treap_node_t* first, treap_node_t* second)
{
	if (first == NULL)
		return second;
	else if (second == NULL)
		return first;
	else if (first->priority < second->priority)
	{
		ConnectNodes(second, Merge(first, second->left), LEFT);
		return second;
	}
	else
	{
		ConnectNodes(first, Merge(first->right, second), RIGHT);
		return first;
	}
}

// ---------------------------------------------------------------------

static treap_node_t* FindNode(treap_t* treap, int x)
{
	treap_node_t* cur = treap->root;

	while (cur != NULL)
	{
		if (cur->key == x)
			return cur;

		if (cur->key > x)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

// ---------------------------------------------------------------------

void PrintTreap(treap_node_t* root)
{
	if (root == NULL)
		return;

	PrintTreap(root->left);

	//printf("([%d] %d {%d} <%d >%d ^%d) ", root, root->key, root->size, root->left, root->right, root->upper);
	printf("%d ", root->key);

	PrintTreap(root->right);
}

// ---------------------------------------------------------------------

void TreapDtor(treap_t* treap)
{
	assert(treap);

	DestructTreap(treap->root);

	free(treap);
};

//---------------------------------------------------------------------------------------

static void ConnectNodes(treap_node_t* parent, treap_node_t* son, const enum Side side)
{
	assert(side == LEFT || side == RIGHT);

	if (side == LEFT)
	{
		parent->left = son;

		if (son != NULL)
			son->upper = parent;
	}
	else
	{
		parent->right = son;

		if (son != NULL)
			son->upper = parent;
	}
}


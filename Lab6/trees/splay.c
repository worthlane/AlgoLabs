#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "splay.h"

static double_splay_node_t* Split(splay_node_t* node, const int key);

static splay_node_t*    NodeCtor(const int key, const splay_node_t* left, const splay_node_t* right, const splay_node_t* upper);
static void             NodeDtor(splay_node_t* node);
static splay_node_t*    InsertNode(splay_node_t* root, splay_node_t* node);

static enum Side
{
	RIGHT,
	LEFT,
};

static void ConnectNodes(splay_node_t* parent, const enum Side side, splay_node_t* son);

static splay_node_t*    LeftZig(splay_node_t* node);
static splay_node_t*    RightZig(splay_node_t* node);
static splay_node_t*    LeftRightZigZag(splay_node_t* node);
static splay_node_t*    RightLeftZigZag(splay_node_t* node);
static splay_node_t*    RightZigZig(splay_node_t* node);
static splay_node_t*    LeftZigZig(splay_node_t* node);
static splay_node_t*    Splay(splay_node_t* root, splay_node_t* node);

static splay_node_t* FindNode(splay_tree_t* tree, const int key);
static splay_node_t* SplayTreePrev(splay_node_t* root, const int key);

static void DestructSplayTree(splay_node_t* root);

static inline splay_node_t* MaxNode(splay_node_t* node1, splay_node_t* node2)
{
	if (node1 == NULL)
		return node2;
	else if (node2 == NULL)
		return node1;

	return (node1->key < node2->key) ? node2 : node1;
}

// =====================================================================

static splay_node_t* NodeCtor(const int key, const splay_node_t* left, const splay_node_t* right, const splay_node_t* upper)
{
	splay_node_t* node = (splay_node_t*) calloc(1, sizeof(splay_node_t));
	assert(node);

	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;

	return node;
}

// ---------------------------------------------------------------------

static void NodeDtor(splay_node_t* node)
{
	assert(node);

    free(node);
}

// ---------------------------------------------------------------------

static void DestructSplayTree(splay_node_t* root)
{
	if (root == NULL)   return;

	DestructSplayTree(root->left);
	DestructSplayTree(root->right);

	NodeDtor(root);
}

// ---------------------------------------------------------------------

splay_tree_t* SplayTreeCtor()
{
	splay_tree_t* tree = calloc(1, sizeof(splay_tree_t));
	assert(tree);

	return tree;
}

// ---------------------------------------------------------------------

void SplayTreeInsert(splay_tree_t* tree, const int key)
{
	assert(tree);

	if (FindNode(tree, key))
		return;

	splay_node_t* node = NodeCtor(key, NULL, NULL, NULL);
	assert(node);

	tree->root = InsertNode(tree->root, node);
}

// ---------------------------------------------------------------------

static splay_node_t* InsertNode(splay_node_t* root, splay_node_t* node)
{
	if (root == NULL)
		return node;

	double_splay_node_t* split = Split(root, node->key);

	ConnectNodes(node, LEFT, split->first);
	ConnectNodes(node, RIGHT, split->second);

	free(split);

	return node;
}


// ---------------------------------------------------------------------

void PrintSplayTree(const splay_node_t* root)
{
	if (root == NULL)
		return;

	PrintSplayTree(root->left);

	//printf("([%d] %d <%d >%d ^%d) ", root, root->key, root->left, root->right, root->upper);
	printf("%d ", root->key);

	PrintSplayTree(root->right);
}

// ---------------------------------------------------------------------

void SplayTreeDtor(splay_tree_t* tree)
{
	assert(tree);

	DestructSplayTree(tree->root);

	free(tree);
};

//---------------------------------------------------------------------------------------

static void ConnectNodes(splay_node_t* parent, const enum Side side, splay_node_t* son)
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

//---------------------------------------------------------------------------------------

static splay_node_t* LeftZig(splay_node_t* node)
{
	splay_node_t* new_root = node->right;
	assert(new_root);

	splay_node_t* parent = node->upper;

	ConnectNodes(node, RIGHT, new_root->left);
	ConnectNodes(new_root, LEFT, node);

	new_root->upper = parent;

	if (parent != NULL)
	{
		if (parent->left == node)
			ConnectNodes(parent, LEFT, new_root);
		else
		{
			assert(parent->right == node);
			ConnectNodes(parent, RIGHT, new_root);
		}
	}

	return new_root;
}

//---------------------------------------------------------------------------------------

static splay_node_t* RightZig(splay_node_t* node)
{
	splay_node_t* new_root = node->left;
	assert(new_root);

	splay_node_t* parent = node->upper;

	ConnectNodes(node, LEFT, new_root->right);
	ConnectNodes(new_root, RIGHT, node);

	new_root->upper = parent;

	if (parent != NULL)
	{
		if (parent->left == node)
			ConnectNodes(parent, LEFT, new_root);
		else
		{
			assert(parent->right == node);
			ConnectNodes(parent, RIGHT, new_root);
		}
	}

	return new_root;
}

//---------------------------------------------------------------------------------------

static splay_node_t* RightLeftZigZag(splay_node_t* node)
{
	ConnectNodes(node, RIGHT, RightZig(node->right));
	return LeftZig(node);
}

//---------------------------------------------------------------------------------------

static splay_node_t* LeftRightZigZag(splay_node_t* node)
{
	ConnectNodes(node, LEFT, LeftZig(node->left));
	return RightZig(node);
}

//---------------------------------------------------------------------------------------

static splay_node_t* RightZigZig(splay_node_t* node)
{
	return RightZig(RightZig(node));
}

//---------------------------------------------------------------------------------------

static splay_node_t* LeftZigZig(splay_node_t* node)
{
	return LeftZig(LeftZig(node));
}

//---------------------------------------------------------------------------------------

static splay_node_t* Splay(splay_node_t* root, splay_node_t* node)
{
	if (node == NULL || node == root)
		return root;

	while (node->upper != NULL)
	{
		splay_node_t* parent      = node->upper;
		splay_node_t* grandparent = parent->upper;

		if (grandparent == NULL)
		{
			if (node == parent->left)
				RightZig(parent);
			else
				LeftZig(parent);
		}
		else
		{
			if (node == parent->left && parent == grandparent->left)
			{
				RightZigZig(grandparent);
			}
			else if (node == parent->right && parent == grandparent->right)
			{
				LeftZigZig(grandparent);
			}
			else if (node == parent->left && parent == grandparent->right)
			{
				RightLeftZigZag(grandparent);
			}
			else
			{
				assert(node == parent->right && parent == grandparent->left);
				LeftRightZigZag(grandparent);
			}
		}
	}
	return node;
}

// ---------------------------------------------------------------------

static splay_node_t* SplayTreePrev(splay_node_t* root, const int key)
{
	splay_node_t* cur = root;

	splay_node_t* max = NULL;

	while (cur != NULL)
	{
		int cur_key = cur->key;

		if (key > cur_key)
		{
			max = MaxNode(max, cur);

			cur = cur->right;
		}
		else
			cur = cur->left;
	}

	return max;
}

// ---------------------------------------------------------------------

static splay_node_t* FindNode(splay_tree_t* tree, const int key)
{
	splay_node_t* cur = tree->root;

	while (cur != NULL)
	{
        int cur_key = cur->key;

		if (cur_key == key)
		{
			tree->root = Splay(tree->root, cur);
			return tree->root;
		}

		if (key < cur_key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

// ---------------------------------------------------------------------

static double_splay_node_t* Split(splay_node_t* root, const int key)
{
	double_splay_node_t* ans = calloc(1, sizeof(double_splay_node_t));
	assert(ans);

	if (root == NULL)
	{
		ans->first = NULL;
		ans->second = NULL;
		return ans;
	}

	splay_node_t* biggest = SplayTreePrev(root, key);

	if (biggest == NULL)
	{
		ans->first  = NULL;
		ans->second = root;
		return ans;
	}

	splay_node_t* new_root = Splay(root, biggest);

	ans->second = new_root->right;
	ans->first  = new_root;

	new_root->right = NULL;

	if (new_root->right != NULL)
		new_root->right->upper = NULL;

	return ans;
}

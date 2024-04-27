#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "avl.h"

static avl_node_t* AVLNodeCtor(const int key, const int height, const avl_node_t* left, const avl_node_t* right, const avl_node_t* upper);
static void        AVLNodeFill(avl_node_t* node, const int key, const int height, const avl_node_t* left, const avl_node_t* right, const avl_node_t* upper);
static avl_node_t* InsertAVLNode(avl_node_t* root, avl_node_t* node);

static enum Side
{
	RIGHT,
	LEFT,
};

static void ConnectAVLNodes(avl_node_t* parent, const enum Side side, avl_node_t* son);

static const int NEXT_MIN_START = 2147483647;
static const int NONE = -1;

static int GetHeight(avl_node_t* node);
static int GetBalance(avl_node_t* node);

static avl_node_t* LeftRotate(avl_node_t* node);
static avl_node_t* RightRotate(avl_node_t* node);
static avl_node_t* BigLeftRotate(avl_node_t* node);
static avl_node_t* BigRightRotate(avl_node_t* node);

static avl_node_t* BalanceAVLNode(avl_node_t* node);

static avl_node_t* FindAVLNode(avl_tree_t* tree, const int x);

static void DestructAVLTree(avl_node_t* root);

static void UpdateHeight(avl_node_t* node);

static inline int Min(const int a, const int b)
{
	return (a > b) ? b : a;
}

static inline int Max(const int a, const int b)
{
	return (a < b) ? b : a;
}

// =====================================================================

static avl_node_t* AVLNodeCtor(const int key, const int height, const avl_node_t* left, const avl_node_t* right, const avl_node_t* upper)
{
	avl_node_t* node = (avl_node_t*) calloc(1, sizeof(avl_node_t));
	assert(node);

	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;
	node->height   = height;

	return node;
}

// ---------------------------------------------------------------------

static void AVLNodeFill(avl_node_t* node, const int key, const int height, const avl_node_t* left, const avl_node_t* right, const avl_node_t* upper)
{
	assert(node);

	node->left     = left;
	node->right    = right;
	node->key      = key;
	node->upper    = upper;
	node->height   = height;
}


// ---------------------------------------------------------------------

static void DestructAVLTree(avl_node_t* root)
{
	if (root == NULL)   return;

	DestructAVLTree(root->left);
	DestructAVLTree(root->right);

	free(root);
}

// ---------------------------------------------------------------------

avl_tree_t* AVLTreeCtor()
{
	avl_tree_t* tree = calloc(1, sizeof(avl_tree_t));
	assert(tree);

	return tree;
}

// ---------------------------------------------------------------------

void AVLTreeInsert(avl_tree_t* tree, const int key)
{
	assert(tree);

	if (FindAVLNode(tree, key))
		return;

	avl_node_t* node = AVLNodeCtor(key, 1, NULL, NULL, NULL);
	assert(node);

	tree->root = InsertAVLNode(tree->root, node);
}

// ---------------------------------------------------------------------

static avl_node_t* InsertAVLNode(avl_node_t* root, avl_node_t* node)
{
	if (root == NULL)
		return node;

	if (node->key < root->key)
		ConnectAVLNodes(root, LEFT, InsertAVLNode(root->left, node));
	else if (node->key > root->key)
		ConnectAVLNodes(root, RIGHT, InsertAVLNode(root->right, node));
	else
		return root;

	avl_node_t* new_root = BalanceAVLNode(root);

	return new_root;
}

// ---------------------------------------------------------------------

static avl_node_t* BalanceAVLNode(avl_node_t* node)
{
	int a_balance = GetBalance(node);                       // for better naming understanding, visit https://neerc.ifmo.ru/wiki/index.php?title=АВЛ-дерево

	if (node->right != NULL && a_balance <= -2)             // left rotate checking
	{
		int b_balance = GetBalance(node->right);

		if (b_balance == 0 || b_balance == -1)
			return LeftRotate(node);

		if (node->right->left != NULL)
		{
			int c_balance = GetBalance(node->right->left);

			if (b_balance == 1 && (c_balance == 0 || c_balance == 1 || c_balance == -1))
				return BigLeftRotate(node);
		}
	}

	if (node->left != NULL && a_balance >= 2)             // right rotate checking
	{
		int b_balance = GetBalance(node->left);

		if (b_balance == 0 || b_balance == 1)
			return RightRotate(node);

		if (node->left->right != NULL)
		{
			int c_balance = GetBalance(node->left->right);

			if (b_balance == -1 && (c_balance == 0 || c_balance == 1 || c_balance == -1))
				return BigRightRotate(node);
		}
	}

	return node;
}

// ---------------------------------------------------------------------

static avl_node_t* FindAVLNode(avl_tree_t* tree, const int x)
{
	avl_node_t* cur = tree->root;

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

void PrintAVLTree(const avl_node_t* root)
{
	if (root == NULL)
		return;

	PrintAVLTree(root->left);

	//printf("([%d] %d {%d} <%d >%d ^%d) ", root, root->key, root->height, root->left, root->right, root->upper);
	printf("%d ", root->key);

	PrintAVLTree(root->right);
}

// ---------------------------------------------------------------------

void AVLTreeDtor(avl_tree_t* tree)
{
	assert(tree);

	DestructAVLTree(tree->root);

	free(tree);
};

//---------------------------------------------------------------------------------------

static void ConnectAVLNodes(avl_node_t* parent, const enum Side side, avl_node_t* son)
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

	UpdateHeight(parent);
}

//---------------------------------------------------------------------------------------

static int GetHeight(avl_node_t* node)
{
	if (node == NULL)
		return 0;

	return node->height;
}

//---------------------------------------------------------------------------------------

static int GetBalance(avl_node_t* node)
{
	if (node == NULL)
		return 0;

	return GetHeight(node->left) - GetHeight(node->right);
}

//---------------------------------------------------------------------------------------

static void UpdateHeight(avl_node_t* node)
{
	if (node == NULL)
		return;

	node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

//---------------------------------------------------------------------------------------

static avl_node_t* LeftRotate(avl_node_t* node)
{
	avl_node_t* new_root = node->right;
	assert(new_root);

	ConnectAVLNodes(node, RIGHT, new_root->left);
	ConnectAVLNodes(new_root, LEFT, node);

	node->height     = Max(GetHeight(node->left),     GetHeight(node->right))     + 1;
	new_root->height = Max(GetHeight(new_root->left), GetHeight(new_root->right)) + 1;

	return new_root;
}

//---------------------------------------------------------------------------------------

static avl_node_t* RightRotate(avl_node_t* node)
{
	avl_node_t* new_root = node->left;
	assert(new_root);

	ConnectAVLNodes(node, LEFT, new_root->right);
	ConnectAVLNodes(new_root, RIGHT, node);

	node->height     = Max(GetHeight(node->left),     GetHeight(node->right))     + 1;
	new_root->height = Max(GetHeight(new_root->left), GetHeight(new_root->right)) + 1;

	return new_root;
}

//---------------------------------------------------------------------------------------

static avl_node_t* BigLeftRotate(avl_node_t* node)
{
	ConnectAVLNodes(node, RIGHT, RightRotate(node->right));
	return LeftRotate(node);
}

//---------------------------------------------------------------------------------------

static avl_node_t* BigRightRotate(avl_node_t* node)
{
	ConnectAVLNodes(node, LEFT, LeftRotate(node->left));
	return RightRotate(node);
}

//---------------------------------------------------------------------------------------

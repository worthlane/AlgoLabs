#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#include "bst.h"

static const int NEXT_NONE = 2147483647;

static bst_node_t* BSTNodeCtor(const int key, const bst_node_t* left, const bst_node_t* right, const bst_node_t* upper);
static bst_node_t* InsertBSTNode(bst_node_t* root, bst_node_t* node);

static enum Side
{
    UNKNOWN,

    LEFT,
    RIGHT,
};

static void ConnectBSTNodes(bst_node_t* parent, const enum Side side, bst_node_t* son);
static void DisconnectSon(bst_node_t* son);
static enum Side WhichSideIsSon(bst_node_t* son);

static void DestructBSTTree(bst_node_t* root);

static bst_node_t* BSTNext(bst_node_t* tree, const int key);

static inline bst_node_t* MinNode(bst_node_t* node1, bst_node_t* node2)
{
	if (node1 == NULL)
		return node2;
	else if (node2 == NULL)
		return node1;

	return (node1->key < node2->key) ? node1 : node2;
}
// -----------------------------------------------------------

static bst_node_t* BSTNodeCtor(const int key, const bst_node_t* left, const bst_node_t* right, const bst_node_t* upper)
{
	bst_node_t* node = (bst_node_t*) calloc(1, sizeof(bst_node_t));
	assert(node);

	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;

	return node;
}

// ---------------------------------------------------------------------

bst_tree_t* BSTTreeCtor()
{
	bst_tree_t* tree = calloc(1, sizeof(bst_tree_t));
	assert(tree);

	return tree;
}

// ---------------------------------------------------------------------

void PrintBSTTree(const bst_node_t* root)
{
	if (root == NULL)
		return;


	PrintBSTTree(root->left);
	//printf("([%d] %d {%d} <%d >%d ^%d) ", root, root->key, root->height, root->left, root->right, root->upper);
	printf("%d ", root->key);

	PrintBSTTree(root->right);
}

// ---------------------------------------------------------------------

void BSTTreeDtor(bst_tree_t* tree)
{
	assert(tree);

	DestructBSTTree(tree->root);

	free(tree);
};

//---------------------------------------------------------------------------------------

static void ConnectBSTNodes(bst_node_t* parent, const enum Side side, bst_node_t* son)
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

static void DisconnectSon(bst_node_t* son)
{

    enum Side side = WhichSideIsSon(son);

    if (side == UNKNOWN)
        return;

    if (side == LEFT)
    {
        son->upper->left = NULL;
        son->upper       = NULL;
    }
    else
    {
        son->upper->right = NULL;
        son->upper        = NULL;
    }
}

// ---------------------------------------------------------------------

static enum Side WhichSideIsSon(bst_node_t* son)
{
    if (son->upper == NULL)
        return UNKNOWN;

    assert(son->upper->left == son || son->upper->right == son);

    if (son->upper->left == son)
        return LEFT;

    return RIGHT;
}

// ---------------------------------------------------------------------

static void DestructBSTTree(bst_node_t* root)
{
	if (root == NULL)   return;

	DestructBSTTree(root->left);
	DestructBSTTree(root->right);

	free(root);
}

// ---------------------------------------------------------------------

static bst_node_t* BSTNext(bst_node_t* root, const int key)
{
	bst_node_t* cur = root;

	bst_node_t* min = NULL;

	while (cur != NULL)
	{
		if (cur->key > key)
		{
			min = MinNode(min, cur);
			cur = cur->left;
		}
		else
			cur = cur->right;
	}

	return min;
}

// ---------------------------------------------------------------------

static bst_node_t* FindNodeInTree(bst_node_t* root, const int key)
{
	bst_node_t* cur = root;

	while (cur != NULL)
	{
		if (cur->key == key)
			return cur;

		if (cur->key > key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

// ---------------------------------------------------------------------

void BSTTreeInsert(bst_tree_t* tree, const int key)
{
    bst_node_t* cur_node = tree->root;

    bst_node_t* inserting = BSTNodeCtor(key, NULL, NULL, NULL);
    assert(inserting);

    if (cur_node == NULL)
    {
        tree->root = inserting;
        return;
    }

    while (cur_node != NULL)
    {
        int cur_key = cur_node->key;

        if (cur_key > key)
        {
            if (cur_node->left != NULL)
                cur_node = cur_node->left;
            else
            {
                ConnectBSTNodes(cur_node, LEFT, inserting);
                return;
            }
        }
        else if (cur_key < key)
        {
            if (cur_node->right != NULL)
                cur_node = cur_node->right;
            else
            {
                ConnectBSTNodes(cur_node, RIGHT, inserting);
                return;
            }
        }
        else
            return;
    }
}

// ---------------------------------------------------------------------

void BSTTreeRemove(bst_tree_t* tree, const int key)
{
    bst_node_t* deleting = FindNodeInTree(tree->root, key);

    if (deleting == NULL)
    {
        return;
    }

    if (deleting->left == NULL && deleting->right == NULL)
    {
        DisconnectSon(deleting);
        free(deleting);
        return;
    }

    if (deleting->left == NULL && deleting->right != NULL)
    {
        enum Side side = WhichSideIsSon(deleting);

        if (side == UNKNOWN)
        {
            tree->root = deleting->right;
            deleting->right->upper = NULL;
        }
        else
            ConnectBSTNodes(deleting->upper, side, deleting->right);

        free(deleting);
    }
    else if (deleting->right == NULL && deleting->left != NULL)
    {
        enum Side side = WhichSideIsSon(deleting);

        if (side == UNKNOWN)
        {
            tree->root = deleting->left;
            deleting->left->upper = NULL;
        }
        else
            ConnectBSTNodes(deleting->upper, side, deleting->right);

        free(deleting);
    }
    else
    {
        bst_node_t* next = BSTNext(tree->root, key);
        deleting->key = next->key;

        enum Side side = WhichSideIsSon(next);

        if (side == LEFT)
            ConnectBSTNodes(next->upper, LEFT, next->right);
        else if (side == RIGHT)
            ConnectBSTNodes(next->upper, RIGHT, next->left);

        free(next);
    }
}

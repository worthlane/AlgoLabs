#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

typedef struct node_t {
	struct node_t* upper;

	int key;
	int height;

	struct node_t* left;
	struct node_t* right;
} node_t;

typedef struct
{
	node_t* root;
} tree_t;

node_t* NodeCtor(const int key, const int height, const node_t* left, const node_t* right, const node_t* upper);
void    NodeFill(node_t* node, const int key, const int height, const node_t* left, const node_t* right, const node_t* upper);
node_t* InsertNode(node_t* root, node_t* node);

enum Side
{
	RIGHT,
	LEFT,
};

void ConnectNodes(node_t* parent, const enum Side side, node_t* son);

static const int NEXT_MIN_START = 2147483647;
static const int NONE = -1;

tree_t* TreeCtor();
void    TreeInsert(tree_t* tree, const int key);
void    TreeDtor(tree_t* tree);
int     TreeNext(tree_t* tree, const int x);

int    GetHeight(node_t* node);
int    GetBalance(node_t* node);

node_t*    LeftRotate(node_t* node);
node_t*    RightRotate(node_t* node);
node_t*    BigLeftRotate(node_t* node);
node_t*    BigRightRotate(node_t* node);

node_t* BalanceNode(node_t* node);

node_t* FindNode(tree_t* tree, const int x);

void PrintTree(const node_t* root);
void DestructTree(node_t* root);

void UpdateHeight(node_t* node);

void GetCommands(size_t N);

static inline void SkipSpaces()
{
	char ch = getc(stdin);

	while (isspace(ch))
		ch = getc(stdin);

	ungetc(ch, stdin);
}

static inline int Min(const int a, const int b)
{
	return (a > b) ? b : a;
}

static inline int Max(const int a, const int b)
{
	return (a < b) ? b : a;
}

// =====================================================================

int main()
{
	srand(time(NULL));

	size_t N = 0;
	assert(scanf("%lu", &N));

	GetCommands(N);

	return 0;
}

// ---------------------------------------------------------------------

void GetCommands(size_t N)
{
	tree_t* tree = TreeCtor();

	int last_k = -1;

	while (N--)
	{
		SkipSpaces();

		int ch = 0;
		int key = 0;
		scanf("%c%d", &ch, &key);

		switch (ch)
		{
		case '?':
		{
			last_k = TreeNext(tree, key);

			if (last_k == NEXT_MIN_START)
				last_k = NONE;

			printf("%d\n", last_k);
			break;
		}

		case '+':
		{
			if (last_k == -1)
				TreeInsert(tree, key);
			else
			{
				TreeInsert(tree, (key + last_k) % 1000000000);
				last_k = -1;
			}

			break;
		}

		default:
		{
			printf("error\n");
			break;
		}
		}
	}

	TreeDtor(tree);
}

// ---------------------------------------------------------------------

node_t* NodeCtor(const int key, const int height, const node_t* left, const node_t* right, const node_t* upper)
{
	node_t* node = (node_t*) calloc(1, sizeof(node_t));
	assert(node);

	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;
	node->height   = height;

	return node;
}

// ---------------------------------------------------------------------

void NodeFill(node_t* node, const int key, const int height, const node_t* left, const node_t* right, const node_t* upper)
{
	assert(node);

	node->left     = left;
	node->right    = right;
	node->key      = key;
	node->upper    = upper;
	node->height   = height;
}


// ---------------------------------------------------------------------

void DestructTree(node_t* root)
{
	if (root == NULL)   return;

	DestructTree(root->left);
	DestructTree(root->right);

	free(root);
}

// ---------------------------------------------------------------------

tree_t* TreeCtor()
{
	tree_t* tree = calloc(1, sizeof(tree_t));
	assert(tree);

	return tree;
}

// ---------------------------------------------------------------------

void TreeInsert(tree_t* tree, const int key)
{
	assert(tree);

	if (FindNode(tree, key))
		return;

	node_t* node = NodeCtor(key, 1, NULL, NULL, NULL);
	assert(node);

	tree->root = InsertNode(tree->root, node);
}

// ---------------------------------------------------------------------

node_t* InsertNode(node_t* root, node_t* node)
{
	if (root == NULL)
		return node;

	if (node->key < root->key)
		ConnectNodes(root, LEFT, InsertNode(root->left, node));
	else if (node->key > root->key)
		ConnectNodes(root, RIGHT, InsertNode(root->right, node));
	else
		return root;

	node_t* new_root = BalanceNode(root);

	return new_root;
}

// ---------------------------------------------------------------------

node_t* BalanceNode(node_t* node)
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

node_t* FindNode(tree_t* tree, const int x)
{
	node_t* cur = tree->root;

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

void PrintTree(const node_t* root)
{
	if (root == NULL)
		return;

	PrintTree(root->left);

	printf("([%d] %d {%d} <%d >%d ^%d) ", root, root->key, root->height, root->left, root->right, root->upper);
	//printf("%d ", root->key);

	PrintTree(root->right);
}

// ---------------------------------------------------------------------

void TreeDtor(tree_t* tree)
{
	assert(tree);

	DestructTree(tree->root);

	free(tree);
};

// ---------------------------------------------------------------------

int TreeNext(tree_t* tree, const int x)
{
	node_t* cur = tree->root;

	int min = NEXT_MIN_START;

	while (cur != NULL)
	{
		if (cur->key >= x)
		{
			min = Min(min, cur->key);
			cur = cur->left;
		}
		else
			cur = cur->right;
	}

	return min;
}

//---------------------------------------------------------------------------------------

void ConnectNodes(node_t* parent, const enum Side side, node_t* son)
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

int GetHeight(node_t* node)
{
	if (node == NULL)
		return 0;

	return node->height;
}

//---------------------------------------------------------------------------------------

int GetBalance(node_t* node)
{
	if (node == NULL)
		return 0;

	return GetHeight(node->left) - GetHeight(node->right);
}

//---------------------------------------------------------------------------------------

void UpdateHeight(node_t* node)
{
	if (node == NULL)
		return;

	node->height = Max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

//---------------------------------------------------------------------------------------

node_t* LeftRotate(node_t* node)
{
	node_t* new_root = node->right;
	assert(new_root);

	ConnectNodes(node, RIGHT, new_root->left);
	ConnectNodes(new_root, LEFT, node);

	node->height     = Max(GetHeight(node->left),     GetHeight(node->right))     + 1;
	new_root->height = Max(GetHeight(new_root->left), GetHeight(new_root->right)) + 1;

	return new_root;
}

//---------------------------------------------------------------------------------------

node_t* RightRotate(node_t* node)
{
	node_t* new_root = node->left;
	assert(new_root);

	ConnectNodes(node, LEFT, new_root->right);
	ConnectNodes(new_root, RIGHT, node);

	node->height     = Max(GetHeight(node->left),     GetHeight(node->right))     + 1;
	new_root->height = Max(GetHeight(new_root->left), GetHeight(new_root->right)) + 1;

	return new_root;
}

//---------------------------------------------------------------------------------------

node_t* BigLeftRotate(node_t* node)
{
	ConnectNodes(node, RIGHT, RightRotate(node->right));
	return LeftRotate(node);
}

//---------------------------------------------------------------------------------------

node_t* BigRightRotate(node_t* node)
{
	ConnectNodes(node, LEFT, LeftRotate(node->left));
	return RightRotate(node);
}

//---------------------------------------------------------------------------------------

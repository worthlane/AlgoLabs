#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

static const size_t MAX_WORD_LEN = 20;

static const int PREV_NONE = -2147483647;
static const int NEXT_NONE = 2147483647;
static const int KTH_NONE =  2147483647;

typedef struct node_t {
	struct node_t* upper;

	int priority;
	int key;
	int size;

	struct node_t* left;
	struct node_t* right;
} node_t;

typedef struct treap_t
{
	node_t* root;
} treap_t;

typedef struct double_node_t
{
	node_t* first;
	node_t* second;
} double_node_t;

node_t* NodeCtor(int priority, int key, int size, node_t* left, node_t* right, node_t* upper);
void    NodeFill(node_t* node, int priority, int key, int size, node_t* left, node_t* right, node_t* upper);

treap_t* TreapCtor();
void     TreapDtor(treap_t* treap);

void           TreapInsert(treap_t* treap, int key);
void           TreapRemove(treap_t* treap, int key);
int            GetKth(node_t* treap, int k);
int            TreapNext(treap_t* treap, int key);
int            TreapPrev(treap_t* treap, int key);
double_node_t* Split(node_t* treap, int x);
node_t*        Merge(node_t* first, node_t* second);
node_t*        FindNode(treap_t* treap, int x);

void PrintTree(node_t* root);

enum Side
{
	RIGHT,
	LEFT,
};

void ConnectNodes(node_t* parent, node_t* son, const enum Side side);
void UpdateNodeSize(node_t* node);

static inline int Min(int a, int b)
{
	return (a > b) ? b : a;
}

static inline int Max(int a, int b)
{
	return (a > b) ? a : b;
}

void    DestructTree(node_t* root);

typedef enum {
	INSERT,
	DELETE,
	EXISTS,
	NEXT,
	PREV,
	KTH,

	UNKNOWN,
} command_t;

void HandleCommands(treap_t* treap);
command_t DefineCommand(char* cmd);

// =====================================================================

int main()
{
	srand(time(NULL));

	treap_t* treap = TreapCtor();

	HandleCommands(treap);

	TreapDtor(treap);

	return 0;
}

// ---------------------------------------------------------------------

void HandleCommands(treap_t* treap)
{
	assert(treap);

	char cmd[MAX_WORD_LEN] = {};
	int  x = 0;
	command_t command_code = UNKNOWN;

	while (true)
	{
		if(scanf("%19s", cmd) != 1)
			return;

		assert(scanf("%d", &x));

		command_code = DefineCommand(cmd);

		switch (command_code)
		{
		case (INSERT):
			TreapInsert(treap, x);
			break;

		case (DELETE):
			TreapRemove(treap, x);
			break;

		case (EXISTS):
		{
			node_t* node = FindNode(treap, x);
			if (node == NULL)
				printf("false\n");
			else
				printf("true\n");
			break;
		}

		case (NEXT):
		{
			int num = TreapNext(treap, x);
			if (num == NEXT_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}


		case (PREV):
		{
			int num = TreapPrev(treap, x);
			if (num == PREV_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}

		case (KTH):
		{
			int num = GetKth(treap->root, x + 1);   // +1 cuz of numeration from zero
			if (num == KTH_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}

		default:
			return;
		}
	}
}

// ---------------------------------------------------------------------

command_t DefineCommand(char* cmd)
{
	static const char* insert = "insert";
	static const char* delete = "delete";
	static const char* exists = "exists";
	static const char* next   = "next";
	static const char* prev   = "prev";
	static const char* kth    = "kth";

	if (!strncmp(cmd, insert, MAX_WORD_LEN))
		return INSERT;
	else if (!strncmp(cmd, delete, MAX_WORD_LEN))
		return DELETE;
	else if (!strncmp(cmd, exists, MAX_WORD_LEN))
		return EXISTS;
	else if (!strncmp(cmd, next, MAX_WORD_LEN))
		return NEXT;
	else if (!strncmp(cmd, prev, MAX_WORD_LEN))
		return PREV;
	else if (!strncmp(cmd, kth, MAX_WORD_LEN))
		return KTH;
	else
		return UNKNOWN;
}


// ---------------------------------------------------------------------

node_t* NodeCtor(int priority, int key, int size, node_t* left, node_t* right, node_t* upper)
{
	node_t* node = (node_t*) calloc(1, sizeof(node_t));
	assert(node);

	node->priority = priority;
	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;
	node->size     = size;

	return node;
}

// ---------------------------------------------------------------------

void NodeFill(node_t* node, int priority, int key, int size, node_t* left, node_t* right, node_t* upper)
{
	assert(node);

	node->left     = left;
	node->right    = right;
	node->key      = key;
	node->priority = priority;
	node->upper    = upper;
	node->size     = size;
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

	int priority = rand();

	node_t* node = NodeCtor(priority, key, 0, NULL, NULL, NULL);
	assert(node);

	if (treap->root == NULL)
	{
		treap->root = node;
		return;
	}

	double_node_t* split = Split(treap->root, key);

	node_t* merge = Merge(split->first, node);
	treap->root = Merge(merge, split->second);

	free(split);
}

// ---------------------------------------------------------------------

void TreapRemove(treap_t* treap, int key)
{
	assert(treap);

	node_t* removing = FindNode(treap, key);

	if (removing == NULL)
		return;

	node_t* replace = Merge(removing->left, removing->right);

	node_t* parent = removing->upper;

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

double_node_t* Split(node_t* treap, int x)
{
	double_node_t* splitted_nodes = calloc(1, sizeof(double_node_t));
	assert(splitted_nodes);

	if (treap == NULL)
	{
		splitted_nodes->first = NULL;
		splitted_nodes->second = NULL;
	}
	else if (x < treap->key)
	{
		double_node_t* splitted_subtree = Split(treap->left, x);
		ConnectNodes(treap, splitted_subtree->second, LEFT);

		splitted_nodes->first  = splitted_subtree->first;
		splitted_nodes->second = treap;

		free(splitted_subtree);
	}
	else
	{
		double_node_t* splitted_subtree = Split(treap->right, x);
		ConnectNodes(treap, splitted_subtree->first, RIGHT);

		splitted_nodes->first  = treap;
		splitted_nodes->second = splitted_subtree->second;

		free(splitted_subtree);
	}

	return splitted_nodes;
}

// ---------------------------------------------------------------------

node_t* Merge(node_t* first, node_t* second)
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

node_t* FindNode(treap_t* treap, int x)
{
	node_t* current = treap->root;

	while (current != NULL)
	{
		if (current->key == x)
			return current;

		if (current->key > x)
			current = current->left;
		else
			current = current->right;
	}

	return current;
}

// ---------------------------------------------------------------------

int TreapNext(treap_t* treap, int x)
{
	node_t* current = treap->root;

	int min = NEXT_NONE;

	while (current != NULL)
	{
		if (current->key > x)
		{
			min = Min(min, current->key);
			current = current->left;
		}
		else
			current = current->right;
	}

	return min;
}

// ---------------------------------------------------------------------

int TreapPrev(treap_t* treap, int x)
{
	node_t* current = treap->root;

	int max = PREV_NONE;

	while (current != NULL)
	{

		if (current->key < x)
		{
			max = Max(max, current->key);
			current = current->right;
		}
		else
			current = current->left;
	}

	return max;
}

// ---------------------------------------------------------------------

void PrintTree(node_t* root)
{
	if (root == NULL)
		return;

	PrintTree(root->left);

	//printf("([%d] %d {%d} <%d >%d ^%d) ", root, root->key, root->size, root->left, root->right, root->upper);
	printf("%d ", root->key);

	PrintTree(root->right);
}

// ---------------------------------------------------------------------

void TreapDtor(treap_t* treap)
{
	assert(treap);

	DestructTree(treap->root);

	free(treap);
};

//---------------------------------------------------------------------------------------

void ConnectNodes(node_t* parent, node_t* son, const enum Side side)
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

	UpdateNodeSize(parent);
}

//---------------------------------------------------------------------------------------

void UpdateNodeSize(node_t* node)
{
	if (node == NULL)
		return;

	int left_size  = 0;
	int right_size = 0;

	node_t* left  = node->left;
	node_t* right = node->right;

	if (left != NULL)
		left_size = left->size;
	if (right != NULL)
		right_size = right->size;

	node->size = 1 + left_size + right_size;
}

//---------------------------------------------------------------------------------------

int GetKth(node_t* treap, int k)
{
	if (treap == NULL)
		return KTH_NONE;

	int left_size = 0;

	if (treap->left != NULL)
		left_size = treap->left->size;

	if (left_size == k - 1)
		return treap->key;
	else if (left_size > k - 1)
		return GetKth(treap->left, k);
	else
		return GetKth(treap->right, k - left_size - 1);
}


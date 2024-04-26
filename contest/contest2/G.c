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

node_t* NodeCtor(int prior, int key, int size, node_t* left, node_t* right, node_t* upper);
void    NodeFill(node_t* node, int prior, int key, int size, node_t* left, node_t* right, node_t* upper);

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

void GetCommand();
command_t DefineCommand(char* cmd);

// =====================================================================

int main()
{
	srand(time(NULL));

	GetCommand();

	return 0;
}

// ---------------------------------------------------------------------

void GetCommand()
{
	char cmd[MAX_WORD_LEN] = {};
	int  x = 0;
	command_t command_code = UNKNOWN;

	treap_t* treap = TreapCtor();
	assert(treap);

	while (true)
	{
		if(scanf("%s", cmd) != 1)
			return;

		command_code = DefineCommand(cmd);

		switch (command_code)
		{
		case (INSERT):
			assert(scanf("%d", &x));
			TreapInsert(treap, x);
			break;

		case (DELETE):
			assert(scanf("%d", &x));
			TreapRemove(treap, x);
			break;

		case (EXISTS):
		{
			assert(scanf("%d", &x));
			node_t* node = FindNode(treap, x);
			if (node == NULL)
				printf("false\n");
			else
				printf("true\n");
			break;
		}

		case (NEXT):
		{
			assert(scanf("%d", &x));
			int num = TreapNext(treap, x);
			if (num == NEXT_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}


		case (PREV):
		{
			assert(scanf("%d", &x));
			int num = TreapPrev(treap, x);
			if (num == PREV_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}

		case (KTH):
		{
			assert(scanf("%d", &x));
			int num = GetKth(treap->root, x + 1);   // +1 cuz of numeration from zero
			if (num == KTH_NONE)
				printf("none\n");
			else
				printf("%d\n", num);
			break;
		}

		default:
			TreapDtor(treap);
			return;
		}
	}

	TreapDtor(treap);
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

node_t* NodeCtor(int prior, int key, int size, node_t* left, node_t* right, node_t* upper)
{
	node_t* node = (node_t*) calloc(1, sizeof(node_t));
	assert(node);

	node->priority = prior;
	node->key      = key;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;
	node->size     = size;

	return node;
}

// ---------------------------------------------------------------------

void NodeFill(node_t* node, int prior, int key, int size, node_t* left, node_t* right, node_t* upper)
{
	assert(node);

	node->left     = left;
	node->right    = right;
	node->key      = key;
	node->priority = prior;
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

	int prior = rand();

	node_t* node = NodeCtor(prior, key, 0, NULL, NULL, NULL);
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
	double_node_t* ans = calloc(1, sizeof(double_node_t));
	assert(ans);

	if (treap == NULL)
	{
		ans->first = NULL;
		ans->second = NULL;
	}
	else if (x < treap->key)
	{
		double_node_t* ans2 = Split(treap->left, x);
		ConnectNodes(treap, ans2->second, LEFT);

		ans->first  = ans2->first;
		ans->second = treap;

		free(ans2);
	}
	else
	{
		double_node_t* ans2 = Split(treap->right, x);
		ConnectNodes(treap, ans2->first, RIGHT);

		ans->first  = treap;
		ans->second = ans2->second;

		free(ans2);
	}

	return ans;
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
	node_t* cur = treap->root;

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

int TreapNext(treap_t* treap, int x)
{
	node_t* cur = treap->root;

	int min = NEXT_NONE;

	while (cur != NULL)
	{
		if (cur->key > x)
		{
			min = Min(min, cur->key);
			cur = cur->left;
		}
		else
			cur = cur->right;
	}

	return min;
}

// ---------------------------------------------------------------------

int TreapPrev(treap_t* treap, int x)
{
	node_t* cur = treap->root;

	int max = PREV_NONE;

	while (cur != NULL)
	{

		if (cur->key < x)
		{
			max = Max(max, cur->key);
			cur = cur->right;
		}
		else
			cur = cur->left;
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


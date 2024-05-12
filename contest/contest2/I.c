#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

static const size_t MAX_WORD_LEN = 500;

typedef struct node_t {
	struct node_t* upper;

	char* key;
	char* val;

	struct node_t* left;
	struct node_t* right;
} node_t;

typedef struct
{
	node_t* root;
} tree_t;

typedef struct double_node_t
{
	node_t* first;
	node_t* second;
} double_node_t;

double_node_t* Split(node_t* node, char key[MAX_WORD_LEN]);

node_t* NodeCtor(char key[MAX_WORD_LEN], char val[MAX_WORD_LEN], const node_t* left, const node_t* right, const node_t* upper);
void    NodeDtor(node_t* node);
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
void    TreeInsert(tree_t* tree, char key[MAX_WORD_LEN], char val[MAX_WORD_LEN]);
void    TreeDtor(tree_t* tree);

node_t*    LeftZig(node_t* node);
node_t*    RightZig(node_t* node);
node_t*    LeftRightZigZag(node_t* node);
node_t*    RightLeftZigZag(node_t* node);
node_t*    RightZigZig(node_t* node);
node_t*    LeftZigZig(node_t* node);
node_t*    Splay(node_t* root, node_t* node);

node_t* FindNode(tree_t* tree, char key[MAX_WORD_LEN]);
node_t* TreePrev(node_t* root, char key[MAX_WORD_LEN]);

void PrintTree(const node_t* root);
void DestructTree(node_t* root);

static inline node_t* MaxNode(node_t* node1, node_t* node2)
{
	if (node1 == NULL)
		return node2;
	else if (node2 == NULL)
		return node1;

	return (strncmp(node2->key, node1->key, MAX_WORD_LEN)) ? node2 : node1;
}

static inline void SkipSpaces()
{
	char ch = getc(stdin);

	while (isspace(ch))
		ch = getc(stdin);

	ungetc(ch, stdin);
}

void FillTrees(tree_t* name_tree, tree_t* surname_tree, const size_t N);
void FindWords(tree_t* name_tree, tree_t* surname_tree, const size_t cmd_amt);

// =====================================================================

int main()
{
	srand(time(NULL));

	tree_t* name_tree = TreeCtor();
	tree_t* surname_tree = TreeCtor();

	size_t N = 0;
	assert(scanf("%lu", &N));

	FillTrees(name_tree, surname_tree, N);

	size_t cmd_amt = 0;
	assert(scanf("%lu", &cmd_amt));

	FindWords(name_tree, surname_tree, cmd_amt);

	TreeDtor(name_tree);
	TreeDtor(surname_tree);

	return 0;
}

// --------------------------------------------------------------------

void FillTrees(tree_t* name_tree, tree_t* surname_tree, const size_t N)
{
	char name[MAX_WORD_LEN] = {};
	char surname[MAX_WORD_LEN] = {};

	for (size_t i = 0; i < N; i++)
	{
		assert(scanf("%499s%499s", name, surname));

		TreeInsert(name_tree, name, surname);
		TreeInsert(surname_tree, surname, name);
	}
}

// --------------------------------------------------------------------

void FindWords(tree_t* name_tree, tree_t* surname_tree, const size_t cmd_amt)
{
	char word[MAX_WORD_LEN] = {};

	for (size_t i = 0; i < cmd_amt; i++)
	{
		assert(scanf("%499s", word));

		node_t* node = FindNode(surname_tree, word);

		if (node == NULL)
			node = FindNode(name_tree, word);

		assert(node);


		printf("%s\n", node->val);
	}
}



// ---------------------------------------------------------------------

node_t* NodeCtor(char key[MAX_WORD_LEN], char val[MAX_WORD_LEN], const node_t* left, const node_t* right, const node_t* upper)
{
	node_t* node = (node_t*) calloc(1, sizeof(node_t));
	assert(node);

	char* node_key = calloc(MAX_WORD_LEN, sizeof(char));
	assert(node_key);
	char* node_val = calloc(MAX_WORD_LEN, sizeof(char));
	assert(node_val);

	assert(memcpy(node_key, key, MAX_WORD_LEN));
	assert(memcpy(node_val, val, MAX_WORD_LEN));

	node->key      = node_key;
	node->val      = node_val;
	node->left     = left;
	node->right    = right;
	node->upper    = upper;

	return node;
}

// ---------------------------------------------------------------------

void NodeDtor(node_t* node)
{
	assert(node);

	free(node->val);
	free(node->key);
}

// ---------------------------------------------------------------------

void DestructTree(node_t* root)
{
	if (root == NULL)   return;

	DestructTree(root->left);
	DestructTree(root->right);

	NodeDtor(root);
}

// ---------------------------------------------------------------------

tree_t* TreeCtor()
{
	tree_t* tree = calloc(1, sizeof(tree_t));
	assert(tree);

	return tree;
}

// ---------------------------------------------------------------------

void TreeInsert(tree_t* tree, char key[MAX_WORD_LEN], char val[MAX_WORD_LEN])
{
	assert(tree);

	if (FindNode(tree, key))
		return;

	node_t* node = NodeCtor(key, val, NULL, NULL, NULL);
	assert(node);

	tree->root = InsertNode(tree->root, node);
}

// ---------------------------------------------------------------------

node_t* InsertNode(node_t* root, node_t* node)
{
	if (root == NULL)
		return node;

	double_node_t* split = Split(root, node->key);

	ConnectNodes(node, LEFT, split->first);
	ConnectNodes(node, RIGHT, split->second);

	free(split);

	return node;
}


// ---------------------------------------------------------------------

void PrintTree(const node_t* root)
{
	if (root == NULL)
		return;

	PrintTree(root->left);

	printf("([%d] %s %s <%d >%d ^%d) ", root, root->key, root->val, root->left, root->right, root->upper);
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
}

//---------------------------------------------------------------------------------------

node_t* LeftZig(node_t* node)
{
	node_t* new_root = node->right;
	assert(new_root);

	node_t* parent = node->upper;

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

node_t* RightZig(node_t* node)
{
	node_t* new_root = node->left;
	assert(new_root);

	node_t* parent = node->upper;

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

node_t* RightLeftZigZag(node_t* node)
{
	ConnectNodes(node, RIGHT, RightZig(node->right));
	return LeftZig(node);
}

//---------------------------------------------------------------------------------------

node_t* LeftRightZigZag(node_t* node)
{
	ConnectNodes(node, LEFT, LeftZig(node->left));
	return RightZig(node);
}

//---------------------------------------------------------------------------------------

node_t* RightZigZig(node_t* node)
{
	return RightZig(RightZig(node));
}

//---------------------------------------------------------------------------------------

node_t* LeftZigZig(node_t* node)
{
	return LeftZig(LeftZig(node));
}

//---------------------------------------------------------------------------------------

node_t* Splay(node_t* root, node_t* node)
{
	if (node == NULL || node == root)
		return root;

	while (node->upper != NULL)
	{
		node_t* parent      = node->upper;
		node_t* grandparent = parent->upper;

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

node_t* TreePrev(node_t* root, char key[MAX_WORD_LEN])
{
	node_t* cur = root;

	node_t* max = NULL;

	while (cur != NULL)
	{
		int compare = strncmp(key, cur->key, MAX_WORD_LEN);

		if (compare > 0)
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

node_t* FindNode(tree_t* tree, char key[MAX_WORD_LEN])
{
	node_t* cur = tree->root;

	while (cur != NULL)
	{
		int compare = strncmp(key, cur->key, MAX_WORD_LEN);

		if (compare == 0)
		{
			tree->root = Splay(tree->root, cur);
			return tree->root;
		}

		if (compare < 0)
			cur = cur->left;
		else
			cur = cur->right;
	}

	return cur;
}

// ---------------------------------------------------------------------

double_node_t* Split(node_t* root, char key[MAX_WORD_LEN])
{
	double_node_t* ans = calloc(1, sizeof(double_node_t));
	assert(ans);

	if (root == NULL)
	{
		ans->first = NULL;
		ans->second = NULL;
		return ans;
	}

	node_t* biggest = TreePrev(root, key);

	if (biggest == NULL)
	{
		ans->first  = NULL;
		ans->second = root;
		return ans;
	}

	node_t* new_root = Splay(root, biggest);

	ans->second = new_root->right;
	ans->first  = new_root;

	new_root->right = NULL;

	if (new_root->right != NULL)
		new_root->right->upper = NULL;

	return ans;
}

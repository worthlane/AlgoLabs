#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem_t
{
	int data;
	int min;        // I accidentally implemented the stack at the minimums
};

struct Stack_t
{
	struct Elem_t* data;

	size_t size;
	size_t capacity;
};

struct Queue_t
{
	struct Stack_t* in_stk;
	struct Stack_t* out_stk;

	size_t size;
};

enum Commands
{
	ENQUEUE,
	DEQUEUE,
	FRONT,
	SIZE,
	CLEAR,
	MIN,
	POP,
	PUSH,
	BACK,
	EXIT
};

static const int RET_FAILURE = 2e9;

static const          size_t MIN_CAPACITY = 16;
static const          size_t MAX_CMD_LEN  = 16;

int  GetCommand(const char* cmd);
void DoCommand(struct Stack_t* dq, const int cmd);

void        StackCtor(struct Stack_t* stk, const size_t capacity);
void        StackDtor(struct Stack_t* stk);
void        StackPush(struct Stack_t* stk, const int value);
void        StackRealloc(struct Stack_t* stk, size_t new_capacity);
void        StackClear(struct Stack_t* stk);
int    StackPop(struct Stack_t* stk);
int    StackBack(struct Stack_t* stk);
int    StackMin(struct Stack_t* stk);

void        QueueCtor(struct Queue_t* dq);
void        QueueDtor(struct Queue_t* dq);

int    Min(int a, int b);


// =====================================================================

int main()
{
	struct Stack_t stk = {};

	StackCtor(&stk, MIN_CAPACITY);

	while (true)
	{
		char cmd[MAX_CMD_LEN] = {};
		scanf("%s", cmd);

		int cmd_id = GetCommand(cmd);

		DoCommand(&stk, cmd_id);

		if (cmd_id == EXIT)
			break;
	}

    StackDtor(&stk);

	return 0;
}

// ---------------------------------------------------------------------

int GetCommand(const char* cmd)
{
	if (!strncmp(cmd, "push", MAX_CMD_LEN))
		return PUSH;
	else if (!strncmp(cmd, "pop", MAX_CMD_LEN))
		return POP;
	else if (!strncmp(cmd, "back", MAX_CMD_LEN))
		return BACK;
	else if (!strncmp(cmd, "size", MAX_CMD_LEN))
		return SIZE;
	else if (!strncmp(cmd, "clear", MAX_CMD_LEN))
		return CLEAR;
	else if (!strncmp(cmd, "exit", MAX_CMD_LEN))
		return EXIT;
	else
		abort();

}

// ---------------------------------------------------------------------

void DoCommand(struct Stack_t* stk, const int cmd)
{
	switch (cmd)
	{
	case BACK:
		if (stk->size == 0)
		{
			printf("error\n");
			break;
		}

		printf("%d\n", StackBack(stk));
		break;
	case CLEAR:
		StackClear(stk);
		printf("ok\n");
		break;
	case POP:
		if (stk->size == 0)
		{
			printf("error\n");
			break;
		}

		printf("%d\n", StackPop(stk));
		break;
	case PUSH:
	{
		int value = 0;

		if (!scanf("%d", &value))
			abort();

		StackPush(stk, value);
		printf("ok\n");
		break;
	}
	case SIZE:
		printf("%d\n", stk->size);
		break;
	case EXIT:
		printf("bye\n");
		break;
	default:
		abort();
	}
}

// ---------------------------------------------------------------------

void StackCtor(struct Stack_t* stk, const size_t capacity)
{
	assert(stk);

	struct Elem_t* data      = NULL;
	size_t         data_size = capacity * sizeof(struct Elem_t);

	data = (struct Elem_t*) calloc(data_size, 1);

	if (data == NULL)
		abort();

	stk->data     = data;
	stk->size     = 0;
	stk->capacity = capacity;
}

//-----------------------------------------------------------------------------------------------------

void StackDtor(struct Stack_t* stk)
{
	assert(stk);

	free(stk->data);

	stk->data     = NULL;
	stk->size     = 0;
	stk->capacity = 0;
}

//-----------------------------------------------------------------------------------------------------

void StackPush(struct Stack_t* stk, const int value)
{
	assert(stk);
	assert(stk->data);

	if (stk->capacity == stk->size)
		StackRealloc(stk, 2 * stk->capacity);

	(stk->data)[(stk->size)].data = value;
	if (stk->size == 0)
		(stk->data)[(stk->size)].min  = value;
	else
		(stk->data)[(stk->size)].min  = Min(value, (stk->data)[(stk->size - 1)].min);

	stk->size++;

}

//-----------------------------------------------------------------------------------------------------

void StackRealloc(struct Stack_t* stk, size_t new_capacity)
{
	assert(stk);

	if (new_capacity <= MIN_CAPACITY)
		new_capacity = MIN_CAPACITY;

	struct Elem_t* data     = stk->data;
	size_t         new_size = new_capacity * sizeof(struct Elem_t);

	struct Elem_t* temp = (struct Elem_t*) realloc(data, new_size);

	if (temp == NULL)
		abort();
	else
		data = temp;

	stk->data     = data;
	stk->capacity = new_capacity;
}

//-----------------------------------------------------------------------------------------------------

int StackPop(struct Stack_t* stk)
{
	assert(stk);
	assert(stk->data);

	if (stk->size == 0)
		return RET_FAILURE;

	struct Elem_t* data_arr = stk->data;
	size_t         stk_size = stk->size;

	int last_elem = data_arr[--(stk->size)].data;

	data_arr[stk_size].data = 0;
	data_arr[stk_size].min  = 0;

	if (stk_size <= stk->capacity / 4)
		StackRealloc(stk, stk->capacity / 4);

	return last_elem;
}

//-----------------------------------------------------------------------------------------------------

int StackBack(struct Stack_t* stk)
{
	assert(stk);
	assert(stk->data);

	if (stk->size == 0)
		return RET_FAILURE;

	int last_elem = (stk->data)[stk->size - 1].data;

	return last_elem;
}

//-----------------------------------------------------------------------------------------------------

int StackMin(struct Stack_t* stk)
{
	assert(stk);
	assert(stk->data);

	if (stk->size == 0)
		return RET_FAILURE;

	int min = (stk->data)[stk->size - 1].min;

	return min;
}

//-----------------------------------------------------------------------------------------------------

void StackClear(struct Stack_t* stk)
{
	assert(stk);

	StackDtor(stk);
	StackCtor(stk, MIN_CAPACITY);
}

// ---------------------------------------------------------------------

void QueueCtor(struct Queue_t* dq)
{
	assert(dq);

	struct Stack_t* in_stk  = (struct Stack_t*) calloc(1, sizeof(struct Stack_t));
	struct Stack_t* out_stk = (struct Stack_t*) calloc(1, sizeof(struct Stack_t));
	assert(in_stk);
	assert(out_stk);

	StackCtor(in_stk, MIN_CAPACITY);
	StackCtor(out_stk, MIN_CAPACITY);

	dq->in_stk  = in_stk;
	dq->out_stk = out_stk;
}

//-----------------------------------------------------------------------------------------------------

void QueueDtor(struct Queue_t* dq)
{
	assert(dq);

	StackDtor(dq->in_stk);
	StackDtor(dq->out_stk);

	free(dq->in_stk);
	free(dq->out_stk);
}

//-----------------------------------------------------------------------------------------------------

int Min(const int a, const int b)
{
	if (a < b)
		return a;
	else
		return b;
}



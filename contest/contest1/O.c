#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>

static const size_t MIN_CAPACITY = 16;
static const size_t MAX_CMD_LEN  = 16;

struct Elem_t
{
	long int data;
	int      order;
};

struct MinHeap
{
	struct Elem_t*  array;
	size_t          size;
	size_t          capacity;
};

static inline void Swap(struct Elem_t* elem1, struct Elem_t* elem2)
{
	struct Elem_t temp = *elem1;
	*elem1             = *elem2;
	*elem2             = temp;
}

void SiftUp(struct MinHeap* heap, size_t index);
void SiftDown(struct MinHeap* heap, size_t index);

void        HeapCtor(struct MinHeap* heap, const size_t capacity);
void        HeapInsert(struct MinHeap* heap, const long int val, const int order);
void        HeapRealloc(struct MinHeap* heap, size_t new_capacity);
void        HeapExtractMin(struct MinHeap* heap);
void        HeapDecrease(struct MinHeap* heap, const int order, const int delta);
void        HeapDtor(struct MinHeap* heap);
long int    HeapGetMin(struct MinHeap* heap);


enum Commands
{
	INSERT,
	GETMIN,
	EXTRACT,
	DECREASE
};


int  GetCommand(const char* cmd);
void DoCommand(struct MinHeap* heap, int cmd, const int order);


// =====================================================================

int main()
{
	int q = 0;
	scanf("%d", &q);

	struct MinHeap heap = {};
	HeapCtor(&heap, MIN_CAPACITY);

	for (int order = 1; order <= q; order++)
	{
		char cmd[MAX_CMD_LEN] = {};
		scanf("%s", cmd);

		int cmd_id = GetCommand(cmd);

		DoCommand(&heap, cmd_id, order);
	}

	HeapDtor(&heap);

	return 0;
}

// ---------------------------------------------------------------------

int GetCommand(const char* cmd)
{
	if (!strncmp(cmd, "decreaseKey", MAX_CMD_LEN))
		return DECREASE;
	else if (!strncmp(cmd, "getMin", MAX_CMD_LEN))
		return GETMIN;
	else if (!strncmp(cmd, "extractMin", MAX_CMD_LEN))
		return EXTRACT;
	else if (!strncmp(cmd, "insert", MAX_CMD_LEN))
		return INSERT;
	else
		abort();

}

// ---------------------------------------------------------------------

void DoCommand(struct MinHeap* heap, int cmd, const int order)
{
	switch (cmd)
	{
	case GETMIN:
		printf("%ld\n", HeapGetMin(heap));
		break;
	case DECREASE:
	{
		int      i     = 0;
		long int delta = 0;

		if (!scanf("%d%ld", &i, &delta))
			abort();

		HeapDecrease(heap, i, delta);

		break;
	}
	case EXTRACT:
		HeapExtractMin(heap);
		break;
	case INSERT:
	{
		long int value = 0;

		if (!scanf("%ld", &value))
			abort();

		HeapInsert(heap, value, order);

		break;
	}
	default:
		abort();
	}
}

// ---------------------------------------------------------------------

void HeapCtor(struct MinHeap* heap, const size_t capacity)
{
	assert(heap);

	struct Elem_t* array = (struct Elem_t*) calloc(capacity, sizeof(struct Elem_t));
	assert(array);

	heap->array    = array;
	heap->size     = 0;
	heap->capacity = capacity;
}

// ---------------------------------------------------------------------

void HeapDtor(struct MinHeap* heap)
{
	assert(heap);

	free(heap->array);
}

// ---------------------------------------------------------------------

void HeapInsert(struct MinHeap* heap, const long int val, const int order)
{
	assert(heap);

	if (heap->capacity == heap->size)
		HeapRealloc(heap, 2 * heap->capacity);

	heap->array[heap->size].data  = val;
	heap->array[heap->size].order = order;
	SiftUp(heap, heap->size);
	heap->size++;
}

//-----------------------------------------------------------------------------------------------------

void HeapRealloc(struct MinHeap* heap, size_t new_capacity)
{
	assert(heap);

	if (new_capacity <= MIN_CAPACITY)
		new_capacity = MIN_CAPACITY;

	struct Elem_t*  data     = heap->array;
	size_t          new_size = new_capacity * sizeof(struct Elem_t);

	struct Elem_t* temp = (struct Elem_t*) realloc(data, new_size);

	if (temp == NULL)
		abort();
	else
		data = temp;

	heap->array    = data;
	heap->capacity = new_capacity;
}

// ---------------------------------------------------------------------

void HeapExtractMin(struct MinHeap* heap)
{
	assert(heap);

	Swap(&heap->array[0], &heap->array[heap->size - 1]);
	heap->size--;

	SiftDown(heap, 0);

	if (heap->size <= heap->capacity / 4)
		HeapRealloc(heap, heap->capacity / 2);
}

// ---------------------------------------------------------------------

void HeapDecrease(struct MinHeap* heap, const int order, const int delta)
{
	assert(heap);

	int index = -1;

	for (int i = 0; i < heap->size; i++)
	{
		if (order == heap->array[i].order)
			index = i;
	}

	assert(index != -1);

	heap->array[index].data -= delta;
	SiftUp(heap, index);
}

// ---------------------------------------------------------------------

void SiftUp(struct MinHeap* heap, size_t index)
{
	assert(heap);

	while (index != 0)
	{
		size_t parent = (index - 1) / 2;

		if (heap->array[parent].data > heap->array[index].data)
		{
			Swap(&heap->array[parent], &heap->array[index]);
			index = parent;
		}
		else
			return;
	}
}

// ---------------------------------------------------------------------

void SiftDown(struct MinHeap* heap, size_t index)
{
	assert(heap);

	while (2 * index + 1 < heap->size)
	{
		int left  = 2 * index + 1;
		int right = 2 * index + 2;
		int j     = left;

		if (right < heap->size && heap->array[left].data > heap->array[right].data)
			j = right;

		if (heap->array[index].data <= heap->array[j].data)
			break;

		Swap(&heap->array[index], &heap->array[j]);
		index = j;
	}
}

// ---------------------------------------------------------------------

long int HeapGetMin(struct MinHeap* heap)
{
	assert(heap);

	return heap->array[0].data;
}


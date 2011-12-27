#define PARENT(x) (((x) - 1) >> 1)
#define LEFT(x)   (((x) << 1) + 1)
#define RIGHT(x)  (((x) << 1) + 2)

typedef struct {
	Node **nodes;
	int count;
} minHeap;

void moveNode(Node **nodes, int from, int to) {
	nodes[to] = nodes[from];
	nodes[to]->hIdx = to;
}

/**
 * Move node up if needed to maintain heap property
 */
void heapifyUp(minHeap* heap, int idx) {
	Node **h = heap->nodes;
	Node *n = h[idx];
	int parent = PARENT(idx);
	while(idx > 0 && n->value < h[parent]->value) {
		moveNode(h, parent, idx);
		idx = parent;
		parent = PARENT(idx);
	}
	h[idx] = n;
	h[idx]->hIdx = idx;
}

/**
 * Make sure the subtree rooted at idx is a heap
 * Used after remove
 */
void heapifyDown(minHeap* heap, int idx) {
	Node **h = heap->nodes;
	Node *n = h[idx];

	while(true) {
		int l = LEFT(idx);
		int r = RIGHT(idx);
		ull min; int minidx;
		if(r < heap->count) {
			int lv = h[l]->value;
			int rv = h[r]->value;

			if(lv < rv) {
				min = lv;
				minidx = l;
			} else {
				min = rv;
				minidx = r;
			}
		} else if(l < heap->count) {
			min = h[l]->value;
			minidx = l;
		} else {
			break;
		}

		if(n->value < min) break;

		moveNode(h, minidx, idx);
		idx = minidx;
	}

	n->hIdx = idx;
	h[idx] = n;
}

void insertHeap(minHeap* heap, Node *n) {
	heap->nodes[heap->count] = n;
	n->hIdx = heap->count;
	heap->count++;
	heapifyUp(heap, heap->count - 1);
}

void removeHeap(minHeap* heap, Node** item) {
	heap->count--;

	Node **h = heap->nodes;
	*item = h[0];

	h[0] = h[heap->count];
	h[0]->hIdx = 0;

	if(heap->count > 0)
		heapifyDown(heap, 0);
}

void updateValue(minHeap* heap, int idx, int newVal) {
	Node *item = heap->nodes[idx];
	if(item->value > newVal) {
		item->value = newVal;
		heapifyUp(heap, idx);
	} else {
		item->value = newVal;
		heapifyDown(heap, idx);
	}
}

void initHeap(minHeap* heap, int size) {
	heap->count = 0;
	heap->nodes = new Node*[size];
}

void deleteHeap(minHeap* heap) {
	delete[] heap->nodes;
	heap->count = 0;
}

void printHeap(minHeap* heap) {
	for(int i = 0; i < heap->count; i++)
		printf("%d ", heap->nodes[i]->value);
	printf("\n");
}


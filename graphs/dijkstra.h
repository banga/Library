#include "graph.h"
#include "heapq.h"

#define MAXCOST 1000000000

int main2() {
	int V, E;
	scanf("%d %d", &V, &E);

	graph g;
	initGraph(&g, V, E);

	FORn(i,E) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		addEdge(&g, from-1, to-1, cost);
	}

	minHeap heap;
	initHeap(&heap, V);

	/* Normal Dijkstra's */
	FORn(i, V) {
		g.nodes[i].value = (i == 0 ? 0 : (MAXCOST + 1));
		insertHeap(&heap, &g.nodes[i]);
	}

	while(heap.count) {
		Node *n;
		removeHeap(&heap, &n);
		for(vector<Edge*>::iterator it = n->edges.begin(); it != n->edges.end(); it++) {
			Edge* e = *it;
			if(e->from == n) {
				Node *t = e->to;
				ull newVal = n->value + e->cost;
				if(newVal < t->value)
					updateValue(&heap, t->hIdx, newVal);
			}
		}
	}

	FORn(i,V)
		printf("%llu ", g.nodes[i].value);
}

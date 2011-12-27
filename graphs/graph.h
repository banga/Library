/*
 * Author: Shrey Banga
 */
#include <cstdio>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

typedef struct Node Node;
typedef struct {
	Node *from, *to;
	ull cost;
} Edge;

struct Node {
	vector<Edge*> edges;
	int hIdx;  // index in heap, for updating values
	ull value; // shortest path distance, dijkstra's
};

/**
 * A simple graph data structure
 */
typedef struct {
	Edge* edges;
	Node* nodes;
	int V, E;
} graph;

void initGraph(graph* g, int V, int E) {
	g->V = 0;
	g->E = 0;
	g->nodes = new Node[V];
	g->edges = new Edge[E];

	FORn(i,V)
		g->nodes[i].edges.clear();
}

void addEdge(graph* g, int from, int to, int cost) {
	Edge *e = &g->edges[g->E];
	e->from = &g->nodes[from];
	e->to   = &g->nodes[to];
	e->cost = cost;
	g->E++;
	g->nodes[from].edges.push_back(e);
	g->nodes[to].edges.push_back(e);
}


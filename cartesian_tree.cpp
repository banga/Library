/**
 * A cartesian tree is a binary min-heap corresponding to a sequence
 * whose inorder traversal produces that exact sequence.
 * As described in http://wcipeg.com/wiki/Cartesian_tree
 */
#include <cstdio>
#include <cstdlib>

#define FORab(i,a,b) for(int i = (a); i < (b); i++)
#define FORn(i,n) FORab(i,0,n)

typedef struct Node {
  Node *left, *right, *parent;
  int value;

  Node(int v)
    : left(NULL), right(NULL), parent(NULL), value(v) {}
} Node;

Node* makeCartesianLinear(int seq[], int count) {
  if(count < 1) return NULL;

  Node *n = new Node(seq[0]);
  Node *v = n;

  for(int i = 1; i < count; i++) {
    n = new Node(seq[i]);
    if(n->value > v->value) {
      v->right  = n;
      n->parent = v;
    } else {
      Node *p = v->parent, *prev = v;
      while(p && p->value > n->value) {
        prev = p;
        p = p->parent;
      }
      n->left = prev;
      n->parent = p;
      if(p)
        p->right = n;
    }
    v = n;
  }

  while(n->parent)
    n = n->parent;

  return n;
}

Node* makeCartesianRecursive(int seq[], int count) {
  if(count < 1) return NULL;
  int mi = 0;
  FORn(i, count)
    if(seq[i] < seq[mi])
      mi = i;

  Node* n = new Node(seq[mi]);
  n->left = makeCartesianRecursive(seq, mi);
  n->right = makeCartesianRecursive(seq + mi + 1, count - mi - 1);
  return n;
}

void inorder(Node* n) {
  if(!n) return;
  inorder(n->left);
  printf("%d ", n->value);
  inorder(n->right);
}

int main() {
  int seq[] = {1, 9, 3, 4, 5, 2, 6, 8, 10, 23, 6, 5};
  int count = sizeof(seq) / sizeof(int);
  
  FORn(i,count)
    printf("%d ", seq[i]);
  printf("\n");
  
  Node* n = makeCartesianLinear(seq, count);
  inorder(n);
  printf("\n");

  Node* m = makeCartesianRecursive(seq, count);
  inorder(m);
  printf("\n");
}


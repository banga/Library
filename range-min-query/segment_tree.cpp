/**
 * Segment Tree
 * A heap-like data structure which answers range minimum queries in O(logn)
 * Build time is O(n)
 * Author: Shrey Banga
 */
#include <cstdio>
#include <cstdlib>

template <class T>
class SegmentTree {
  public:

  SegmentTree(T* a, int n)
  : A(a), nodes(0), count(0), size(n) {
    int h = 0;
    while((1 << h) < size)
      h++;
    // Maximum 2*2^h - 1 nodes
    count = (1 << (h + 1)) - 1;
    nodes = new int[count];

    init(0, 0, size-1);
  }

  int rmq(int i, int j) {
    return query(0, 0, size-1, i, j);
  }

  private:
  T *A;
  int *nodes;
  int count;// No. of nodes
  int size; // Size of the interval

  void init(int idx, int i, int j) {
    if(i == j)
      nodes[idx] = i;
    else {
      int left = 2 * idx + 1, mid = (i + j) / 2;
      init(left, i, mid);
      init(left+1, mid+1, j);
      nodes[idx] = (A[nodes[left]] <= A[nodes[left+1]]) ? nodes[left] : nodes[left+1];
    }
  }

  int query(int idx, int start, int end, int i, int j) {
    if(start > j || end < i)
      return -1;
  
    if(start >= i && end <= j) {
      return nodes[idx];
    }

    int left = 2 * idx + 1, mid = (start + end) / 2;
    int q1 = query(left, start, mid, i, j);
    int q2 = query(left+1, mid+1, end, i, j);
    if(q1 == -1)
      return q2;
    if(q2 == -1)
      return q1;
    return (A[q1] <= A[q2] ? q1 : q2);
  }
};

int rmq(int* a, int i, int j) {
  int mi = i;
  for(i++; i <= j; i++)
    if(a[i] < a[mi])
      mi = i;
  return mi;
}

void check(int *a, int count, SegmentTree<int>& t) {
  for(int i = 0; i < count; i++) {
    for(int j = i; j < count; j++) {
      int x = t.rmq(i,j), y = rmq(a,i,j);
      if(x != y) {
        printf("! x = %d y = %d in [%d,%d]\n", x, y, i, j);
//        for(int k = i; k <= j; k++)
//          printf("%d ", a[k]);
//        printf("\n");
//        printf("i = %d j = %d t.rmq = %d rmq = %d\n", i, j, a[x], a[y]);
      }
    }
  }
}

int main() {
  int count = 1000;
  int *a = new int[count];
  for(int i = 0; i < count; i++)
    a[i] = rand();

  SegmentTree<int> t(a, count);

  check(a, count, t);
}


/*
 * Sparse Table
 *
 * Performs range minimum queries in constant time
 * nlogn building time
 *
 * Author: Shrey Banga
 */
#include <cstdio>
#include <cstdlib>

#define FORab(i,a,b) for(int i = (a); i < (b); i++)
#define FORn(i,n) FORab(i,0,n)

template <typename T>
T MIN(const T& a, const T& b) {
  return (a < b) ? a : b;
}

template <typename T>
T MAX(const T& a, const T& b) {
  return (a > b) ? a : b;
}

template <typename T>
void SWAP(T& a, T& b) {
  T t = a;
  a = b;
  b = t;
}

template <class T>
class SparseTable {
  public:
  SparseTable(T* a, int n)
  : max(n), logmax(0), A(a), M(0) {
    while((1 << logmax) <= max)
      logmax++;
    logmax++;

    M = new int*[logmax];
    for(int i = 0; i < logmax; i++)
      M[i] = new int[max];

    // Populate first row
    for(int j = 0; j < max; j++)
      M[0][j] = j;

    // Populate rest using recurrence
    // M[i][j] = M[i][j-1] + M[i + 2^(j-1)][j-1]
    for(int i = 1; i < logmax; i++) {
      int k = 1 << (i - 1);
      for(int j = max - 1; j >= (max - k); j--)
        M[i][j] = M[i-1][j];
      for(int j = max - k - 1; j >= 0; j--) {
        int p = M[i-1][j], q = M[i-1][j+k];
        M[i][j] = (A[p] < A[q]) ? p : q;
      }
    }

    printf("M is %dx%d\n", logmax, max);
    for(int i = 0; i < logmax; i++) {
      for(int j = 0; j < max; j++)
        printf("%3d ", A[M[i][j]]);
      printf("\n");
    }
  }

  // Assuming i <= j and i,j are in range
  int rmq(int i, int j) {
    int diff = j-i+1, k = 0, w = 2;
    while(w < diff) {
      w <<= 1;
      k++;
    }
    w >>= 1;
    int l = MAX(0, j + 1 - w);
    int p = M[k][i], q = M[k][l];
    return (A[p] < A[q]) ? p : q;
  }

  ~SparseTable() {
    for(int i = 0; i < logmax; i++)
      delete[] M[i];
    delete[] M;
  }

  private:
  int max, logmax;
  T *A;
  int **M;

  SparseTable(const SparseTable& t)
  : max(t.max), logmax(t.logmax), A(0), M(0) {
  }

  SparseTable& operator = (const SparseTable&) {
    return *this;
  }
};

int rmq(int* a, int i, int j) {
  int mi = i;
  for(i++; i <= j; i++)
    if(a[i] < a[mi])
      mi = i;
  return mi;
}

int main() {
  int a[] = {7, 5, 9, 4, 8, 3, 6, 2, 1};
  int count = sizeof(a) / sizeof(int);

  SparseTable<int> t(a, count);

  for(int i = 0; i < count; i++) {
    for(int j = i; j < count; j++) {
      int x = t.rmq(i,j), y = rmq(a,i,j);
      if(x != y) {
        for(int k = i; k <= j; k++)
          printf("%d ", a[k]);
        printf("\n");
        printf("i = %d j = %d t.rmq = %d rmq = %d\n", i, j, a[x], a[y]);
      }
    }
  }
}


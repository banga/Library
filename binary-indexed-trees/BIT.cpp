/**
 * Binary Indexed Tree
 * As described in http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
 * Author: Shrey Banga
 */
#include "BIT.h"
#include <cstdio>
#include <cstdlib>

void check(int *f, BIT& bt, int N) {
  int sum = 0;
  for(int i = 0; i < N; i++) {
    int s = bt.readSingle(i);
    if(f[i] != s)
     printf("FAILED: i = %d, f[i] = %d, readSingle returned %d\n", i, f[i], s);

    sum += f[i];
    s = bt.readCumulative(i);
    if(sum != s)
     printf("FAILED: i = %d, cf[i] = %d, readCumulative returned %d\n", i, sum, s);
  }
}

int main() {
  int N = 1000000;
  int *f = new int[N];
  BIT bt(N);
  
  for(int i = 0; i < N; i++) {
    f[i] = rand() % 1000;
    bt.add(i, f[i]);
  }

  check(f, bt, N);

  for(int i = 0; i < N; i++) {
    int s = rand() % 100 - 50;
    f[i] += s;
    bt.add(i, s);
  }

  check(f, bt, N);

  delete[] f;
}

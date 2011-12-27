/**
 * 2-D Binary Indexed Tree
 * As described in http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
 * Author: Shrey Banga
 */
#include <cstdio>
#include "BIT2D.h"
#include <cstdlib>

int main() {
  int m[5][5] = 
  { {1,2,3,4,5},
    {3,5,2,9,4},
    {2,6,7,8,1},
    {9,9,2,4,5},
    {3,7,3,4,1}};
  int s[5][5];

  BIT2D bt(5,5);
  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++)
      bt.add(i,j,m[i][j]);

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++) {
      s[i][j] = 0;
      for(int ii = 0; ii <= i; ii++)
        for(int jj = 0; jj <= j; jj++)
          s[i][j] += m[ii][jj];
    }
  
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      printf("%2d ", s[i][j]);
    }
    printf("\n");
  }

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      printf("%2d ", bt.readCumulative(i,j));
    }
    printf("\n");
  }

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      printf("%2d ", bt.readSingle(i,j));
    }
    printf("\n");
  }
}

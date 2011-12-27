/*
 * Author: Shrey Banga
 */
#include <cstdio>
#include <ctime>

#define DIGITS 18000
#define BASE 1000000000
#define BASEW 9

typedef unsigned long long ull;
//typedef unsigned int ull;

int main() {
  clock_t ticks = clock();

  const int size = (10 * DIGITS) / 3 + 1;
  ull A[size];
  char str[DIGITS * BASEW + 1];
  int istr = 0;
  for(int i = 0; i < size; i++)
    A[i] = 2;

  for(int digit = 1; digit <= DIGITS / BASEW; digit++) {
    ull s, q = 0;
    for(int i = size, d = 2 * size - 1; i > 0; i--, d -= 2) {
      s = A[i-1] * BASE + q * i;
      A[i-1] = s % d;
      q = s / d;
    }
    A[0] = q % BASE;
    q = q / BASE;

    if(q >= BASE) {
      ull cy = q / BASE;
      q -= cy * BASE;

      int istr2 = istr;
      while(cy) {
        istr2--;
        ull sum = (str[istr2] - '0') + cy;
        str[istr2] = '0' + (sum % 10);
        cy = cy / 10;
      }
    }

    for(int k = BASE / 10; k > 0; k /= 10) {
      ull qd = q / k;
      str[istr++] = '0' +  qd;
      q -= qd * k;
    }
  }
  str[DIGITS*BASEW] = 0;
  str[BASEW-2] = '3';
  str[BASEW-1] = '.';
  printf("%s", str + (BASEW-2));

  printf("\n%.3fs\n", (clock() - ticks) / (float)CLOCKS_PER_SEC);
}


/*
 * What does this code do?
 * m = x >> 31;
 * printf("%d", x ^ m - m);
 */
#include <stdio.h>


void printBytes(int x) {
	int mask = 1;

	for(int i = 31; i >= 0; i--) {
		printf("%c", x & (1 << i) ? '1' : '0');
	}
}

int main() {
	int x = -7, m;

	x >>= 1;
	printf("x = "); printBytes(x); printf(" = %d\n", x);

	scanf("%d", &x);

	m = x >> 31;
	printf("\nx       = "); printBytes(x);
	printf("\nm       = "); printBytes(m);
	printf("\nx^m     = "); printBytes(x^m);
	printf("\nx^m - m = "); printBytes(x^m - m);

	printf(" = %d\n", (x^m) - m);
}

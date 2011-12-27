#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MEM_DEBUG 0
#include "cust_malloc.h"

int main() {
	char *str;
	clock_t t = clock();
	unsigned int count = 0, max_count = 1024*1024*1024;

	do {
		str = (char*)cust_malloc(24);
		count += 24;
	} while(str && count < max_count);

	printf("%u\n", clock() - t);

	return 0;
}

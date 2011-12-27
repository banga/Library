#ifndef __CUST_MALLOC
#define __CUST_MALLOC

typedef struct {
	char file[128];
	int line;
	size_t size;
} malloc_info;

const int _offset = sizeof(malloc_info);
static int allocatedMemory = 0;

void* my_malloc(size_t size, const char* file, int line) {
	void* mem = malloc(size + _offset);
	if(mem) {
		malloc_info* info = (malloc_info*)mem;
		strcpy(info->file, file);
		info->line = line;
		info->size = size;

		printf("Allocating %u bytes at 0x%x in %s:%d\n", size, mem, file, line);

		allocatedMemory += size;

		return (void*)((char*)mem + _offset);
	} else {
		printf("Allocation of %u bytes failed in %s:%d\n", size, file, line);
	}
	return NULL;
}

void my_free(void* ptr, const char* file, int line) {
	malloc_info* info = (malloc_info*)((char*)ptr - _offset);
	printf("Deallocating %u bytes at 0x%x (allocated at %s:%d) in %s:%d\n", info->size, info, info->file, info->line, file, line);

	allocatedMemory -= info->size;

	free(info);
}

#if MEM_DEBUG
	#define cust_malloc(size) my_malloc(size, __FILE__, __LINE__)
	#define cust_free(ptr) my_free(ptr, __FILE__, __LINE__)
#else
	#define cust_malloc(size) malloc(size)
	#define cust_free(ptr) free(ptr)
#endif

#endif

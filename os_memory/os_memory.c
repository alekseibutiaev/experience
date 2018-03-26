#include <stdlib.h>

/* OS interface */

void* OS_malloc(int size) {
	return malloc(size);
}

void OS_free(int size, void* ponter) {
	free(ponter);
}

#define block_size 16
/* implement a malloc function */

struct mem_info {
	int size[block_size/sizeof(int)];
};

void* _malloc(int size) {
	int t = size % block_size > 0;
	int bcount = size / block_size + t + 1;
	int rsize = bcount * block_size;
	struct mem_info* result = (struct mem_info*)OS_malloc(rsize);
	if( result ) {
		result->size[0] = rsize;
		return &result[1];
	}
	return 0;
}

void _free(void* ptr) {
	if (ptr) {
		struct mem_info* info = (struct mem_info*)ptr;
		OS_free(info[-1].size[0], &info[-1]);
	}
}

int main(void) {
	{
		void* p = _malloc(13);
		_free(p);
	}
	{
		void* p = _malloc(61);
		_free(p);
	}
	return 0;
}

#include "types.h"

typedef struct Block Block;

struct Block{
    Block* next;
    size_t size;
    int is_free;

};

void allocator_init(void* start_address, size_t size);
void * alloc(size_t size);
void free(void * ptr);
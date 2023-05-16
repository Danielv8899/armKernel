#include "mm.h"

Block* heap_head;

void allocator_init(void* start_address, size_t size) {
    heap_head = start_address;
    int heap_size = size;

    Block* initial_block = (Block*)heap_head;
    initial_block->size = heap_size;
    initial_block->is_free = 1;
    initial_block->next = NULL;
}

void* alloc(size_t size) {
    size_t rounded_size = 1;
    while (rounded_size < size) {
        rounded_size <<= 1;
    }

    Block* current_block = heap_head;
    while (current_block) {
        if (current_block->is_free && current_block->size >= rounded_size) {
            // Split the block until we reach the desired size
            while (current_block->size > rounded_size * 2) {
                Block* new_block = (Block*)((char*)current_block + current_block->size / 2);
                new_block->size = current_block->size / 2;
                new_block->is_free = 1;
                new_block->next = current_block->next;
                current_block->next = new_block;
                current_block->size /= 2;
            }

            current_block->is_free = 0;
            return (void*)((char*)current_block + sizeof(Block));  // Return the address after the block header
        }
        current_block = current_block->next;
    }

    return NULL;  // No suitable block found
}

void free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->is_free = 1;

    // Coalesce adjacent free blocks
    Block* current_block = heap_head;
    while (current_block) {
        if (current_block->is_free) {
            if (current_block->next && current_block->next->is_free) {
                current_block->size *= 2;
                current_block->next = current_block->next->next;
            } else {
                current_block = current_block->next;
            }
        } else {
            current_block = current_block->next;
        }
    }
}
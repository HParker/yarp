#ifndef YARP_ALLOC_H
#define YARP_ALLOC_H

#include "yarp/defines.h"
#include <stdlib.h>

#define MAX_POOLS 100 // TODO: malloc instead of static length

typedef struct yp_memory_pool {
    size_t capacity;
    size_t size;
    char *memory;
} yp_memory_pool_t;

typedef struct yp_allocator {
    size_t capacity;
    size_t size;
    size_t pool_count;
    yp_memory_pool_t pools[MAX_POOLS];
} yp_allocator_t;

void
yp_assure_available_memory(yp_allocator_t *allocator, size_t size);

void *
yp_malloc(yp_allocator_t *allocator, size_t size);

void *
yp_calloc(yp_allocator_t *allocator, size_t num, size_t size);

void
yp_free(yp_allocator_t *allocator, void *ptr);

yp_memory_pool_t
yp_memory_pool_init(size_t capacity);

yp_allocator_t
yp_allocator_init(size_t size);

void
yp_allocator_free(yp_allocator_t *allocator);

#endif // YARP_ALLOC_H

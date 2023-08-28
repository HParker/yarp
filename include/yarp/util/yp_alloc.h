#ifndef YARP_ALLOC_H
#define YARP_ALLOC_H

#include "yarp/defines.h"
#include <stdlib.h>

typedef struct yp_allocator {
    size_t size;
    void *memory;
} yp_allocator_t;

void *
yp_malloc(yp_allocator_t *allocator, size_t size);

void *
yp_calloc(yp_allocator_t *allocator, size_t num, size_t size);

void *
yp_realloc(yp_allocator_t *allocator, void *ptr, size_t size);

void
yp_free(yp_allocator_t *allocator, void *ptr);

yp_allocator_t
yp_allocator_init(size_t size);

void
yp_allocator_free(yp_allocator_t *allocator);

#endif // YARP_ALLOC_H

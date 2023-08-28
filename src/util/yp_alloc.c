#include "yarp/util/yp_alloc.h"

void *
yp_malloc(yp_allocator_t *allocator, size_t size) {
    (void)allocator;
    return malloc(size);
}

void *
yp_calloc(yp_allocator_t *allocator, size_t num, size_t size) {
    (void)allocator;
    return calloc(num, size);
}

void
yp_free(yp_allocator_t *allocator, void *ptr) {
    (void)allocator;
    free(ptr);
}

yp_allocator_t
yp_allocator_init(size_t size) {
    yp_allocator_t allocator = {
        .size = size,
        .memory = malloc(sizeof(char) * size)
    };
    return allocator;
}

void
yp_allocator_free(yp_allocator_t *allocator) {
    free(allocator->memory);
}

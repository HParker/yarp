#include "yarp/util/yp_alloc.h"

// 16mb default pool size as a "good guess" for big enough for all files
#define DEFAULT_POOL_SIZE 16000
#define USE_ARENA 1

void *
yp_malloc(yp_allocator_t *allocator, size_t size) {
    if (USE_ARENA) {
        size = (size + 7) & ~7UL;
        allocator->size += size;
        yp_assure_available_memory(allocator, size);

        void *ptr = allocator->pools[allocator->pool_count].memory + allocator->pools[allocator->pool_count].size;
        allocator->pools[allocator->pool_count].size += size;

        return ptr;
    } else {
        return malloc(size);
    }
}

void *
yp_calloc(yp_allocator_t *allocator, size_t num, size_t size) {
    if (USE_ARENA) {
        return yp_malloc(allocator, num * size);
    } else {
        return calloc(num, size);
    }
}

void
yp_free(yp_allocator_t *allocator, void *ptr) {
    if (USE_ARENA) {
        // NO OP
        (void)allocator;
    } else {
        free(ptr);
    }
}

yp_memory_pool_t
yp_memory_pool_init(size_t capacity) {
    yp_memory_pool_t pool = {
        .capacity = capacity,
        .size = 0,
        .memory = calloc(1, capacity)
    };
    return pool;
}

yp_allocator_t
yp_allocator_init(size_t capacity) {
    yp_allocator_t allocator = {
        .capacity = capacity,
        .size = 0,
        .pool_count = 0,
    };

    allocator.pools[allocator.pool_count] = yp_memory_pool_init(DEFAULT_POOL_SIZE);

    return allocator;
}

void
yp_assure_available_memory(yp_allocator_t *allocator, size_t size) {
    if (allocator->pools[allocator->pool_count].size + size >= allocator->pools[allocator->pool_count].capacity) {
        allocator->pool_count++;
        allocator->pools[allocator->pool_count] = yp_memory_pool_init(DEFAULT_POOL_SIZE);
    }
}

void
yp_allocator_free(yp_allocator_t *allocator) {
    for (size_t i = 0; i < allocator->pool_count; i++) {
        free(allocator->pools[i].memory);
    }
}

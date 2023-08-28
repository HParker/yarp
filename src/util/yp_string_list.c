#include "yarp/util/yp_string_list.h"

// Allocate a new yp_string_list_t.
yp_string_list_t *
yp_string_list_alloc(void) {
    return (yp_string_list_t *) malloc(sizeof(yp_string_list_t));
}

// Initialize a yp_string_list_t with its default values.
void
yp_string_list_init(yp_allocator_t *allocator, yp_string_list_t *string_list) {
    string_list->strings = (yp_string_t *) yp_malloc(allocator, sizeof(yp_string_t));
    string_list->length = 0;
    string_list->capacity = 1;
}

// Append a yp_string_t to the given string list.
void
yp_string_list_append(yp_allocator_t *allocator, yp_string_list_t *string_list, yp_string_t *string) {
    if (string_list->length + 1 > string_list->capacity) {
        string_list->capacity *= 2;
        // TODO: do realloc before commiting
        string_list->strings = (yp_string_t *) yp_realloc(allocator, string_list->strings, string_list->capacity * sizeof(yp_string_t));
    }

    string_list->strings[string_list->length++] = *string;
}

// Free the memory associated with the string list.
void
yp_string_list_free(yp_allocator_t *allocator, yp_string_list_t *string_list) {
    yp_free(allocator, string_list->strings);
}

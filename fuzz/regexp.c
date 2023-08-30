#include <yarp.h>

void
harness (const char *input, size_t size) {
    yp_string_list_t *capture_list = yp_string_list_alloc ();
    yp_allocator_t allocator = yp_allocator_init (0);
    assert (capture_list);
    yp_string_list_init (&allocator, capture_list);
    yp_regexp_named_capture_group_names ((const char *)input, size,
                                         capture_list);
    yp_string_list_free (&allocator, capture_list);
    free (capture_list);
    yp_allocator_free (&allocator);
}

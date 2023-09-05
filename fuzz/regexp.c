#include <yarp.h>

void
harness(const uint8_t *input, size_t size) {
    yp_string_list_t capture_list;
    yp_string_list_init(&capture_list);

    yp_allocator_t allocator;
    yp_allocator_init(&allocator, 0);

    yp_regexp_named_capture_group_names(allocator, input, size, &capture_list, false, &yp_encoding_utf_8);
    yp_string_list_free(&capture_list);
}

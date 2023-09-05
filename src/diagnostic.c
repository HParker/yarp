#include "yarp/diagnostic.h"

// Append an error to the given list of diagnostic.
bool
yp_diagnostic_list_append(yp_list_t *list, const uint8_t *start, const uint8_t *end, const char *message) {
    yp_diagnostic_t *diagnostic = (yp_diagnostic_t *) malloc(sizeof(yp_diagnostic_t));
    if (diagnostic == NULL) return false;

    *diagnostic = (yp_diagnostic_t) { .start = start, .end = end, .message = message };
    yp_list_append(list, (yp_list_node_t *) diagnostic);
    return true;
}

// Append an error to the error diagnostic list.
bool
yp_diagnostic_error_list_append(yp_parser_t *parser, const uint8_t *start, const uint8_t *end, const char *message) {
    return yp_diagnostic_list_append(&parser->error_list, start, end, message);
}

// Append a warning to the warning diagnostic list.
bool
yp_diagnostic_warning_list_append(yp_parser_t *parser, const uint8_t *start, const uint8_t *end, const char *message) {
    return yp_diagnostic_list_append(&parser->warning_list, start, end, message);
}

// Deallocate the internal state of the given diagnostic list.
void
yp_diagnostic_list_free(yp_list_t *list) {
    yp_list_node_t *node, *next;

    for (node = list->head; node != NULL; node = next) {
        next = node->next;

        yp_diagnostic_t *diagnostic = (yp_diagnostic_t *) node;
        free(diagnostic);
    }
}

#include <vx/core.h>


void vx_mem_fail(
    VXString type
) {
    vx_fatal("Failed to allocate memory for %s", type);
}


void vx_fatal(char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "%sVX fatal error: %s", VX_ANSI_RED, VX_ANSI_YELLOW);
    vfprintf(stderr, format, args);
    fprintf(stderr, "%s\n", VX_ANSI_RESET);
    va_end(args);
    exit(1);
}

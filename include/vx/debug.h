#ifndef VX_DEBUG_H
#define VX_DEBUG_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <vx/types.h>

void vx_debug(
    char *format, 
    ...
);
void vx_debug_col(
    VXString file, 
    VXPos    line,
    VXString colour,
    VXString format, 
    ...
);
void vx_debug_token(
    VXString type, 
    VXString str, 
    VXPos    len
);
void vx_debug_on();
void vx_debug_off();

#define VX_DEBUG_INIT         0x0002
#define VX_DEBUG_MEM          0x0004
#define VX_DEBUG_CALL         0x0008
#define VX_DEBUG_FILE         0x0010
#define VX_DEBUG_DELTA        0x0020
#define VX_DEBUG_EPSILON      0x0040
#define VX_DEBUG_PASTA        0x0080
#define VX_DEBUG_NOODLY       0x0100
#define VX_DEBUG_APPENDAGE    0x0200
#define VX_DEBUG_ALL          0xFFFF

#define VX_ANSI_RED           "\e[31m"
#define VX_ANSI_GREEN         "\e[32m"
#define VX_ANSI_YELLOW        "\e[33m"
#define VX_ANSI_BLUE          "\e[34m"
#define VX_ANSI_MAGENTA       "\e[35m"
#define VX_ANSI_CYAN          "\e[36m"
#define VX_ANSI_WHITE         "\e[37m"
#define VX_ANSI_RESET         "\e[0m"
#define VX_ANSI_NONE          ""

#define VX_DEBUG_LINE_COL     VX_ANSI_CYAN
#define VX_DEBUG_FILE_COL     VX_ANSI_YELLOW

#ifndef VX_DEBUG
    #define VX_DEBUG 0
#elif (VX_DEBUG == 1)
    #undef  VX_DEBUG
    #define VX_DEBUG VX_DEBUG_ALL
#endif

#if VX_DEBUG
    #define vx_assert                                                 \
            assert
    #define vx_debug_at(...)                                          \
            vx_debug_col(__FILE__, __LINE__, __VA_ARGS__)
    #define vx_debug_msg(...)                                         \
            vx_debug_at(VX_ANSI_RESET,   __VA_ARGS__)
    #define vx_debug_red(...)                                         \
            vx_debug_at(VX_ANSI_RED,     __VA_ARGS__)
    #define vx_debug_green(...)                                       \
            vx_debug_at(VX_ANSI_GREEN,   __VA_ARGS__)
    #define vx_debug_yellow(...)                                      \
            vx_debug_at(VX_ANSI_YELLOW,  __VA_ARGS__)
    #define vx_debug_blue(...)                                        \
            vx_debug_at(VX_ANSI_BLUE,    __VA_ARGS__)
    #define vx_debug_magenta(...)                                     \
            vx_debug_at(VX_ANSI_MAGENTA, __VA_ARGS__)
    #define vx_debug_cyan(...)                                        \
            vx_debug_at(VX_ANSI_CYAN,    __VA_ARGS__)

    #if VX_DEBUG & VX_DEBUG_INIT
        #define vx_debug_init(...)    vx_debug_yellow(__VA_ARGS__)
    #else 
        #define vx_debug_init(format, ...)
    #endif

    #if VX_DEBUG & VX_DEBUG_MEM
        #define vx_debug_mem(...)     vx_debug_cyan(__VA_ARGS__)
    #else 
        #define vx_debug_mem(format, ...)
    #endif

    #if VX_DEBUG & VX_DEBUG_CALL
        #define vx_debug_call(...)    vx_debug_blue(__VA_ARGS__)
    #else 
        #define vx_debug_call(format, ...)
    #endif

    #if VX_DEBUG & VX_DEBUG_DELTA
        #define vx_debug_delta(...)    vx_debug_magenta(__VA_ARGS__)
    #else 
        #define vx_debug_delta(format, ...)
    #endif

    #if VX_DEBUG & VX_DEBUG_EPSILON
        #define vx_debug_epsilon(...) vx_debug_cyan(__VA_ARGS__)
    #else 
        #define vx_debug_epsilon(format, ...)
    #endif

#else
    #define vx_assert             (void)
    #define vx_debug_msg(...)
    #define vx_debug_red(...)
    #define vx_debug_green(...)
    #define vx_debug_yellow(...)
    #define vx_debug_blue(...)
    #define vx_debug_magenta(...)
    #define vx_debug_cyan(...)
    #define vx_debug_init(...)
    #define vx_debug_mem(...)
    #define vx_debug_call(...)
    #define vx_debug_delta(...)
    #define vx_debug_epsilon(...)
#endif

#endif /* VX_DEBUG_H */



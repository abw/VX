#ifndef VX_MEMORY_H
#define VX_MEMORY_H

#include <vx/core.h>


/*--------------------------------------------------------------------------
 * Function prototypes
 *--------------------------------------------------------------------------*/
void    vx_mem_fail(VXString);
void    vx_fatal(char *format, ...);


/*--------------------------------------------------------------------------
 * Aliases
 *--------------------------------------------------------------------------*/

#define vx_mem_alloc(size)            malloc(size)
#define vx_mem_resize(memory, size)   realloc(memory, size)
#define vx_mem_free(memory)           free(memory)


/*--------------------------------------------------------------------------
 * Macro to patch in memmove(), bcopy() or a hand-rolled memory copy function
 *--------------------------------------------------------------------------*/

/* gcc 4.4 doesn't like empty values in #elif */
#ifdef  VX_HAVE_BCOPY
#undef  VX_HAVE_BCOPY
#define VX_HAVE_BCOPY 1
#endif

#ifdef  VX_HAVE_MEMMOVE
#   define vx_mem_copy(src, dest, len) memmove(dest, src, len)
#elif   VX_HAVE_BCOPY
#   define vx_mem_copy(src, dest, len) bcopy(src, dest, len)
#else
#   define VX_ADD_MEM_COPY 1
    VXMemory vx_mem_copy(
        VXMemory src,
        VXMemory dest,
        VXSize   len
    );
#endif



#endif /* VX_MEMORY_H */

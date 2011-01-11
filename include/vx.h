#ifndef VX_H
#define VX_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <vx/core.h>
//#include <vx/delta.h>
//#include <vx/modules.h>

/* VX initialisation and cleanup functions */
VX              VX_new();
void            VX_free(VX);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif /* VX_H */


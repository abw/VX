#ifndef VX_CORE_H
#define VX_CORE_H

/*--------------------------------------------------------------------------
 * This header file includes all the other core header files that are 
 * required by most, if not all of the library source files.
 *--------------------------------------------------------------------------*/

#define _GNU_SOURCE
 
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/types.h>

#include <vx/config.h>            /* local system configuration           */
#include <vx/os.h>                /* operating system specific items      */
#include <vx/defines.h>           /* various data definitions             */
#include <vx/types.h>             /* type definitions                     */
#include <vx/debug.h>             /* debugging functions/definitions      */
#include <vx/memory.h>            /* memory management                    */

#endif /* VX_CORE_H */

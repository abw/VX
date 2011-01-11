#ifndef VX_OS_H
#define VX_OS_H

#ifdef WIN32
#  define VX_PATH_SEPARATOR     ";"
#  define VX_DIR_SEPARATOR      "\\"
#  define VX_ROOT_DIR           "\\"
#  define VX_CURRENT_DIR        "."
#  define VX_PARENT_DIR         ".."
#  define VX_REAL_OS            0
#else
#  define VX_PATH_SEPARATOR     ":"
#  define VX_DIR_SEPARATOR      "/"
#  define VX_ROOT_DIR           "/"
#  define VX_CURRENT_DIR        "."
#  define VX_PARENT_DIR         ".."
#  define VX_REAL_OS            1
#endif

/* bits adapted from LuaJIT */
#define VX_ARCH_X86           32
#define VX_ARCH_X64           64
#define VX_ARCH_LITTLE_ENDIAN 1234
#define VX_ARCH_BIG_ENDIAN    4321


#ifndef VX_TARGET
    #if defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
        #define VX_TARGET     VX_ARCH_X86
    #elif defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || defined (_M_IA64)
        #define VX_TARGET     VX_ARCH_X64
    #else
        #error "No support for this architecture (yet)"
    #endif
#endif

#if VX_TARGET == VX_ARCH_X86
    #define VX_ARCHITECTURE   "x86"
    #define VX_WORD_LENGTH    32
#elif VX_TARGET == VX_ARCH_X64
    #define VX_ARCHITECTURE   "x64"
    #define VX_WORD_LENGTH    64
#else
    #error "No target architecture defined"
#endif

#if __LITTLE_ENDIAN__ || VX_TARGET == VX_ARCH_X86 || VX_TARGET == VX_ARCH_X64
    #define VX_BYTE_ORDER     VX_ARCH_LITTLE_ENDIAN
#elif __BIG_ENDIAN__
    #define VX_BYTE_ORDER     VX_ARCH_BIG_ENDIAN
#else
    #error "Can't determine the endian-ness of the target architecture"
#endif

#if VX_BYTE_ORDER == VX_ARCH_LITTLE_ENDIAN
    #define VX_LITTLE_ENDIAN  1
    #define VX_BIG_ENDIAN     0
    #define VX_ENDIAN         "little"
#elif VX_BYTE_ORDER == VX_ARCH_BIG_ENDIAN
    #define VX_LITTLE_ENDIAN  0
    #define VX_BIG_ENDIAN     1
    #define VX_ENDIAN         "big"
#else
    #error "No endianness defined for the target architecture"
#endif


#ifndef VX_INLINE
    #if defined __cplusplus
        #define VX_INLINE     inline
    #elif defined __GNUC__
        #define VX_INLINE     __inline__
    #elif defined _MSC_VER
        #define VX_INLINE     __inline
    #else
        #define VX_INLINE     inline
    # endif
#endif

#ifndef VX_DO_INLINE
    #if defined __GNUC__
        #define VX_DO_INLINE  __attribute__((always_inline)) VX_INLINE
    #elif defined _MSC_VER
        #define VX_DO_INLINE  __forceinline
    #else
        #define VX_DO_INLINE  VX_INLINE
    #endif
#endif

#ifndef VX_NO_INLINE
    #if defined __GNUC__
        #define VX_NO_INLINE  __attribute__((noinline))
    #elif defined _MSC_VER
        #define VX_NO_INLINE  __declspec(noinline)
    #else
        #define VX_NO_INLINE
    #endif
#endif


/*--------------------------------------------------------------------------
 * Thread locking.  Encapsulates a block of code with a locked mutex.
 * Cargo-culto from Nik Clayton's TAP library, but not really used.  Thread
 * safety is something that (will|may) come later.
 *--------------------------------------------------------------------------*/

#ifdef VX_HAVE_LIBPTHREAD
    #include <pthread.h>
    static  pthread_mutex_t M = PTHREAD_MUTEX_INITIALIZER;
    #define VX_MUTEX_LOCK     pthread_mutex_lock(&M);
    #define VX_MUTEX_UNLOCK   pthread_mutex_unlock(&M);
#else
    #define VX_MUTEX_LOCK
    #define VX_MUTEX_UNLOCK
#endif

#endif /* VX_OS_H */
#include <vx.h>


/*--------------------------------------------------------------------------
 * vx object initialisation functions
 *--------------------------------------------------------------------------*/

VX
VX_new() {
    vx_debug_msg("vx_new()\n");
    VX vx = (VX) vx_mem_alloc( sizeof(struct vx) );
    if (! vx)
        vx_mem_fail("Vx");

    vx->verbose = VX_FALSE;
    vx->debug   = VX_FALSE;

    return vx;
}

/*--------------------------------------------------------------------------
 * vx object cleanup functions
 *--------------------------------------------------------------------------*/

void
VX_free(
    VX vx
) {
    vx_debug_msg("vx_free()\n");

    /* vx */
    vx_mem_free(vx);
}


/*--------------------------------------------------------------------------
 * Miscellaneous functions
 *--------------------------------------------------------------------------*/


VXString
VX_version() {
    return VX_VERSION;
}


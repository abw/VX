#ifndef VX_TYPES_H
#define VX_TYPES_H


/*--------------------------------------------------------------------------
 * Generic data types.  We use VXBlah data types internally for the sake 
 * of consistency, simplicity and to abstract away any differences between
 * platforms.
 *--------------------------------------------------------------------------*/

typedef u_int8_t                  VXU8;       /* generic 8 bit integer    */
typedef u_int16_t                 VXU16;      /* generic 16 bit integer   */
typedef u_int32_t                 VXU32;      /* generic 32 bit integer   */
typedef u_int64_t                 VXU64;      /* generic 64 bit integer   */
typedef u_int32_t                 VXFlags;    /* bitmask                  */
typedef int32_t                   VXOffset;   /* -ve/+ve offset           */
typedef int32_t                   VXInt;      /* generic integer          */
typedef double                    VXNum;      /* generic fp number        */
typedef unsigned long int         VXUint;     /* generic unsigned int     */
typedef unsigned long int         VXSize;     /* +ve size of list         */
typedef unsigned long int         VXPos;      /* +ve posn. in string/list */
typedef unsigned short int        VXPrec;     /* operator precedence      */
typedef unsigned char             VXBool;     /* boolean true/false       */
typedef unsigned char             VXChar;     /* single character         */
typedef void                    * VXMemory;   /* generic memory pointer   */
typedef const char              * VXName;     /* immutable C string       */
typedef char                    * VXString;   /* C string                 */
typedef jmp_buf                   VXJumpBuf;  /* longjmp buffer           */


/*--------------------------------------------------------------------------
 * VX data types
 *--------------------------------------------------------------------------*/

typedef enum   vx_errno         VXErrno;
typedef enum   vx_jump_type     VXJumpType;
typedef enum   vx_tag_style     VXTagStyle;

/* values */
typedef struct vx_unary_op      VXUnaryOp;
typedef struct vx_binary_op     VXBinaryOp;
typedef struct vx_block_op      VXBlockOp;
typedef union  vx_op            VXOp;
typedef union  vx_value         VXValue;

/* pointers to vx data structures */
typedef struct vx             * VX;
typedef struct vx_action      * VXAction;
typedef struct vx_cache       * VXCache;
typedef struct vx_codec       * VXCodec;
typedef struct vx_delta       * VXDelta;
typedef struct vx_element     * VXElement;
typedef struct vx_error       * VXError;
typedef struct vx_frame       * VXFrame;
typedef struct vx_module      * VXModule;
typedef struct vx_namespace   * VXNamespace;
typedef struct vx_object      * VXObject;
typedef struct vx_params      * VXParams;
typedef struct vx_proto       * VXProto;
typedef struct vx_pool        * VXPool;
typedef struct vx_scope       * VXScope;
typedef struct vx_slab        * VXSlab;
typedef struct vx_slot        * VXSlot;
typedef struct vx_stack       * VXStack;
typedef struct vx_viewer      * VXViewer;


/*--------------------------------------------------------------------------
 * main vx data structure
 *--------------------------------------------------------------------------*/

struct vx {
    VXBool          debug;
    VXBool          verbose;
};



/*--------------------------------------------------------------------------
 * Module loading and binding function pointers
 *--------------------------------------------------------------------------*/

typedef VXBool
(* VXBinder)(
    VXModule      module,
    VX            vx
);

typedef VXBool
(* VXLoader)(
    VXModule      module
);


#endif /* VX_TYPES_H */
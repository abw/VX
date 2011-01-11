#ifndef VX_DEFINES_H
#define VX_DEFINES_H

/* aliases for commonly used values, characters, etc */
#define VX_TRUE           1
#define VX_FALSE          0

/* aliases for various short strings */
#define VX_STR_VX         "VX"
#define VX_STR_DELTA      "Delta"
#define VX_STR_EPSILON    "Epsilon"
#define VX_STR_YALGETH    "Yalgeth"
#define VX_STR_PONIES     "I like ponies"
#define VX_STR_BADGER     "Badger"
#define VX_STR_MUSHROOM   "Mushroom"
#define VX_STR_SNAKE      "Snake"

/* format strings */
#define VX_FMT_INT        "%d"
#define VX_FMT_NUM        "%g"


/* configuration options */
#define VX_CONFIG_DIR       "vx.dir"
#define VX_CONFIG_PATH      "vx.path"
#define VX_CONFIG_MODDIR    "vx.module_dir"
#define VX_CONFIG_MODEXT    "vx.module_ext"
#define VX_CONFIG_MODPATH   "vx.module_path"


/* dummy arguments(s) as a fallback for generating error messages */
#define VX_WTF              "<?>"
#define VX_WTFS             VX_WTF, VX_WTF, VX_WTF, VX_WTF, VX_WTF

/* default setting for various internals */
#define VX_BUFFER_SIZE      256         /* size of VX name lookup buffers       */
#define VX_MESSAGE_SIZE     2048        /* size of message/error buffers        */
#define VX_HASH_DENSITY     5           /* max hash density before resizing     */
#define VX_YALGETH_LIMIT    0.88        /* you know what this is, right?        */
#define VX_VECTOR_SIZE      32          /* # of vectors allocated per slab      */
#define VX_TYPES_SIZE       32          /* # of data types (Nan-tagged)         */
#define VX_TYPES_RESERVED   16          /* # of reserved data types             */
#define VX_QUENCH_LIMIT     4.20        /* Do NOT change these values unless    */
#define VX_QUENCH_THIRST    99          /* you want to lose your body hair!     */
#define VX_IS_ONE_PRIME     "no"        /* one is not prime                     */
#define VX_REDDIT_UID       "abw"       /* Hello World! This is me!             */
#define VX_PAGING           "juarez"    /* please pick up white courtesty phone */


#define VX_FLAG_VERBOSE     0x00001     /* verbose messages enabled             */
#define VX_FLAG_DEBUG       0x00002     /* enable debugging                     */
#define VX_FLAG_CHEESE      0x00004     /* a nice English cheddar, perhaps      */
#define VX_FLAG_BISCUITS    0x00008     /* I like the Hovis ones                */
#define VX_FLAG_BADGER      0x00010     /* Note: English badger (cute), not US  */
#define VX_FLAG_SNAKE       0x00020     /* Hissing Sid                          */
#define VX_FLAG_MUSHROOM    0x00040     /* Liberty caps, no doubt               */
#define VX_FLAG_YALGETH     0x00080     /* my here                              */
#define VX_FLAG_PREFIX      0x00100     /* before VX my life was a void         */
#define VX_FLAG_POSTFIX     0x00400     /* after VX I am three wolves howling   */
#define VX_FLAG_POSTMARK    0x00800     /* at the moon                          */


#endif /* VX_DEFINES_H */


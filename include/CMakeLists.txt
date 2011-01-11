file(
    GLOB        VX_HEADERS
    vx/*.h
)

install (
    FILES       "${PROJECT_SOURCE_DIR}/include/vx.h" 
    DESTINATION include
)

install(
    FILES       ${VX_HEADERS}
    DESTINATION include/vx
)

install (
    FILES       "${PROJECT_BINARY_DIR}/include/vx/config.h" 
    DESTINATION include/vx
)

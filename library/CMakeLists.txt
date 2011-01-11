file(
    GLOB VX_LIBRARY_SOURCES 
    *.c 
)

add_library(
    vx_library
    SHARED
    ${VX_LIBRARY_SOURCES}
)

set_target_properties(
    vx_library
    PROPERTIES 
    OUTPUT_NAME vx
)

install (
    TARGETS     vx_library
    DESTINATION lib
)



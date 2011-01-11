add_executable(
    vx_program
    vx.c
)

set_target_properties(
    vx_program
    PROPERTIES 
    OUTPUT_NAME vx
)

target_link_libraries(
    vx_program
    vx_library
    ${PROGRAM_LIBS}
)

install (
    TARGETS     vx_program
    DESTINATION bin
)


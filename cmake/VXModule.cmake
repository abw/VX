macro(vx_module type name)
    add_library(
        vx_${type}_${name}
        MODULE
        ${name}.c
    )
    set_target_properties(
        vx_${type}_${name}
        PROPERTIES
        OUTPUT_NAME ${name}
        PREFIX      ""
        SUFFIX      ${VX_MODULE_EXT}
    )
    target_link_libraries(
        vx_${type}_${name}
        vx_library
    )
    install (
        TARGETS     vx_${type}_${name}
        DESTINATION ${VX_MODULE_DIR}/${type}
    )
endmacro(vx_module)

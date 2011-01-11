cmake_minimum_required (VERSION 2.8)

project (VX)
enable_testing()

set(VX_VERSION_MAJOR            0)
set(VX_VERSION_MINOR            1)
set(VX_NAME                     "VX")
set(VX_AUTHOR                   "Andy Wardley")
set(VX_EMAIL                    "vx@wardley.org")
set(VX_URL                      "http://wardley.org/vx/")
set(VX_DIR                      ${CMAKE_INSTALL_PREFIX}/${VX_NAME})
set(VX_SOURCE_DIR               ${PROJECT_SOURCE_DIR})
set(VX_TEST_DIR                 ${PROJECT_SOURCE_DIR}/tests)
set(VX_MODULE_DIR               "modules")
set(VX_MODULE_EXT               ".vxm")

set(CMAKE_MODULE_PATH           ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -g -Wall")

include(CheckIncludeFile)
check_include_file(dirent.h     VX_HAVE_DIRENT_H)
check_include_file(memory.h     VX_HAVE_MEMORY_H)
check_include_file(stdint.h     VX_HAVE_STDINT_H)
check_include_file(stdlib.h     VX_HAVE_STDLIB_H)
check_include_file(string.h     VX_HAVE_STRING_H)
check_include_file(strings.h    VX_HAVE_STRINGS_H)
check_include_file(inttypes.h   VX_HAVE_INTTYPES_H)
check_include_file(sys/stat.h   VX_HAVE_SYS_STAT_H)
check_include_file(sys/types.h  VX_HAVE_SYS_TYPES_H)
check_include_file(unistd.h     VX_HAVE_UNISTD_H)
check_include_file(windows.h    VX_HAVE_WINDOWS_H) 

include(CheckFunctionExists)
check_function_exists(bcopy     VX_HAVE_BCOPY)
check_function_exists(memmove   VX_HAVE_MEMMOVE)
check_function_exists(memset    VX_HAVE_MEMSET)
check_function_exists(strdup    VX_HAVE_STRDUP)
check_function_exists(strerror  VX_HAVE_STRERROR)
check_function_exists(strtol    VX_HAVE_STRTOL)
check_function_exists(strtoll   VX_HAVE_STRTOLL)
check_function_exists(strtoq    VX_HAVE_STRTOQ)

find_package( ReadLine REQUIRED )

# do we also need dl and/or other platform-specific library?
set(
    PROGRAM_LIBS 
    ${PROGRAM_LIBS} 
    readline m
)

# TODO: CMAKE_BUILD_TYPE

set(VX_DEBUG "" CACHE STRING "Set the debugging level")

if(VX_DEBUG)
    add_definitions( -DVX_DEBUG=${VX_DEBUG} )
endif(VX_DEBUG)

# Build the custom vx/config.h header file. 
# This feature alone makes CMake worth the price of admission.
configure_file (
    "${PROJECT_SOURCE_DIR}/include/vx/config.h.in"
    "${PROJECT_BINARY_DIR}/include/vx/config.h"
)

# location of header files for build
include_directories(
    "${PROJECT_BINARY_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include"
)

add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(programs)
#add_subdirectory(modules/codec)

# disabled while testing languages
add_subdirectory(tests)
#add_subdirectory(tests/core)

message(STATUS "Summary of configuration:") 
message(STATUS " + Project source dir ........... : ${PROJECT_SOURCE_DIR}") 
message(STATUS " + Project build dir ............ : ${PROJECT_BINARY_DIR}") 
message(STATUS " + Installation prefix .......... : ${CMAKE_INSTALL_PREFIX}") 
message(STATUS " + VX root dir .................. : ${VX_DIR}") 
message(STATUS " + Readline library ............. : ${READLINE_LIBRARY}") 
message(STATUS " + Ncurses library .............. : ${NCURSES_LIBRARY}") 
message(STATUS " + Compile flags ................ : ${CMAKE_C_FLAGS}") 
message(STATUS " + Debug level .................. : ${VX_DEBUG}") 

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${VX_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VX_VERSION_MINOR}")
include (CPack)

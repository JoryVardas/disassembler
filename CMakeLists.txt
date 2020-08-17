cmake_minimum_required(VERSION 3.13)

project(Disassembler VERSION 0.1 LANGUAGES CXX)

# Prevent in-source builds
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

# Make sure Windows exports all the symbols (exluding data symbols)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Settings for the library
add_library(Disassembler SHARED "")

configure_file(include/config.h.in include/config.h)

target_include_directories(Disassembler PUBLIC "${PROJECT_BINARY_DIR}/include")
target_include_directories(Disassembler PUBLIC include)

add_subdirectory(src)


# Settings for the app
add_executable(Disassembler-app "")
target_link_libraries(Disassembler-app PUBLIC Disassembler)

add_subdirectory(app)
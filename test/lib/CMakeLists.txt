add_subdirectory(Catch2)
add_subdirectory(fmt)

# Add Catch to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/extras/")

include(CTest)
include(Catch)

# Include unfmt headers
target_include_directories(Disassembler-app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")
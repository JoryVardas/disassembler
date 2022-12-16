add_subdirectory(Catch2)
add_subdirectory(fmt)

# Add Catch to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Catch2/extras/")

include(CTest)
include(Catch)

# Include unfmt headers
target_include_directories(Disassembler-app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

# Get Range-v3
include(FetchContent)

FetchContent_Declare(
        Range-v3
        GIT_REPOSITORY "https://github.com/ericniebler/range-v3"
        GIT_TAG master
)
FetchContent_MakeAvailable(Range-v3)
target_link_libraries(Disassembler-test PRIVATE range-v3)
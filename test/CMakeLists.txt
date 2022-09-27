add_executable(Disassembler-test "")
target_link_libraries(Disassembler-test PRIVATE Disassembler)

add_subdirectory(lib)


# Include Catch2 headers
# target_include_directories(Disassembler-test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/Catch2/src")

target_link_libraries(Disassembler-test PRIVATE Catch2::Catch2WithMain)

# find_package(fmt)
target_link_libraries(Disassembler-test PRIVATE fmt::fmt)

# target_sources(Disassembler-test PRIVATE x86Tests.cpp)

add_subdirectory(tests)

catch_discover_tests(Disassembler-test)
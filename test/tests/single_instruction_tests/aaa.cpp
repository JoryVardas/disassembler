#include "single_instruction_tests.h"
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("AAA", "[legacy]") {
    CREATE_LEGACY_DISASSEMBLER(disassembler);
    _DECODE_INSTRUCTION(disassembler,
                        _INSTRUCTION("AAA",
                                     _PREFIXES(_NO_PREFIX, _ALL_RAW_PREFIXES),
                                     OPCODE(0x37)));
}
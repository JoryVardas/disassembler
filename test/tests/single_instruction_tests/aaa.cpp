#include "single_instruction_tests.h"
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("AAA", "[legacy]") {
    CREATE_LEGACY_DISASSEMBLER(disassembler);
    DECODE_INSTRUCTION_(disassembler,
                        INSTRUCTION_("AAA",
                                     PREFIXES_(NO_PREFIX_, ALL_RAW_PREFIXES_),
                                     OPCODE(0x37)));
}
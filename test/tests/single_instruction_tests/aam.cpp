#include "single_instruction_tests.h"
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("AAM", "[x86][legacy]") {
    CREATE_LEGACY_DISASSEMBLER(disassembler);
    DECODE_INSTRUCTION_(disassembler,
                        INSTRUCTION_("AAM",
                                     PREFIXES_(NO_PREFIX_, ALL_RAW_PREFIXES_),
                                     OPCODE(0xD4), IMM8_));
}

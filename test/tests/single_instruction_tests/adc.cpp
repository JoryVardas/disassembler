#include "single_instruction_tests.h"
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("ADC", "[x86][legacy][x64]") {
    SECTION("ADC AL, {IMM8}") {
        CREATE_DISASSEMBLER(disassembler);
        DECODE_INSTRUCTION_(
            disassembler,
            INSTRUCTION_("ADC", PREFIXES_(NO_PREFIX_, ALL_RAW_PREFIXES_),
                         OPCODE(0x14), IMPLIED_("AL"), IMM8_));
    }
    SECTION("ADC {AX, EAX, RAX}, {IMM16, IMM32}") {
        CREATE_DISASSEMBLER(disassembler);
        DECODE_INSTRUCTION_(
            disassembler,
            INSTRUCTION_(
                "ADC",
                PREFIXES_(
                    NO_PREFIX_, ALL_RAW_PREFIXES_,
                    IF_X64_DISASSEMBLER_(disassembler, ALL_REX_PREFIXES_)),
                OPCODE(0x15),
                SWITCH_(OPT_(ON_X16_PARAMETER_, IMPLIED_("AX")),
                        OPT_(ON_X32_PARAMETER_, IMPLIED_("EAX")),
                        OPT_(ON_X64_PARAMETER_, IMPLIED_("RAX"))),
                IF_(CONDITION_(ON_X16_PARAMETER_), IMM16_, ELSE_(IMM32_))));
    }
    SECTION("ADC RM8, IMM8") {
        CREATE_DISASSEMBLER(disassembler);
        DECODE_INSTRUCTION_(
            disassembler,
            INSTRUCTION_(
                "ADC",
                PREFIXES_(
                    NO_PREFIX_, ALL_RAW_PREFIXES_,
                    IF_X64_DISASSEMBLER_(disassembler, ALL_REX_PREFIXES_)),
                OPCODE(0x15),
                SWITCH_(OPT_(ON_X16_PARAMETER_, IMPLIED_("AX")),
                        OPT_(ON_X32_PARAMETER_, IMPLIED_("EAX")),
                        OPT_(ON_X64_PARAMETER_, IMPLIED_("RAX"))),
                IF_(CONDITION_(ON_X16_PARAMETER_), IMM16_, ELSE_(IMM32_))));
    }
}

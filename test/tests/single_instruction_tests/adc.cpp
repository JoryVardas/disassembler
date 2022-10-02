#include "single_instruction_tests.h"
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("ADC", "[x86][legacy][x64]") {
    SECTION("ADC AL, {IMM8}") {
        CREATE_DISASSEMBLER(disassembler);
        _DECODE_INSTRUCTION(
            disassembler,
            _INSTRUCTION("ADC", _PREFIXES(_NO_PREFIX, _ALL_RAW_PREFIXES),
                         OPCODE(0x14), _IMPLIED("AL"), _IMM8));
    }
    SECTION("ADC {AX, EAX, RAX}, {IMM16, IMM32}") {
        CREATE_DISASSEMBLER(disassembler);
        _DECODE_INSTRUCTION(
            disassembler,
            _INSTRUCTION("ADC",
                         _PREFIXES(_NO_PREFIX, _ALL_RAW_PREFIXES,
                                   _IF_X64_DISASSEMBLER(disassembler,
                                                        _ALL_REX_PREFIXES)),
                         OPCODE(0x15),
                         _SWITCH(_OPT(_CONDITION(_ON_X16), _IMPLIED("AX")),
                                 _OPT(_CONDITION(_ON_X32), _IMPLIED("EAX")),
                                 _OPT(_CONDITION(_ON_X64), _IMPLIED("RAX"))),
                         _SWITCH(_OPT(_CONDITION(_ON_X16), _IMM16),
                                 _OPT(_CONDITION(_ON_X32), _IMM32),
                                 _OPT(_CONDITION(_ON_X64), _IMM32))));
    }
    SECTION("ADC RM8, IMM8") {
        CREATE_DISASSEMBLER(disassembler);
        _DECODE_INSTRUCTION(
            disassembler,
            _INSTRUCTION("ADC",
                         _PREFIXES(_NO_PREFIX, _ALL_RAW_PREFIXES,
                                   _IF_X64_DISASSEMBLER(disassembler,
                                                        _ALL_REX_PREFIXES)),
                         OPCODE(0x15),
                         _SWITCH(_OPT(_CONDITION(_ON_X16), _IMPLIED("AX")),
                                 _OPT(_CONDITION(_ON_X32), _IMPLIED("EAX")),
                                 _OPT(_CONDITION(_ON_X64), _IMPLIED("RAX"))),
                         _SWITCH(_OPT(_CONDITION(_ON_X16), _IMM16),
                                 _OPT(_CONDITION(_ON_X32), _IMM32),
                                 _OPT(_CONDITION(_ON_X64), _IMM32))));
    }
}

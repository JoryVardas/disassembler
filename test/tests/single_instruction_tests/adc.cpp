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
    // TEST_CASE("ADC RM8, IMM8", "[ADC][x86][x64]") {
    //     CREATE_DISASSEMBLER(disassembler);
    //
    //     imm_set imms = GENERATE_IMM_SET;
    //     disp_set disp = GENERATE_IMM_SET;
    //
    //     SECTION("no prefix") {
    //         SECTION("address") {
    //             if (disassembler_env._defaultAdressMode ==
    //                 X86Environment::X86AddressMode::X16) {
    //                 imm op2 = GET_IMM8(imms);
    //                 prefix_t cs = CS_SEGMENT_OVERRIDE_PREFIX;
    //                 address_t op1 = GENERATE_MODRM16_RM(BYTE_PTR, disp, cs);
    //
    //                 DECODE_INSTRUCTION(disassembler, decodedInstruction,
    //                                    PREFIXES(cs), OPCODE(0x80),
    //                                    MODRM(disassembler, op1, FIXED_R(2)),
    //                                    IMM_TO_BYTES(disassembler, op2));
    //
    //                 REQUIRE(decodedInstruction->toString() ==
    //                         fmt::format("ADC {}, {:#x}", op1.str,
    //                                     IMM_TO_BIG_ENDIAN(op2)));
    //             }
    //         }
    //     }
    // }
}

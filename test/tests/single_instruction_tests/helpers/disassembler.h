#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_DISASSEMBLER_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_DISASSEMBLER_HELPERS_H

#include <architecture/x86/x86Disassembler.h>
#include <architecture/x86/x86Environment.h>
#include <catch2/generators/catch_generators.hpp>

#define CREATE_DISASSEMBLER(name)                                              \
    X86Environment name##_env = GENERATE(                                      \
        generateX86Environment(X86Environment::X86InstructionMode::BOTH));     \
    X86Disassembler name(name##_env)

#define CREATE_LEGACY_DISASSEMBLER(name)                                       \
    X86Environment name##_env = GENERATE(                                      \
        generateX86Environment(X86Environment::X86InstructionMode::LEGACY));   \
    X86Disassembler name(name##_env)
#define CREATE_X64_DISASSEMBLER(name)                                          \
    X86Environment name##_env = GENERATE(                                      \
        generateX86Environment(X86Environment::X86InstructionMode::X64));      \
    X86Disassembler name(name##_env)

#define DISASSEMBLER_PARAMETER_MODE(disassembler)                              \
    disassembler##_env._defaultParameterMode
#define DISASSEMBLER_ADDRESS_MODE(disassembler)                                \
                                                                               \
    disassembler##_env._defaultAddressMode
#define DISASSEMBLER_INSTRUCTION_MODE(disassembler)                            \
                                                                               \
    disassembler##_env._defaultInstructionMode

#define PARAMETER_MODE_X16 X86Environment::X86ParameterMode::X16
#define PARAMETER_MODE_X32 X86Environment::X86ParameterMode::X32
#define PARAMETER_MODE_X64 X86Environment::X86ParameterMode::X64
#define ADDRESS_MODE_X16 X86Environment::X86AddressMode::X16
#define ADDRESS_MODE_X32 X86Environment::X86AddressMode::X32
#define ADDRESS_MODE_X64 X86Environment::X86AddressMode::X64
#define INSTRUCTION_MODE_LEGACY X86Environment::X86InstructionMode::LEGACY
#define INSTRUCTION_MODE_X64 X86Environment::X86InstructionMode::X64

#define DISASSEMBLER_ENDIANNESS_NATIVE(disassembler)                           \
    disassembler##_env._endianness == std::endian::native

#endif
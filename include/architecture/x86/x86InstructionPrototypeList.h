#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPELIST_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPELIST_H

#include <vector>

#include "x86InstructionPrototype.h"


#define ANY_PREFIX std::vector<X86InstructionPrefix>()
#define PREFIX_LIST(...) std::vector<X86InstructionPrefix>{__VA_ARGS__}
#define PREFIX_66 X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE
#define PREFIX_67 X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE

#define imm8 X86InstructionImmediateParameterPrototypeSpecification<8>()
#define imm16 X86InstructionImmediateParameterPrototypeSpecification<16>()
#define imm32 X86InstructionImmediateParameterPrototypeSpecification<32>()
#define r8 X86InstructionRegisterParameterPrototypeSpecification<8>()
#define r16 X86InstructionRegisterParameterPrototypeSpecification<16>()
#define r32 X86InstructionRegisterParameterPrototypeSpecification<32>()
#define r64 X86InstructionRegisterParameterPrototypeSpecification<64>()
#define m8 X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::BYTE_PTR>()
#define m16 X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::WORD_PTR>()
#define m32 X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::DWORD_PTR>()
#define m64 X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::QWORD_PTR>()
#define rm8 r8, m8
#define rm16 r16, m16
#define rm32 r32, m32
#define rm64

#define AL X86InstructionSingleRegisterParameterPrototypeSpecification("AL")
#define AX X86InstructionSingleRegisterParameterPrototypeSpecification("AX")
#define EAX X86InstructionSingleRegisterParameterPrototypeSpecification("EAX")
#define RAX X86InstructionSingleRegisterParameterPrototypeSpecification("RAX")

#define MODE X86Environment::X86InstructionMode
#define LOCATION X86InstructionParameterLocation
#define STANDARD_COMPARISON {}
#define PARAMETER(location, ...) {LOCATION::location, {__VA_ARGS__}}

const std::vector<X86InstructionPrototype> X86InstructionPrototypeList {
    {"AAA", MODE::LEGACY, 0x37},

    {"AAD", MODE::LEGACY, ANY_PREFIX, 0xD5, {PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},

    {"AAM", MODE::LEGACY, ANY_PREFIX, 0XD4, {PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},

    {"AAS", MODE::LEGACY, 0x3F},

    {"ADC", MODE::BOTH, ANY_PREFIX, 0x14, {PARAMETER(IMPLIED, AL), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x15, {PARAMETER(IMPLIED, AX, EAX, RAX), PARAMETER(IMMEDIATE, imm16, imm32)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x80, 2, {PARAMETER(MODRM_RM, rm8), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x81, 2, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(IMMEDIATE, imm16, imm32)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x83, 2, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x10, {PARAMETER(MODRM_RM, rm8), PARAMETER(MODRM_REG, r8)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x11, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(MODRM_REG, r16, r32, r64)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x12, {PARAMETER(MODRM_REG, r8), PARAMETER(MODRM_RM, rm8)}, STANDARD_COMPARISON},
    {"ADC", MODE::BOTH, ANY_PREFIX, 0x13, {PARAMETER(MODRM_REG, r16, r32, r64), PARAMETER(MODRM_RM, rm16, rm32, rm64)}, STANDARD_COMPARISON},

    {"ADCX", MODE::BOTH, PREFIX_LIST(PREFIX_66), 0x0f38f6, {PARAMETER(MODRM_REG, r32, r64), PARAMETER(MODRM_RM, rm32, rm64)}, STANDARD_COMPARISON},

    {"ADD", MODE::BOTH, ANY_PREFIX, 0x04, {PARAMETER(IMPLIED, AL), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x05, {PARAMETER(IMPLIED, AX, EAX, RAX), PARAMETER(IMMEDIATE, imm16, imm32)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x80, 0, {PARAMETER(MODRM_RM, rm8), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x81, 0, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(IMMEDIATE, imm16, imm32)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x83, 0, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(IMMEDIATE, imm8)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x00, {PARAMETER(MODRM_RM, rm8), PARAMETER(MODRM_REG, r8)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x01, {PARAMETER(MODRM_RM, rm16, rm32, rm64), PARAMETER(MODRM_REG, r16, r32, r64)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x02, {PARAMETER(MODRM_REG, r8), PARAMETER(MODRM_RM, rm8)}, STANDARD_COMPARISON},
    {"ADD", MODE::BOTH, ANY_PREFIX, 0x03, {PARAMETER(MODRM_REG, r16, r32, r64), PARAMETER(MODRM_RM, rm16, rm32, rm64)}, STANDARD_COMPARISON},


};


#undef ANY_PREFIX
#undef PREFIX_66
#undef PREFIX_67

#undef imm8
#undef imm16
#undef imm32
#undef r8
#undef r16
#undef r32
#undef r64
#undef m8
#undef m16
#undef m32
#undef m64
#undef rm8
#undef rm16
#undef rm32
#undef rm64

#undef AL
#undef AX
#undef EAX
#undef RAX

#undef MODE
#undef LOCATION
#undef STANDARD_COMPARISON
#undef PARAMETER

#endif
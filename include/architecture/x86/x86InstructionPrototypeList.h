#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPELIST_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPELIST_H

#include <vector>

#include "x86InstructionPrototype.h"


#define ANY_PREFIX std::vector<X86InstructionPrefix>()

#define imm8 std::make_shared<X86InstructionImmediateParameterPrototypeSpecification<8>>()
#define imm16 std::make_shared<X86InstructionImmediateParameterPrototypeSpecification<16>>()
#define imm32 std::make_shared<X86InstructionImmediateParameterPrototypeSpecification<32>>()
#define r8 std::make_shared<X86InstructionRegisterParameterPrototypeSpecification<8>>()
#define r16 std::make_shared<X86InstructionRegisterParameterPrototypeSpecification<16>>()
#define r32 std::make_shared<X86InstructionRegisterParameterPrototypeSpecification<32>>()
#define m8 std::make_shared<X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::BYTE_PTR>>()
#define m16 std::make_shared<X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::WORD_PTR>>()
#define m32 std::make_shared<X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::DWORD_PTR>>()
#define rm8 r8, m8
#define rm16 r16, m16
#define rm32 r32, m32
#define rm64 /*r64, m64*/

#define AL std::make_shared<X86InstructionSingleRegisterParameterPrototypeSpecification>("AL")
#define AX std::make_shared<X86InstructionSingleRegisterParameterPrototypeSpecification>("AX")
#define EAX std::make_shared<X86InstructionSingleRegisterParameterPrototypeSpecification>("EAX")
#define RAX /*std::make_shared<X86InstructionSingleRegisterParameterPrototypeSpecification>("RAX")*/

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
    //{"AAD", ANY_PREFIX, 0xd5, {{X86InstructionParameterLocation::IMMEDIATE, {imm8}}}, {}},
    //{"ADC", ANY_PREFIX, 0x80, 2, {{X86InstructionParameterLocation::MODRM_RM, {r8, m8}}, {X86InstructionParameterLocation::IMMEDIATE, {imm8}}}, {}},
    //{"ADC", ANY_PREFIX, 0x81, 2, {{X86InstructionParameterLocation::MODRM_RM, {r16, r32, m16, m32}}, {X86InstructionParameterLocation::IMMEDIATE, {imm16, imm32}}}, {}}
};


#undef ANY_PREFIX

#undef imm8
#undef imm16
#undef imm32
#undef r8
#undef r16
#undef r32
#undef m8
#undef m16
#undef m32

#undef AL
#undef AX
#undef EAX
#undef RAX

#undef MODE
#undef LOCATION
#undef STANDARD_COMPARISON
#undef PARAMETER

#endif
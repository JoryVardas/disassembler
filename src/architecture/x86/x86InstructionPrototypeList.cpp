#include <architecture\x86\x86InstructionPrototypeList.h>

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

const std::vector<X86InstructionPrototype> X86InstructionPrototypeList = {
    {"AAA", 0x37},
    {"AAD", ANY_PREFIX, 0xd5, {{X86InstructionParameterLocation::IMMEDIATE, {imm8}}}, {}},
    {"ADC", ANY_PREFIX, 0x80, 2, {{X86InstructionParameterLocation::MODRM_RM, {r8, m8}}, {X86InstructionParameterLocation::IMMEDIATE, {imm8}}}, {}},
    {"ADC", ANY_PREFIX, 0x81, 2, {{X86InstructionParameterLocation::MODRM_RM, {r16, r32, m16, m32}}, {X86InstructionParameterLocation::IMMEDIATE, {imm16, imm32}}}, {}}
};
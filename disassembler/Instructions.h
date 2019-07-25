#pragma once

#include "Common.h"
#include "Registers.h"
#include "Prefixes.h"

typedef uint64_t operandType_t;
enum : operandType_t {
	OPERAND_TYPE_NO_OPERANDS	= 0,
	OPERAND_TYPE_REL8			= 1ULL << 0,
	OPERAND_TYPE_REL16			= 1ULL << 1,
	OPERAND_TYPE_REL32			= 1ULL << 2,
	OPERAND_TYPE_PTR16_16		= 1ULL << 3,
	OPERAND_TYPE_PTR16_32		= 1ULL << 4,
	OPERAND_TYPE_R8				= 1ULL << 5,
	OPERAND_TYPE_R16			= 1ULL << 6,
	OPERAND_TYPE_R32			= 1ULL << 7,
	OPERAND_TYPE_R64			= 1ULL << 8,
	OPERAND_TYPE_IMM8			= 1ULL << 9,
	OPERAND_TYPE_IMM16			= 1ULL << 10,
	OPERAND_TYPE_IMM32			= 1ULL << 11,
	OPERAND_TYPE_IMM64			= 1ULL << 12,
	OPERAND_TYPE_M8				= 1ULL << 13,
	OPERAND_TYPE_M16			= 1ULL << 14,
	OPERAND_TYPE_M32			= 1ULL << 15,
	OPERAND_TYPE_M64			= 1ULL << 16,
	OPERAND_TYPE_M128			= 1ULL << 17,
	OPERAND_TYPE_M16_16			= 1ULL << 18,
	OPERAND_TYPE_M16_32			= 1ULL << 19,
	OPERAND_TYPE_M16_64			= 1ULL << 20,
	OPERAND_TYPE_M16__32		= 1ULL << 21,
	OPERAND_TYPE_M16__16		= 1ULL << 22,
	OPERAND_TYPE_M32__32		= 1ULL << 23,
	OPERAND_TYPE_M16__64		= 1ULL << 24,
	OPERAND_TYPE_MOFFS8			= 1ULL << 25,
	OPERAND_TYPE_MOFFS16		= 1ULL << 26,
	OPERAND_TYPE_MOFFS32		= 1ULL << 27,
	OPERAND_TYPE_MOFFS64		= 1ULL << 28,
	OPERAND_TYPE_SREG			= 1ULL << 29,
	OPERAND_TYPE_M32FP			= 1ULL << 30,
	OPERAND_TYPE_M64FP			= 1ULL << 31,
	OPERAND_TYPE_M80FP			= 1ULL << 32,
	OPERAND_TYPE_M16INT			= 1ULL << 33,
	OPERAND_TYPE_M32INT			= 1ULL << 34,
	OPERAND_TYPE_M64INT			= 1ULL << 35,
	OPERAND_TYPE_ST0			= 1ULL << 36, //should this be moved to implicit?
	OPERAND_TYPE_ST				= 1ULL << 37,
	OPERAND_TYPE_MM				= 1ULL << 38,
	OPERAND_TYPE_XMM			= 1ULL << 39,
	OPERAND_TYPE_YMM			= 1ULL << 40,
	OPERAND_TYPE_M256			= 1ULL << 41,
	OPERAND_TYPE_BND			= 1ULL << 42,
	OPERAND_TYPE_MIB			= 1ULL << 43,
	OPERAND_TYPE_ZMM			= 1ULL << 44,
	OPERAND_TYPE__K_Z_			= 1ULL << 45,
	OPERAND_TYPE__K_			= 1ULL << 46,
	OPERAND_TYPE_K				= 1ULL << 47,
	OPERAND_TYPE_MV				= 1ULL << 48,
	OPERAND_TYPE_VM32			= 1ULL << 49,
	OPERAND_TYPE_VM64			= 1ULL << 50,
	OPERAND_TYPE_M32BCST		= 1ULL << 51,
	OPERAND_TYPE_M64BCST		= 1ULL << 52,
	OPERAND_TYPE_IMPLICIT_AL	= 1ULL << 53,
	OPERAND_TYPE_IMPLICIT_AX	= 1ULL << 54,
	OPERAND_TYPE_IMPLICIT_EAX	= 1ULL << 55,
	OPERAND_TYPE_IMPLICIT_RAX	= 1ULL << 56,
	OPERAND_TYPE_IMPLICIT_XMM0	= 1ULL << 57,
	OPERAND_TYPE_IMPLICIT_YMM0	= 1ULL << 58,
	OPERAND_TYPE_IMPLICIT_ZMM0	= 1ULL << 59
};

#define OPERAND_TYPE_R16_32_64 OPERAND_TYPE_R16 | OPERAND_TYPE_R32 | OPERAND_TYPE_R64
#define OPERAND_TYPE_M16_32_64 OPERAND_TYPE_M16 | OPERAND_TYPE_M32 | OPERAND_TYPE_M64
#define OPERAND_TYPE_RM16_32_64 OPERAND_TYPE_R16_32_64 | OPERAND_TYPE_M16_32_64
#define OPERAND_TYPE_RM8 OPERAND_TYPE_R8 | OPERAND_TYPE_M8
#define OPERAND_TYPE_RM16 OPERAND_TYPE_R16 | OPERAND_TYPE_M16
#define OPERAND_TYPE_RM32 OPERAND_TYPE_R32 | OPERAND_TYPE_M32
#define OPERAND_TYPE_RM64 OPERAND_TYPE_R64 | OPERAND_TYPE_M64
#define OPERAND_TYPE_IMM16_32 OPERAND_TYPE_IMM16 | OPERAND_TYPE_IMM32
#define OPERAND_TYPE_R32_64 OPERAND_TYPE_R32 | OPERAND_TYPE_R64
#define OPERAND_TYPE_RM32_64 OPERAND_TYPE_RM32 | OPERAND_TYPE_RM64
#define OPERAND_TYPE_IMPLICIT_AX_EAX_RAX OPERAND_TYPE_IMPLICIT_AX | OPERAND_TYPE_IMPLICIT_EAX | OPERAND_TYPE_IMPLICIT_RAX
#define OPERAND_TYPE_XMM_M128 OPERAND_TYPE_XMM | OPERAND_TYPE_M128
#define OPERAND_TYPE_IMPLICIT_XMM0_YMM0_ZMM0 OPERAND_TYPE_IMPLICIT_XMM0 | OPERAND_TYPE_IMPLICIT_YMM0 | OPERAND_TYPE_IMPLICIT_ZMM0
#define OPERAND_TYPE_XMM_YMM_ZMM OPERAND_TYPE_XMM | OPERAND_TYPE_YMM | OPERAND_TYPE_ZMM

#define operandTypeHasFlags(operandType, flags) ((operandType & (flags)) == (flags))
#define operandTypeHasSomeFlags(operandType, flags) ((operandType & (flags)) > 0)

typedef uint8_t instructionOperandEncoding_t;
enum : instructionOperandEncoding_t {
	INSTRUCTION_OPERAND_ENCODING_NA,
	INSTRUCTION_OPERAND_ENCODING_IMPLIED_AX_IMM,
	INSTRUCTION_OPERAND_ENCODING_R_RM,
	INSTRUCTION_OPERAND_ENCODING_RM_R,
	INSTRUCTION_OPERAND_ENCODING_RM_IMM,
	INSTRUCTION_OPERAND_ENCODING_R_VEC_RM,
	INSTRUCTION_OPERAND_ENCODING_R_RM_IMM,
	INSTRUCTION_OPERAND_ENCODING_R_RM_VEC,
	INSTRUCTION_OPERAND_ENCODING_R_RM_IMPLIED_XMM0,
	INSTRUCTION_OPERAND_ENCODING_IMM
};

typedef uint8_t instructionEnvironment_t;
enum : instructionEnvironment_t {
	INSTRUCTION_ENVIRONMENT_NO_ENVIRONMENT = 0,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_0 = 1,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_1 = 2,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_2 = 3,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_3 = 4,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_4 = 5,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_5 = 6,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_6 = 7,
	INSTRUCTION_ENVIRONMENT_MODRM_REG_7 = 8,
	INSTRUCTION_ENVIRONMENT_OPCODE_HAS_REG = 1 << 4,
	INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_66 = 1 << 5,
	INSTRUCTION_ENVIRONMENT_REQUIRES_PREFIX_67 = 1 << 6
};
#define INSTRUCTION_ENVIRONMENT_MODRM_REG 0x0F
#define INSTRUCTION_ENVIRONMENT_HAS_FLAGS(env, flags) ((env & flags) == flags)


typedef uint32_t opcode_t;
typedef uint32_t instructionNameIndex_t;
typedef uint64_t instructionId_t;

struct InstructionInfo {
	instructionNameIndex_t name;
	prefixContext_t prefixContext;
	opcode_t opcode;
	instructionEnvironment_t instructionEnvironment;

};

extern uint64_t instructionListLength;
extern InstructionInfo instructionList[];

extern instructionOperandEncoding_t instructionOperandEncoding[];
extern cstring_t instructionName[];

struct InstructionOperand {
	operandType_t operand1;
	operandType_t operand2;
	operandType_t operand3;
	operandType_t operand4;
};

extern InstructionOperand instructionOperands[];

typedef uint8_t addressSize_t;
typedef uint8_t operandSize_t;
enum : addressSize_t {
	ADDRESS_SIZE_16,
	ADDRESS_SIZE_32,
	ADDRESS_SIZE_64
};
enum : operandSize_t {
	OPERAND_SIZE_16,
	OPERAND_SIZE_32,
	OPERAND_SIZE_64
};


typedef uint8_t decodedOperandType_t;
enum : decodedOperandType_t {
	DECODED_OPERAND_TYPE_NO_OPERAND = 0,
	DECODED_OPERAND_TYPE_REGISTER,
	DECODED_OPERAND_TYPE_MEM,
	DECODED_OPERAND_TYPE_IMMEDIATE
};

struct DecodedInstruction {
	struct DecodedOperand {
		decodedOperandType_t decodedOperandType;
		union
		{
			uint64_t immediate;
			struct {
				//enum {
				//	DECODED_OPERAND_REG_FORMAT_REG,
				//	DECODED_OPERAND_REG_FORMAT_REG_K,
				//	DECODED_OPERAND_REG_FORMAT_REG_K_Z
				//} format;
				register_t reg;
				uint8_t k_register : 3;
				bool z_mask_used : 1;
				bool kzFieldsUsed : 1;
			} reg;
			struct {
				segmentRegister_t segment;
				//enum {
				//	DECODED_OPERAND_MEMORY_FORMAT_REG, // includes reg*s+disp
				//	DECODED_OPERAND_MEMORY_FORMAT_DISP, // includes disp
				//	DECODED_OPERAND_MEMORY_FORMAT_REG_REG //includes reg*s+reg+disp
				//} format;
				register_t baseReg;
				register_t scaledReg;
				uint8_t scalar;
				uint64_t disp;
			} memory;
		} operandData;
	};

	instructionId_t instruction;
	DecodedOperand operand1;
	DecodedOperand operand2;
	DecodedOperand operand3;
	DecodedOperand operand4;
	uint64_t startPosition;
};
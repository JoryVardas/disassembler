#pragma once

#include "Common.h"

typedef uint8_t segmentRegister_t;
enum : segmentRegister_t {
	SEGMENT_REGISTER_NO_REGISTER = 0,
	SEGMENT_REGISTER_CS,
	SEGMENT_REGISTER_SS,
	SEGMENT_REGISTER_DS,
	SEGMENT_REGISTER_ES,
	SEGMENT_REGISTER_FS,
	SEGMENT_REGISTER_GS
};

typedef uint16_t register_t;
enum : register_t {
	REGISTER_NO_REGISTER = 0,
	REGISTER_INVALID_REGISTER = 1,
	//general purpose byte registers
	REGISTER_AL,
	REGISTER_BL,
	REGISTER_CL,
	REGISTER_DL,
	REGISTER_AH,
	REGISTER_BH,
	REGISTER_CH,
	REGISTER_DH,
	REGISTER_R8B,
	REGISTER_R9B,
	REGISTER_R10B,
	REGISTER_R11B,
	REGISTER_R12B,
	REGISTER_R13B,
	REGISTER_R14B,
	REGISTER_R15B,
	//general purpose word registers
	REGISTER_AX,
	REGISTER_BX,
	REGISTER_CX,
	REGISTER_DX,
	REGISTER_DI,
	REGISTER_SI,
	REGISTER_BP,
	REGISTER_SP,
	REGISTER_R8W,
	REGISTER_R9W,
	REGISTER_R10W,
	REGISTER_R11W,
	REGISTER_R12W,
	REGISTER_R13W,
	REGISTER_R14W,
	REGISTER_R15W,
	//general purpose double word registers
	REGISTER_EAX,
	REGISTER_EBX,
	REGISTER_ECX,
	REGISTER_EDX,
	REGISTER_EDI,
	REGISTER_ESI,
	REGISTER_EBP,
	REGISTER_ESP,
	REGISTER_R8D,
	REGISTER_R9D,
	REGISTER_R10D,
	REGISTER_R11D,
	REGISTER_R12D,
	REGISTER_R13D,
	REGISTER_R14D,
	REGISTER_R15D,
	//general purpose quad word registers
	REGISTER_RAX,
	REGISTER_RBX,
	REGISTER_RCX,
	REGISTER_RDX,
	REGISTER_RDI,
	REGISTER_RSI,
	REGISTER_RBP,
	REGISTER_RSP,
	REGISTER_R8,
	REGISTER_R9,
	REGISTER_R10,
	REGISTER_R11,
	REGISTER_R12,
	REGISTER_R13,
	REGISTER_R14,
	REGISTER_R15,
	//segment registers (16bit)
	REGISTER_CS,
	REGISTER_DS,
	REGISTER_SS,
	REGISTER_ES,
	REGISTER_FS,
	REGISTER_GS,
	//FLAGS registers
	REGISTER_EFLAGS, //32bit
	REGISTER_RFLAGS, //64bit
	//x87 FPU registers (80bit)
	REGISTER_ST0,
	REGISTER_ST1,
	REGISTER_ST2,
	REGISTER_ST3,
	REGISTER_ST4,
	REGISTER_ST5,
	REGISTER_ST6,
	REGISTER_ST7,
	//MMX regIsters
	REGISTER_MM0,
	REGISTER_MM1,
	REGISTER_MM2,
	REGISTER_MM3,
	REGISTER_MM4,
	REGISTER_MM5,
	REGISTER_MM6,
	REGISTER_MM7,
	//debug registesr
	REGISTER_DR0,
	REGISTER_DR1,
	REGISTER_DR2,
	REGISTER_DR3,
	REGISTER_DR4,
	REGISTER_DR5,
	REGISTER_DR6,
	REGISTER_DR7,
	//control registers
	REGISTER_CR0,
	REGISTER_CR1,
	REGISTER_CR2,
	REGISTER_CR3,
	REGISTER_CR4,
	REGISTER_CR5,
	REGISTER_CR6,
	REGISTER_CR7,
	REGISTER_CR8,
	//ZMM registers
	REGISTER_ZMM0,
	REGISTER_ZMM1,
	REGISTER_ZMM2,
	REGISTER_ZMM3,
	REGISTER_ZMM4,
	REGISTER_ZMM5,
	REGISTER_ZMM6,
	REGISTER_ZMM7,
	REGISTER_ZMM8,
	REGISTER_ZMM9,
	REGISTER_ZMM10,
	REGISTER_ZMM11,
	REGISTER_ZMM12,
	REGISTER_ZMM13,
	REGISTER_ZMM14,
	REGISTER_ZMM15,
	REGISTER_ZMM16,
	REGISTER_ZMM17,
	REGISTER_ZMM18,
	REGISTER_ZMM19,
	REGISTER_ZMM20,
	REGISTER_ZMM21,
	REGISTER_ZMM22,
	REGISTER_ZMM23,
	REGISTER_ZMM24,
	REGISTER_ZMM25,
	REGISTER_ZMM26,
	REGISTER_ZMM27,
	REGISTER_ZMM28,
	REGISTER_ZMM29,
	REGISTER_ZMM30,
	REGISTER_ZMM31,
	//YMM registers
	REGISTER_YMM0,
	REGISTER_YMM1,
	REGISTER_YMM2,
	REGISTER_YMM3,
	REGISTER_YMM4,
	REGISTER_YMM5,
	REGISTER_YMM6,
	REGISTER_YMM7,
	REGISTER_YMM8,
	REGISTER_YMM9,
	REGISTER_YMM10,
	REGISTER_YMM11,
	REGISTER_YMM12,
	REGISTER_YMM13,
	REGISTER_YMM14,
	REGISTER_YMM15,
	REGISTER_YMM16,
	REGISTER_YMM17,
	REGISTER_YMM18,
	REGISTER_YMM19,
	REGISTER_YMM20,
	REGISTER_YMM21,
	REGISTER_YMM22,
	REGISTER_YMM23,
	REGISTER_YMM24,
	REGISTER_YMM25,
	REGISTER_YMM26,
	REGISTER_YMM27,
	REGISTER_YMM28,
	REGISTER_YMM29,
	REGISTER_YMM30,
	REGISTER_YMM31,
	//XMM registers
	REGISTER_XMM0,
	REGISTER_XMM1,
	REGISTER_XMM2,
	REGISTER_XMM3,
	REGISTER_XMM4,
	REGISTER_XMM5,
	REGISTER_XMM6,
	REGISTER_XMM7,
	REGISTER_XMM8,
	REGISTER_XMM9,
	REGISTER_XMM10,
	REGISTER_XMM11,
	REGISTER_XMM12,
	REGISTER_XMM13,
	REGISTER_XMM14,
	REGISTER_XMM15,
	REGISTER_XMM16,
	REGISTER_XMM17,
	REGISTER_XMM18,
	REGISTER_XMM19,
	REGISTER_XMM20,
	REGISTER_XMM21,
	REGISTER_XMM22,
	REGISTER_XMM23,
	REGISTER_XMM24,
	REGISTER_XMM25,
	REGISTER_XMM26,
	REGISTER_XMM27,
	REGISTER_XMM28,
	REGISTER_XMM29,
	REGISTER_XMM30,
	REGISTER_XMM31,
	//opmask registers
	REGISTER_K0,
	REGISTER_K1,
	REGISTER_K2,
	REGISTER_K3,
	REGISTER_K4,
	REGISTER_K5,
	REGISTER_K6,
	REGISTER_K7,
	//entry to specify total number of entries in the enum.
	REGISTER_COUNT
};

extern uint16_t registerSize[REGISTER_COUNT];

extern cstring_t segmentRegisterToString[];
extern cstring_t registerToString[];
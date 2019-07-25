#pragma once

#include "Common.h"
#include "Registers.h"

typedef uint8_t prefix_t;
enum : prefix_t {
	PREFIX_NO_PREFIX = 0,
	PREFIX_F0, // LOCK
	PREFIX_F2, // REPNE/REPNZ *or* BND
	PREFIX_F3, // REP *or* REPE/REPZ
	PREFIX_2E, // CS segment override *or* branch not taken 
	PREFIX_36, // SS segment override
	PREFIX_3E, // DS segment override *or* branch taken
	PREFIX_26, // ES segment override
	PREFIX_64, // FS segment override
	PREFIX_65, // GS segment override
	PREFIX_66, // operand size override
	PREFIX_67, // address size override
	PREFIX_COUNT
};

typedef uint32_t prefixContext_t;
//A bit mask map for the prefixes and state which are required for an instruction.
//
enum : prefixContext_t {
	PREFIX_CONTEXT_PREFIX_NOT_REQUIRED  = 0,
	PREFIX_CONTEXT_PREFIX_F0			= 1ULL << 0,
	PREFIX_CONTEXT_PREFIX_F2			= 1ULL << 1,
	PREFIX_CONTEXT_PREFIX_F3			= 1ULL << 2,
	PREFIX_CONTEXT_PREFIX_2E			= 1ULL << 3,
	PREFIX_CONTEXT_PREFIX_36			= 1ULL << 4,
	PREFIX_CONTEXT_PREFIX_3E			= 1ULL << 5,
	PREFIX_CONTEXT_PREFIX_26			= 1ULL << 6,
	PREFIX_CONTEXT_PREFIX_64			= 1ULL << 7,
	PREFIX_CONTEXT_PREFIX_65			= 1ULL << 8,
	PREFIX_CONTEXT_PREFIX_66			= 1ULL << 9,
	PREFIX_CONTEXT_PREFIX_67			= 1ULL << 10,
	PREFIX_CONTEXT_REX					= 1ULL << 11,
	PREFIX_CONTEXT_REX_W0				= 1ULL << 12,
	PREFIX_CONTEXT_REX_W1				= 1ULL << 13,
	PREFIX_CONTEXT_VEX					= 1ULL << 14,
	PREFIX_CONTEXT_VEX_W0				= 1ULL << 15,
	PREFIX_CONTEXT_VEX_W1				= 1ULL << 16,
	PREFIX_CONTEXT_VEX_IMPLIED_0F		= 1ULL << 17,
	PREFIX_CONTEXT_VEX_IMPLIED_0F38		= 1ULL << 18,
	PREFIX_CONTEXT_VEX_IMPLIED_0F3A		= 1ULL << 19,
	PREFIX_CONTEXT_VEX_128				= 1ULL << 20,
	PREFIX_CONTEXT_VEX_256				= 1ULL << 21,
	PREFIX_CONTEXT_EVEX					= 1ULL << 22,
	PREFIX_CONTEXT_EVEX_IMPLIED_0F		= 1ULL << 23,
	PREFIX_CONTEXT_EVEX_IMPLIED_0F38	= 1ULL << 24,
	PREFIX_CONTEXT_EVEX_IMPLIED_0F3A	= 1ULL << 25,
	PREFIX_CONTEXT_EVEX_W0				= 1ULL << 26,
	PREFIX_CONTEXT_EVEX_W1				= 1ULL << 27,
	PREFIX_CONTEXT_EVEX_128				= 1ULL << 28,
	PREFIX_CONTEXT_EVEX_256				= 1ULL << 29,
	PREFIX_CONTEXT_EVEX_512				= 1ULL << 30
};

#define PREFIX_CONTEXT_VEX_128_66_0F PREFIX_CONTEXT_VEX | PREFIX_CONTEXT_VEX_128 | PREFIX_CONTEXT_PREFIX_66 | PREFIX_CONTEXT_VEX_IMPLIED_0F

#define prefixContextHasFlag(context, flag) ((context & (flag)) == (flag))


struct REX {
	unsigned char W : 1;
	unsigned char R : 1;
	unsigned char X : 1;
	unsigned char B : 1;
};

struct VEX {
	unsigned char R : 1;
	unsigned char X : 1;
	unsigned char B : 1;
	unsigned char m_mmmm : 5;
	unsigned char W : 1;
	unsigned char vvvv : 4;
	unsigned char L : 1;
	unsigned char pp : 2;
};

struct EVEX {
	unsigned char mm : 2;
	unsigned char pp : 2;
	unsigned char R : 1;
	unsigned char X : 1;
	unsigned char B : 1;
	unsigned char R1 : 1;
	unsigned char vvvv : 4;
	unsigned char V1 : 1;
	unsigned char aaa : 3;
	unsigned char W : 1;
	unsigned char z : 1;
	unsigned char b : 1;
	unsigned char L : 1;
	unsigned char L1 : 1;
};

struct ExtendedPrefixData {
	enum {EXTENDED_PREFIX_INVALID = 0, EXTENDED_PREFIX_REX, EXTENDED_PREFIX_VEX, EXTENDED_PREFIX_EVEX} dataType;
	union {
		REX rex;
		VEX vex;
		EVEX evex;
	};
};
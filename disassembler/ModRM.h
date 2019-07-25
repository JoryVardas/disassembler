#pragma once

#include "Registers.h"

//indexed first by ModR/M.reg to get a group then by the register size.
extern register_t modrmRegisterGroups[32][8];
#define modrmRegisterGroups_R8 0
#define modrmRegisterGroups_R16 1
#define modrmRegisterGroups_R32 2
#define modrmRegisterGroups_R64 3
#define modrmRegisterGroups_MMX 4
#define modrmRegisterGroups_XMM 5
#define modrmRegisterGroups_YMM 6
#define modrmRegisterGroups_ZMM 7


extern register_t modrmMemoryGroups[16][2];
#define modrmMemoryGroups_R32 0
#define modrmMemoryGroups_R64 1
extern register_t modrmSibBaseGroups[16][2];
#define modrmSibBaseGroups_R32 0
#define modrmSibBaseGroups_R64 1
extern register_t modrmSibScaledGroups[16][2];
#define modrmSibScaledGroups_R32 0
#define modrmSibScaledGroups_R64 1


struct ModRM {
	uint8_t mod : 2;
	uint8_t reg : 3;
	uint8_t rm : 3;

	ModRM(byte);
};

struct SIB {
	uint8_t scale : 2;
	uint8_t index : 3;
	uint8_t base : 3;

	SIB(byte);
};
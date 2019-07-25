#pragma once

#include "Common.h"
#include "Prefixes.h"
#include "Registers.h"
#include "ModRM.h"
#include "Instructions.h"

class Decoder {
public:
	DecodedInstruction decodeNext(ByteStream& stream);

	std::string decodedInstructionToString(DecodedInstruction&);
};
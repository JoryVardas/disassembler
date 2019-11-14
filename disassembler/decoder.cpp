#include "decoder.h"
#include "ModRM.h"
#include <sstream>

uint8_t decodeBasePrefix(byte b) {
	switch (b) {
	case 0xF0:
		return PREFIX_F0;
	case 0xF2:
		return PREFIX_F2;
	case 0xF3:
		return PREFIX_F3;
	case 0x2E:
		return PREFIX_2E;
	case 0x36:
		return PREFIX_36;
	case 0x3E:
		return PREFIX_3E;
	case 0x26:
		return PREFIX_26;
	case 0x64:
		return PREFIX_64;
	case 0x65:
		return PREFIX_65;
	case 0x66:
		return PREFIX_66;
	case 0x67:
		return PREFIX_67;
	default:
		return PREFIX_NO_PREFIX;
	};

	return PREFIX_NO_PREFIX;
};

bool isRexPrefix(byte b) {
	return (b & 0xF0) == 0x40;
};
bool isVex2Prefix(byte b) {
	return b == 0xC5;
};
bool isVex3Prefix(byte b) {
	return b == 0xC4;
};
bool isEvexPrefix(byte b) {
	return b == 0x62;
};

std::pair<uint64_t, ExtendedPrefixData> decodePrefixContext(ByteStream& stream) {
	uint64_t context = 0;
	ExtendedPrefixData extendedPrefixData;
	zeromem(&extendedPrefixData, sizeof(ExtendedPrefixData));

	//first we decode any base prefixs that may exist, and add them to the context
	uint8_t decodedBasePrefix = 0;
	do {
		decodedBasePrefix = decodeBasePrefix(stream.peekByte());

		switch (decodedBasePrefix) {
		case PREFIX_F0:
			context |= PREFIX_CONTEXT_PREFIX_F0;
			stream.consumeByte();
			break;
		case PREFIX_F2:
			context |= PREFIX_CONTEXT_PREFIX_F2;
			stream.consumeByte();
			break;
		case PREFIX_F3:
			context |= PREFIX_CONTEXT_PREFIX_F3;
			stream.consumeByte();
			break;
		case PREFIX_2E:
			context |= PREFIX_CONTEXT_PREFIX_2E;
			stream.consumeByte();
			break;
		case PREFIX_36:
			context |= PREFIX_CONTEXT_PREFIX_36;
			stream.consumeByte();
			break;
		case PREFIX_3E:
			context |= PREFIX_CONTEXT_PREFIX_3E;
			stream.consumeByte();
			break;
		case PREFIX_26:
			context |= PREFIX_CONTEXT_PREFIX_26;
			stream.consumeByte();
			break;
		case PREFIX_64:
			context |= PREFIX_CONTEXT_PREFIX_64;
			stream.consumeByte();
			break;
		case PREFIX_65:
			context |= PREFIX_CONTEXT_PREFIX_65;
			stream.consumeByte();
			break;
		case PREFIX_66:
			context |= PREFIX_CONTEXT_PREFIX_66;
			stream.consumeByte();
			break;
		case PREFIX_67:
			context |= PREFIX_CONTEXT_PREFIX_67;
			stream.consumeByte();
			break;
		default:
			break;
		};
	} while (decodedBasePrefix != PREFIX_NO_PREFIX);

	//if we didn't have any prefixes, set the no prefix flag
	if ((context & (~(PREFIX_CONTEXT_PREFIX_66 | PREFIX_CONTEXT_PREFIX_67))) == 0) {
		context |= PREFIX_CONTEXT_NO_PREFIX;
	};

	//next we check if there is a REX prefix, and if so decode it and add it to the context.
	if (isRexPrefix(stream.peekByte())) {
		if (extendedPrefixData.dataType != ExtendedPrefixData::EXTENDED_PREFIX_INVALID) {
			std::cerr << "REX/VEX/EVEX already defined for current instruction, skipping duplicate REX prefix. Location: " << stream.currentLocation() << std::endl;

			//remove the REX byte.
			stream.consumeByte();
		}
		else {

			context |= PREFIX_CONTEXT_REX;
			extendedPrefixData.dataType = ExtendedPrefixData::EXTENDED_PREFIX_REX;

			byte rex = stream.consumeByte();
			extendedPrefixData.rex.W = ((rex & 0x08) >> 3);
			extendedPrefixData.rex.R = ((rex & 0x04) >> 2);
			extendedPrefixData.rex.X = ((rex & 0x02) >> 1);
			extendedPrefixData.rex.B = ((rex & 0x01) >> 0);

			if (extendedPrefixData.rex.W > 0) {
				context |= PREFIX_CONTEXT_REX_W1;
			}
			else {
				context |= PREFIX_CONTEXT_REX_W0;
			};
		};
	};

	//next we check if there is a VEX2 prefix
	if (isVex2Prefix(stream.peekByte())) {
		if (extendedPrefixData.dataType != ExtendedPrefixData::EXTENDED_PREFIX_INVALID) {
			std::cerr << "REX/VEX/EVEX already defined for current instruction, skipping duplicate VEX prefix. Location: " << stream.currentLocation() << std::endl;

			//remove the VEX bytes.
			stream.consumeByte();
			stream.consumeByte();
		}
		else {
			context |= PREFIX_CONTEXT_VEX;
			extendedPrefixData.dataType = ExtendedPrefixData::EXTENDED_PREFIX_VEX;

			//consume the indicator byte
			stream.consumeByte();
			//get the data.
			byte vex = stream.consumeByte();

			extendedPrefixData.vex.R = ((vex & 0x80) >> 7);
			extendedPrefixData.vex.vvvv = ((vex & 0x78) >> 3);
			extendedPrefixData.vex.L = ((vex & 0x04) >> 2);
			if (extendedPrefixData.vex.L == 1) {
				context |= PREFIX_CONTEXT_VEX_256;
			}
			else {
				context &= PREFIX_CONTEXT_VEX_128;
			};
			extendedPrefixData.vex.pp = (vex & 0x03);
			switch (extendedPrefixData.vex.pp) {
			case 0:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_NONE;
				break;
			case 1:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_66;
				break;
			case 2:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F3;
				break;
			case 3:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F2;
				break;
			};
		};
	};

	//next we check if there is a VEX3 prefix
	if (isVex2Prefix(stream.peekByte())) {
		if (extendedPrefixData.dataType != ExtendedPrefixData::EXTENDED_PREFIX_INVALID) {
			std::cerr << "REX/VEX/EVEX already defined for current instruction, skipping duplicate VEX prefix. Location: " << stream.currentLocation() << std::endl;

			//remove the VEX bytes.
			stream.consumeByte();
			stream.consumeByte();
			stream.consumeByte();
		}
		else {
			context |= PREFIX_CONTEXT_VEX;
			extendedPrefixData.dataType = ExtendedPrefixData::EXTENDED_PREFIX_VEX;

			//consume the indicator byte
			stream.consumeByte();
			//get the data.
			byte vex1 = stream.consumeByte();
			byte vex2 = stream.consumeByte();

			extendedPrefixData.vex.R = ((vex1 & 0x80) >> 7);
			extendedPrefixData.vex.X = ((vex1 & 0x40) >> 6);
			extendedPrefixData.vex.B = ((vex1 & 0x20) >> 5);
			extendedPrefixData.vex.m_mmmm = (vex1 & 0x1F);
			switch (extendedPrefixData.vex.m_mmmm) {
			case 1:
				context |= PREFIX_CONTEXT_VEX_IMPLIED_0F;
				break;
			case 2:
				context |= PREFIX_CONTEXT_VEX_IMPLIED_0F38;
				break;
			case 3:
				context |= PREFIX_CONTEXT_VEX_IMPLIED_0F3A;
				break;
			default:
				break;
			};
			extendedPrefixData.vex.W = ((vex2 & 0x80) >> 7);
			if (extendedPrefixData.vex.W == 1) {
				context |= PREFIX_CONTEXT_VEX_W1;
			}
			else {
				context |= PREFIX_CONTEXT_VEX_W0;
			};
			extendedPrefixData.vex.vvvv = ((vex2 & 0x78) >> 3);
			extendedPrefixData.vex.L = ((vex2 & 0x04) >> 2);
			if (extendedPrefixData.vex.L == 1) {
				context |= PREFIX_CONTEXT_VEX_256;
			}
			else {
				context |= PREFIX_CONTEXT_VEX_128;
			};
			extendedPrefixData.vex.pp = (vex2 & 0x03);
			switch (extendedPrefixData.vex.pp) {
			case 0:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_NONE;
				break;
			case 1:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_66;
				break;
			case 2:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F3;
				break;
			case 3:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F2;
				break;
			};
		};

	};

	//next we check if there is a EVEX prefix
	if (isEvexPrefix(stream.peekByte())) {
		if (extendedPrefixData.dataType != ExtendedPrefixData::EXTENDED_PREFIX_INVALID) {
			std::cerr << "REX/VEX/EVEX already defined for current instruction, skipping duplicate EVEX prefix. Location: " << stream.currentLocation() << std::endl;

			//remove the VEX bytes.
			stream.consumeByte();
			stream.consumeByte();
			stream.consumeByte();
			stream.consumeByte();
		}
		else {
			context |= PREFIX_CONTEXT_EVEX;
			extendedPrefixData.dataType = ExtendedPrefixData::EXTENDED_PREFIX_EVEX;

			//consume the indicator byte
			stream.consumeByte();
			//get the data.
			byte evex1 = stream.consumeByte();
			byte evex2 = stream.consumeByte();
			byte evex3 = stream.consumeByte();

			extendedPrefixData.evex.R = ((evex1 & 0x80) >> 7);
			extendedPrefixData.evex.X = ((evex1 & 0x40) >> 6);
			extendedPrefixData.evex.B = ((evex1 & 0x20) >> 5);
			extendedPrefixData.evex.R1 = ((evex1 & 0x10) >> 4);
			extendedPrefixData.evex.mm = (evex1 & 0x03);
			switch (extendedPrefixData.evex.mm) {
			case 1:
				context |= PREFIX_CONTEXT_EVEX_IMPLIED_0F;
				break;
			case 2:
				context |= PREFIX_CONTEXT_EVEX_IMPLIED_0F38;
				break;
			case 3:
				context |= PREFIX_CONTEXT_EVEX_IMPLIED_0F3A;
				break;
			default:
				break;
			};
			extendedPrefixData.evex.W = ((evex2 & 0x80) >> 7);
			if (extendedPrefixData.evex.W == 1) {
				context |= PREFIX_CONTEXT_EVEX_W1;
			}
			else {
				context |= PREFIX_CONTEXT_EVEX_W0;
			};
			extendedPrefixData.evex.vvvv = ((evex2 & 0x78) >> 3);
			extendedPrefixData.evex.pp = (evex2 & 0x03);
			switch (extendedPrefixData.evex.pp) {
			case 0:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_NONE;
				break;
			case 1:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_66;
				break;
			case 2:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F3;
				break;
			case 3:
				context |= PREFIX_CONTEXT_VEX_EVEX_PREFIX_F2;
				break;
			default:
				break;
			};
			extendedPrefixData.evex.z = ((evex3 & 0x80) >> 7);
			extendedPrefixData.evex.L1 = ((evex3 & 0x40) >> 6);
			extendedPrefixData.evex.L = ((evex3 & 0x20) >> 5);
			switch (((extendedPrefixData.evex.L1) << 1) + extendedPrefixData.evex.L) {
			case 0:
				context |= PREFIX_CONTEXT_EVEX_128;
				break;
			case 1:
				context |= PREFIX_CONTEXT_EVEX_256;
				break;
			case 2:
				context |= PREFIX_CONTEXT_EVEX_512;
				break;
			default:
				break;
			};
			extendedPrefixData.evex.b = ((evex3 & 0x10) >> 4);
			extendedPrefixData.evex.V1 = ((evex3 & 0x08) >> 3);
			extendedPrefixData.evex.aaa = (evex3 & 0x07);
		};

	};

	//we have now retrieved the prefix context for the instruction.
	return { context, extendedPrefixData };
};


//modrm may not actually have any useful infomation
instructionId_t findInstruction(opcode_t opcode, prefixContext_t prefixContex, ModRM potentialModrm, ByteStream& stream) {
	std::vector<instructionId_t> matches;

	//we go through instruction by instruction, though it might be possible to sort the instruciton list and do a binary search pattern.
	//we start at index 1, since the first instruction in the list is the UNKNOWN instruction, which isn't something that we want to search against.
	for (uint64_t i = 1; i < instructionListLength; ++i) {
		//we use this to check for instructions which use the last three bits of the opcode as a register field.
		opcode_t partialOpcode = opcode & 0xFFFFFFF8;

		InstructionInfo& cur = instructionList[i];

		if (cur.opcode == opcode) {
			//we have a match on the opcode, what about the prefix context?
			if ((prefixContex & cur.prefixContext) == cur.prefixContext) {
				//the prefix context matches, what about the instruction context?
				if ((cur.instructionEnvironment & INSTRUCTION_ENVIRONMENT_MODRM_REG) > 0) {
					if ((cur.instructionEnvironment & INSTRUCTION_ENVIRONMENT_MODRM_REG) - 1 == potentialModrm.reg) {
						//the instruction matches
						matches.push_back(i);
					}
				}
				else {
					//the instruction doesn't need the modrm.reg field as part of the opcode, so we have found the instruction
					matches.push_back(i);
				};
			};
		}
		else if (cur.opcode == partialOpcode) {
			//we have a match with the partial opcode, but does the instruction actually use a partial opcode.
			if ((cur.instructionEnvironment & INSTRUCTION_ENVIRONMENT_OPCODE_HAS_REG) == INSTRUCTION_ENVIRONMENT_OPCODE_HAS_REG) {
				//we have a match on the opcode, what about the prefix context?
				if ((prefixContex & cur.prefixContext) == cur.prefixContext) {
					//the prefix context matches, so add this value to our list of matches.
					matches.push_back(i);
				};
			};
		}
	};

	//if we didn't find any mathces, then return an empty instruction.
	if (matches.size() <= 0) {
		std::cerr << "Could not find any matching instruction. Location: " << stream.currentLocation() << std::endl;
		return 0;
	};

	//if we found multiple matches, then return an empty instruction.
	if (matches.size() > 1) {
		std::cerr << "Multiple matching instructions found. Location: " << stream.currentLocation() << std::endl;
		return 0;
	};

	//otherwise return the found instruciton.
	return matches[0];
};

addressSize_t getActualAddressSize(addressSize_t defaultAddressSize, prefixContext_t prefixContext) {
	switch (defaultAddressSize) {
	case ADDRESS_SIZE_32:
	    if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_PREFIX_67)) {
			return ADDRESS_SIZE_64;
		}
		else {
			return ADDRESS_SIZE_32;
		};
		break;
	case ADDRESS_SIZE_64:
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_PREFIX_67)) {
			return ADDRESS_SIZE_32;
		}
		else {
			return ADDRESS_SIZE_64;
		};
		break;
	default:
		return defaultAddressSize;
	};
	return defaultAddressSize;
};

operandSize_t getActualOperandSize(operandSize_t defaultOperandSize, prefixContext_t prefixContext) {
	switch (defaultOperandSize) {
	case OPERAND_SIZE_16:
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_REX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_W1)) {
			return OPERAND_SIZE_64;
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_PREFIX_66)) {
			return OPERAND_SIZE_32;
		}
		else {
			return OPERAND_SIZE_16;
		};
		break;
	case OPERAND_SIZE_32:
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_REX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_W1)) {
			return OPERAND_SIZE_64;
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_PREFIX_66)) {
			return OPERAND_SIZE_16;
		}
		else {
			return OPERAND_SIZE_32;
			return OPERAND_SIZE_32;
		};
		break;
	case OPERAND_SIZE_64:
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_REX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_W1) | prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_W1)) {
			return OPERAND_SIZE_64;
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_PREFIX_66)) {
			return OPERAND_SIZE_32;
		}
		else {
			return OPERAND_SIZE_64;
		};
		break;
	default:
		return defaultOperandSize;
	};
	return defaultOperandSize;
};


struct InstructionRawOperandData {
	std::optional<ModRM> modrm;
	std::optional<SIB> sib;
	std::optional<uint64_t> displacement;
};

void getRawModRMData(InstructionRawOperandData& rawOperandData, ByteStream& stream) {
	//we need to get the modrm byte.
	rawOperandData.modrm = ModRM(stream.consumeByte());


	//IMPRTANT! For now I am only considering 64bit machine code (which uses the 32bit addressing mode ModRM table)

	//get the SIB byte if we need one
	if (rawOperandData.modrm->mod != 3 && rawOperandData.modrm->rm == 4) {
		//we have a SIB byte
		rawOperandData.sib = SIB(stream.consumeByte());

		//do we need a displacement?
		if (rawOperandData.sib->base == 5 && rawOperandData.modrm->mod == 0) {
			rawOperandData.displacement = (uint64_t)stream.consumeDWord();
		};
	};


	//get any displacement (if we need one that wasn't required by the SIB)
	if (rawOperandData.modrm->mod == 0 && rawOperandData.modrm->rm == 5) {
		rawOperandData.displacement = (uint64_t)stream.consumeDWord();
	}
	else if (rawOperandData.modrm->mod == 1) {
		rawOperandData.displacement = (uint64_t)stream.consumeByte();
	}
	else if (rawOperandData.modrm->mod == 2) {
		rawOperandData.displacement = (uint64_t)stream.consumeDWord();
	};

	//we now have the ModRM, SIM, and displacement bytes.
};

InstructionRawOperandData getRawOperandData(instructionId_t instruction, addressSize_t addressSize, ByteStream& stream) {
	InstructionRawOperandData rawOperandData;

	//firstly do we need ModRM data?
	switch (instructionOperandEncoding[instruction]) {
	case INSTRUCTION_OPERAND_ENCODING_R_RM:
	case INSTRUCTION_OPERAND_ENCODING_RM_R:
	case INSTRUCTION_OPERAND_ENCODING_RM_IMM:
	case INSTRUCTION_OPERAND_ENCODING_R_VEC_RM:
	case INSTRUCTION_OPERAND_ENCODING_R_RM_IMM:
	case INSTRUCTION_OPERAND_ENCODING_R_RM_VEC:
	case INSTRUCTION_OPERAND_ENCODING_R_RM_IMPLIED_XMM0:
		getRawModRMData(rawOperandData, stream);
	};

	//We can't get the immediate data yet, since the size of the immediate data changes per instruction.

	return rawOperandData;
};

operandType_t getClosestImplicitOperandType(operandType_t operandType, prefixContext_t prefixContext, operandSize_t operandSize) {
	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_IMPLICIT_AX_EAX_RAX)) {
		switch (operandSize) {
		case OPERAND_SIZE_64:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_RAX)) {
				return OPERAND_TYPE_IMPLICIT_RAX;
			};
		case OPERAND_SIZE_32:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_EAX)) {
				return OPERAND_TYPE_IMPLICIT_EAX;
			};
		case OPERAND_SIZE_16:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_AX)) {
				return OPERAND_TYPE_IMPLICIT_AX;
			}
		default:
			std::cerr << "getClosestImplicitOperandType passed unknown operand size." << std::endl;
			return OPERAND_TYPE_NO_OPERANDS;
		};
	}
	else if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_AL)) {
		return OPERAND_TYPE_IMPLICIT_AL;
	}
	else if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_IMPLICIT_XMM0_YMM0_ZMM0)) {
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_128) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_128)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_XMM0)) {
				return OPERAND_TYPE_IMPLICIT_XMM0;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_256) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_256)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_YMM0)) {
				return OPERAND_TYPE_IMPLICIT_YMM0;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_512)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMPLICIT_ZMM0)) {
				return OPERAND_TYPE_IMPLICIT_ZMM0;
			}
		};
	};

	//if we get here we couldn't determine the actual type.
	std::cerr << "getClosestImplicitOperandType could not determine operand type." << std::endl;
	return OPERAND_TYPE_NO_OPERANDS;
};
register_t getImplicitRegisterFromOperandType(operandType_t operandType) {
	switch (operandType) {
	case OPERAND_TYPE_IMPLICIT_AL:
		return REGISTER_AL;
	case OPERAND_TYPE_IMPLICIT_AX:
		return REGISTER_AX;
	case OPERAND_TYPE_IMPLICIT_EAX:
		return REGISTER_EAX;
	case OPERAND_TYPE_IMPLICIT_RAX:
		return REGISTER_RAX;
	case OPERAND_TYPE_IMPLICIT_XMM0:
		return REGISTER_XMM0;
	case OPERAND_TYPE_IMPLICIT_YMM0:
		return REGISTER_YMM0;
	case OPERAND_TYPE_IMPLICIT_ZMM0:
		return REGISTER_ZMM0;
	default:
		std::cerr << "Could not determine the implicit register." << std::endl;
		return REGISTER_INVALID_REGISTER;
	};
	return REGISTER_INVALID_REGISTER;
};
void decodeImmpliedRegisterOperand(DecodedInstruction::DecodedOperand& decodedOperand, operandType_t operandType, prefixContext_t prefixContext, operandSize_t operandSize) {
	decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_REGISTER;
	//decodedOperand.operandData.reg.format = decodedOperand.operandData.reg.DECODED_OPERAND_REG_FORMAT_REG;
	decodedOperand.operandData.reg.reg = getImplicitRegisterFromOperandType(getClosestImplicitOperandType(operandType, prefixContext, operandSize));
};

operandType_t getClosestImmediateOperandType(operandType_t operandType, operandSize_t operandSize) {
	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_IMM16_32 | OPERAND_TYPE_IMM64)) {
		switch (operandSize) {
		case OPERAND_SIZE_64:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMM64)) {
				return OPERAND_TYPE_IMM64;
			};
		case OPERAND_SIZE_32:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMM32)) {
				return OPERAND_TYPE_IMM32;
			};
		case OPERAND_SIZE_16:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMM16)) {
				return OPERAND_TYPE_IMM16;
			};
		default:
			std::cerr << "getClosestImplicitOperandType passed unknown operand size." << std::endl;
			return OPERAND_TYPE_NO_OPERANDS;
		};
	}
	else if (operandTypeHasFlags(operandType, OPERAND_TYPE_IMM8)) {
		return OPERAND_TYPE_IMM8;
	}
	else {
		std::cerr << "getClosestImmediateOperandType could not determine operand type." << std::endl;
		return OPERAND_TYPE_NO_OPERANDS;
	};
	return OPERAND_TYPE_NO_OPERANDS;
};
uint64_t getImmediateOperandFromOpeandType(operandType_t operandType, ByteStream& stream) {
	switch (operandType) {
	case OPERAND_TYPE_IMM8:
		return (uint64_t)stream.consumeByte();
	case OPERAND_TYPE_IMM16:
		return (uint64_t)stream.consumeWord();
	case OPERAND_TYPE_IMM32:
		return (uint64_t)stream.consumeDWord();
	case OPERAND_TYPE_IMM64:
		return (uint64_t)stream.consumeQWord();
	default:
		std::cerr << "Could not determine the immediate value." << std::endl;
		return 0;
	};
	return 0;
};
void decodeImmediateOperand(DecodedInstruction::DecodedOperand& decodedOperand, operandType_t operandType, operandSize_t operandSize, ByteStream& stream) {
	decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_IMMEDIATE;
	decodedOperand.operandData.immediate = getImmediateOperandFromOpeandType(getClosestImmediateOperandType(operandType, operandSize), stream);
};

operandType_t getClosestRegisterOperandType(operandType_t operandType, prefixContext_t prefixContext, operandSize_t operandSize) {
	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_R16_32_64)) {
		switch (operandSize) {
		case OPERAND_SIZE_64:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_R64)) {
				return OPERAND_TYPE_R64;
			};
		case OPERAND_SIZE_32:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_R32)) {
				return OPERAND_TYPE_R32;
			};
		case OPERAND_SIZE_16:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_R16)) {
				return OPERAND_TYPE_R16;
			};
		default:
			std::cerr << "getClosestRegisterOperandType passed unknown operand size." << std::endl;
			return OPERAND_TYPE_NO_OPERANDS;
		};
	}
	else if (operandTypeHasFlags(operandType, OPERAND_TYPE_R8)) {
		return OPERAND_TYPE_R8;
	}
	else if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_XMM_YMM_ZMM)) {
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_128) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_128)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_XMM)) {
				return OPERAND_TYPE_XMM;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_256) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_256)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_YMM)) {
				return OPERAND_TYPE_YMM;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_512)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_ZMM)) {
				return OPERAND_TYPE_ZMM;
			}
		}
		else {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_ZMM)) {
				return OPERAND_TYPE_ZMM;
			}
			else if (operandTypeHasFlags(operandType, OPERAND_TYPE_YMM)) {
				return OPERAND_TYPE_YMM;
			}
			else if (operandTypeHasFlags(operandType, OPERAND_TYPE_XMM)) {
				return OPERAND_TYPE_XMM;
			}
		};
	};

	//if we get here we couldn't figure out the type
	std::cerr << "getClosestRegisterOperandType could not determine operand type." << std::endl;
	return OPERAND_TYPE_NO_OPERANDS;
};
register_t getRegisterFromOperandType(operandType_t operandType, ExtendedPrefixData& prefixData, InstructionRawOperandData& operandData) {
	uint8_t reg = operandData.modrm->reg;

	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_R16_32_64 | OPERAND_TYPE_R8)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
			if (prefixData.rex.R == 1) {
				reg |= 0x08;
			};
		};

		switch (operandType) {
		case OPERAND_TYPE_R8:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R8];
		case OPERAND_TYPE_R16:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R16];
		case OPERAND_TYPE_R32:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R32];
		case OPERAND_TYPE_R64:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R64];
		};
	}
	else if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_XMM_YMM_ZMM)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
			//we have a rex prefix which may contain register extension bits.
			if (prefixData.rex.R == 1) {
				reg |= 0x08;
			};
		}
		else if (prefixData.dataType == prefixData.EXTENDED_PREFIX_VEX) {
			//we have a vex prefix which may contain register extension bits.
			if (prefixData.vex.R == 0) {
				reg |= 0x08;
			};
		}
		else if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//we have a evex prefix which may contain register extension bits.
			if (prefixData.evex.R == 0) {
				reg |= 0x08;
			};
			if (prefixData.evex.R1 == 0) {
				reg |= 0x10;
			};
		};

		//now that we have the extended register we can simply retrieve it from the table.
		switch (operandType) {
		case OPERAND_TYPE_XMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_XMM];
		case OPERAND_TYPE_YMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_YMM];
		case OPERAND_TYPE_ZMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_ZMM];
		};
	};

	//if we end up here we couldn't determine the register
	std::cerr << "Could not determine the register value." << std::endl;
	return REGISTER_INVALID_REGISTER;
};
void decodeRegisterOperand(DecodedInstruction::DecodedOperand& decodedOperand, operandType_t operandType, prefixContext_t prefixContext, ExtendedPrefixData& prefixData, InstructionRawOperandData& rawOperandData, operandSize_t  operandSize) {
	decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_REGISTER;
	//decodedOperand.operandData.reg.k_register = 0;
	//decodedOperand.operandData.reg.z_mask_used = 0;
	operandType_t determinedOperandType = getClosestRegisterOperandType(operandType, prefixContext, operandSize);
	decodedOperand.operandData.reg.reg = getRegisterFromOperandType(determinedOperandType, prefixData, rawOperandData);
	
	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE__K_ | OPERAND_TYPE__K_Z_)) {
		//if we don't have an evex prefix then we don't have a writemask
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//decodedOperand.operandData.reg.kzFieldsUsed = true;
			decodedOperand.operandData.reg.k_register = prefixData.evex.aaa;
		};
	};
	if (operandTypeHasFlags(operandType, OPERAND_TYPE__K_Z_)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//decodedOperand.operandData.reg.kzFieldsUsed = true;
			decodedOperand.operandData.reg.z_mask_used = prefixData.evex.z;
		};
	};
};


register_t getMemoryRegisterFromOperandType(operandType_t operandType, ExtendedPrefixData& prefixData, InstructionRawOperandData& operandData) {
	uint8_t reg = operandData.modrm->rm;

	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_R16_32_64 | OPERAND_TYPE_R8)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
			//we are garanteed to not have a SIB byte if we are decodeing the rm field as a register.
			if (prefixData.rex.B == 1) {
				reg |= 0x08;
			};
		};

		switch (operandType) {
		case OPERAND_TYPE_R8:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R8];
		case OPERAND_TYPE_R16:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R16];
		case OPERAND_TYPE_R32:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R32];
		case OPERAND_TYPE_R64:
			return modrmRegisterGroups[reg][modrmRegisterGroups_R64];
		};
	}
	else if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_XMM_YMM_ZMM)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
			//we have a rex prefix which may contain register extension bits.
			if (prefixData.rex.B == 1) {
				reg |= 0x08;
			};
		}
		else if (prefixData.dataType == prefixData.EXTENDED_PREFIX_VEX) {
			//we have a vex prefix which may contain register extension bits.
			if (prefixData.vex.B == 0) {
				reg |= 0x08;
			};
		}
		else if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//we have a evex prefix which may contain register extension bits.
			if (prefixData.evex.B == 0) {
				reg |= 0x08;
			};
			if (prefixData.evex.X == 0) {
				reg |= 0x10;
			};
		};

		//now that we have the extended register we can simply retrieve it from the table.
		switch (operandType) {
		case OPERAND_TYPE_XMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_XMM];
		case OPERAND_TYPE_YMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_YMM];
		case OPERAND_TYPE_ZMM:
			return modrmRegisterGroups[reg][modrmRegisterGroups_ZMM];
		};
	};

	//if we end up here we couldn't determine the register
	std::cerr << "Could not determine the register value." << std::endl;
	return REGISTER_INVALID_REGISTER;
};
operandType_t getClosestMemoryOperandType(operandType_t operandType, prefixContext_t prefixContext, operandSize_t operandSize) {
	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_M16_32_64)) {
		switch (operandSize) {
		case OPERAND_SIZE_64:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M64)) {
				return OPERAND_TYPE_M64;
			};
		case OPERAND_SIZE_32:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M32)) {
				return OPERAND_TYPE_M32;
			};
		case OPERAND_SIZE_16:
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M16)) {
				return OPERAND_TYPE_M16;
			};
		default:
			//std::cerr << "getClosestMemoryOperandType passed unknown operand size." << std::endl;
			//return OPERAND_TYPE_NO_OPERANDS;
			
			//while this would normally be an error, there are cases such as ADDSD in which the operandSize != 64 but the memory size does.
			//so to handle such cases, just forward the memory.
			return operandType & (OPERAND_TYPE_M16_32_64 | OPERAND_TYPE_M128_256_512);
		};
	}
	else if (operandTypeHasFlags(operandType, OPERAND_TYPE_M8)) {
		return OPERAND_TYPE_M8;
	}
	else if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE_M128_256_512)) {
		if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_128) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_128)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M128)) {
				return OPERAND_TYPE_M128;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_VEX_256) || prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_256)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M256)) {
				return OPERAND_TYPE_M256;
			}
		}
		else if (prefixContextHasFlag(prefixContext, PREFIX_CONTEXT_EVEX_512)) {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M512)) {
				return OPERAND_TYPE_M512;
			}
		}
		else {
			if (operandTypeHasFlags(operandType, OPERAND_TYPE_M512)) {
				return OPERAND_TYPE_M512;
			}
			else if (operandTypeHasFlags(operandType, OPERAND_TYPE_M256)) {
				return OPERAND_TYPE_M256;
			}
			else if (operandTypeHasFlags(operandType, OPERAND_TYPE_M128)) {
				return OPERAND_TYPE_M128;
			}
		};
	};

	return OPERAND_TYPE_NO_OPERANDS;
};
void decodeRegisterMemoryOperand(DecodedInstruction::DecodedOperand& decodedOperand, operandType_t operandType, prefixContext_t prefixContext, ExtendedPrefixData& prefixData, InstructionRawOperandData& rawOperandData, operandSize_t operandSize, addressSize_t addressSize) {
	//first we need to decide if we are decoding a register or a memory address
	//  we can do this by checking the modrm.mod field.
	if (rawOperandData.modrm->mod == 3) {
		//we are decoding a register, so just decode it like normal.
		// I would like to be able to just call the existing function for this, but the register extension bits are in different spots so I have to rewrite it.

		decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_REGISTER;
		decodedOperand.operandData.reg.reg = getMemoryRegisterFromOperandType(getClosestRegisterOperandType(operandType, prefixContext, operandSize), prefixData, rawOperandData);

		if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE__K_ | OPERAND_TYPE__K_Z_)) {
			//if we don't have an evex prefix then we don't have a writemask
			if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
				//decodedOperand.operandData.reg.kzFieldsUsed = true;
				decodedOperand.operandData.reg.k_register = prefixData.evex.aaa;
			};
		};
		if (operandTypeHasFlags(operandType, OPERAND_TYPE__K_Z_)) {
			if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
				//decodedOperand.operandData.reg.kzFieldsUsed = true;
				decodedOperand.operandData.reg.z_mask_used = prefixData.evex.z;
			};
		};
	}
	else {
		//We are decoding a memory address
		decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_MEM;

		//lets first check if the rm feild only specifies a displacement
		// this might be wrong because it ignores any prefixs, but if it is it will come up in testing.
		if (rawOperandData.modrm->mod == 0 && rawOperandData.modrm->rm == 5) {
			//decodedOperand.operandData.memory.format = decodedOperand.operandData.memory.DECODED_OPERAND_MEMORY_FORMAT_DISP;
			decodedOperand.operandData.memory.disp = rawOperandData.displacement.value();
		}
		else {
			//we are dealing with register memory address
			switch (rawOperandData.modrm->mod) {
			case 0:
				if (rawOperandData.modrm->rm == 4) {
					//we have an SIB byte.

					uint8_t baseReg = rawOperandData.sib->base;
					uint8_t scaledReg = rawOperandData.sib->index;

					if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
						if (prefixData.rex.B == 1) baseReg |= 0x08;
						if (prefixData.rex.X == 1) scaledReg |= 0x08;
					}
					//IMPORTANT as far as I know the xmm, ymm, and zmm registers cant be used as a memory address.

					//get the base register
					if (baseReg == 5) {
						//the base reg is actually a disp32
						decodedOperand.operandData.memory.disp = rawOperandData.displacement.value();
					}
					else {
						if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.baseReg = modrmSibBaseGroups[baseReg][modrmSibBaseGroups_R32];
						else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.baseReg = modrmSibBaseGroups[baseReg][modrmSibBaseGroups_R64];
					};


					//get the scaled register
					if (scaledReg != 4) {
						if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.scaledReg = modrmSibScaledGroups[scaledReg][modrmSibScaledGroups_R32];
						else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.scaledReg = modrmSibScaledGroups[scaledReg][modrmSibScaledGroups_R64];
					};

					switch (rawOperandData.sib->scale) {
					case 0:
						decodedOperand.operandData.memory.scalar = 1;
						break;
					case 1:
						decodedOperand.operandData.memory.scalar = 2;
						break;
					case 2:
						decodedOperand.operandData.memory.scalar = 4;
						break;
					case 3:
						decodedOperand.operandData.memory.scalar = 8;
						break;
					};
				}
				else {
					//we don't have a sib byte.
					uint8_t baseReg = rawOperandData.modrm->rm;
					if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
						if (prefixData.rex.B) baseReg |= 0x08;
					};

					if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.baseReg = modrmMemoryGroups[baseReg][modrmMemoryGroups_R32];
					else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.baseReg = modrmMemoryGroups[baseReg][modrmMemoryGroups_R64];
				};
				break;
			case 1:
			case 2:
				if (rawOperandData.modrm->rm == 4) {
					//we have an SIB byte.

					uint8_t baseReg = rawOperandData.sib->base;
					uint8_t scaledReg = rawOperandData.sib->index;

					if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
						if (prefixData.rex.B == 1) baseReg |= 0x08;
						if (prefixData.rex.X == 1) scaledReg |= 0x08;
					}
					//IMPORTANT as far as I know the xmm, ymm, and zmm registers cant be used as a memory address.

					//get the base register
					if (baseReg == 5) {
						//the base reg is EBP
						if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.baseReg = REGISTER_EBP;
						else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.baseReg = REGISTER_RBP;
					}
					else {
						if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.baseReg = modrmSibBaseGroups[baseReg][modrmSibBaseGroups_R32];
						else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.baseReg = modrmSibBaseGroups[baseReg][modrmSibBaseGroups_R64];
					};


					//get the scaled register
					if (scaledReg != 4) {
						if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.scaledReg = modrmSibScaledGroups[scaledReg][modrmSibScaledGroups_R32];
						else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.scaledReg = modrmSibScaledGroups[scaledReg][modrmSibScaledGroups_R64];
					};

					switch (rawOperandData.sib->scale) {
					case 0:
						decodedOperand.operandData.memory.scalar = 1;
						break;
					case 1:
						decodedOperand.operandData.memory.scalar = 2;
						break;
					case 2:
						decodedOperand.operandData.memory.scalar = 4;
						break;
					case 3:
						decodedOperand.operandData.memory.scalar = 8;
						break;
					};
				}
				else {
					//we don't have a sib byte.
					uint8_t baseReg = rawOperandData.modrm->rm;
					if (prefixData.dataType == prefixData.EXTENDED_PREFIX_REX) {
						if (prefixData.rex.B) baseReg |= 0x08;
					};

					if (addressSize == ADDRESS_SIZE_32) decodedOperand.operandData.memory.baseReg = modrmMemoryGroups[baseReg][modrmMemoryGroups_R32];
					else if (addressSize == ADDRESS_SIZE_64) decodedOperand.operandData.memory.baseReg = modrmMemoryGroups[baseReg][modrmMemoryGroups_R64];
				};

				decodedOperand.operandData.memory.disp = rawOperandData.displacement.value();
				break;
			};
		};


		//now we have to get the memory size
		switch (getClosestMemoryOperandType(operandType, prefixContext, operandSize)) {
		case OPERAND_TYPE_M8:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_BYTE;
			break;
		case OPERAND_TYPE_M16:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_WORD;
			break;
		case OPERAND_TYPE_M32:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_DWORD;
			break;
		case OPERAND_TYPE_M64:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_QWORD;
			break;
		case OPERAND_TYPE_M128:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_XMMWORD;
			break;
		case OPERAND_TYPE_M256:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_YMMWORD;
			break;
		case OPERAND_TYPE_M512:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_ZMMWORD;
			break;
		default:
			decodedOperand.operandData.memory.size = MEMORY_OPERAND_SIZE_UNKNOWN;
			break;
		}
	};
};


void decodeVectorOperand(DecodedInstruction::DecodedOperand& decodedOperand, operandType_t operandType, prefixContext_t prefixContext, ExtendedPrefixData& prefixData) {
	decodedOperand.decodedOperandType = DECODED_OPERAND_TYPE_REGISTER;

	//the operandSize is not actually used for this.
	operandType_t decidedType = getClosestRegisterOperandType(operandType, prefixContext, OPERAND_SIZE_64);

	uint8_t reg = 0;
	if (prefixData.dataType == prefixData.EXTENDED_PREFIX_VEX) {
		reg = (~prefixData.vex.vvvv) & 0x0F;
	}
	else if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
		reg = (~prefixData.evex.vvvv) & 0x0F;
		if (prefixData.evex.V1 == 0) {
			reg |= 0x10;
		};
	};

	if (operandTypeHasFlags(decidedType, OPERAND_TYPE_XMM)) {
		decodedOperand.operandData.reg.reg = modrmRegisterGroups[reg][modrmRegisterGroups_XMM];
	}
	else if (operandTypeHasFlags(decidedType, OPERAND_TYPE_YMM)) {
		decodedOperand.operandData.reg.reg = modrmRegisterGroups[reg][modrmRegisterGroups_YMM];
	}
	else if (operandTypeHasFlags(decidedType, OPERAND_TYPE_ZMM)) {
		decodedOperand.operandData.reg.reg = modrmRegisterGroups[reg][modrmRegisterGroups_ZMM];
	};

	if (operandTypeHasSomeFlags(operandType, OPERAND_TYPE__K_ | OPERAND_TYPE__K_Z_)) {
		//if we don't have an evex prefix then we don't have a writemask
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//decodedOperand.operandData.reg.kzFieldsUsed = true;
			decodedOperand.operandData.reg.k_register = prefixData.evex.aaa;
		};
	};
	if (operandTypeHasFlags(operandType, OPERAND_TYPE__K_Z_)) {
		if (prefixData.dataType == prefixData.EXTENDED_PREFIX_EVEX) {
			//decodedOperand.operandData.reg.kzFieldsUsed = true;
			decodedOperand.operandData.reg.z_mask_used = prefixData.evex.z;
		};
	};
};


void decodeInstructionOperands(DecodedInstruction& decodedInstruction, instructionOperandEncoding_t encoding, InstructionOperand operands, prefixContext_t prefixContext, ExtendedPrefixData& prefixData, InstructionRawOperandData& rawOperandData, addressSize_t addressSize, operandSize_t operandSize, ByteStream& stream) {
	switch (encoding) {
	case INSTRUCTION_OPERAND_ENCODING_NA:
		decodedInstruction.operand1.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand2.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_IMPLIED_AX_IMM:
		decodeImmpliedRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, operandSize);
		decodeImmediateOperand(decodedInstruction.operand2, operands.operand2, operandSize, stream);
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_R_RM:
		decodeRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize);
		decodeRegisterMemoryOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_RM_R:
		decodeRegisterMemoryOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodeRegisterOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData, rawOperandData, operandSize);
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_RM_IMM:
		decodeRegisterMemoryOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodeImmediateOperand(decodedInstruction.operand2, operands.operand2, operandSize, stream);
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_R_VEC_RM:
		decodeRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize);
		decodeVectorOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData);
		decodeRegisterMemoryOperand(decodedInstruction.operand3, operands.operand3, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_R_RM_IMM:
		decodeRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize);
		decodeRegisterMemoryOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodeImmediateOperand(decodedInstruction.operand3, operands.operand3, operandSize, stream);
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_R_RM_VEC:
		decodeRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize);
		decodeRegisterMemoryOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodeVectorOperand(decodedInstruction.operand3, operands.operand3, prefixContext, prefixData);
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	case INSTRUCTION_OPERAND_ENCODING_R_RM_IMPLIED_XMM0:
		decodeRegisterOperand(decodedInstruction.operand1, operands.operand1, prefixContext, prefixData, rawOperandData, operandSize);
		decodeRegisterMemoryOperand(decodedInstruction.operand2, operands.operand2, prefixContext, prefixData, rawOperandData, operandSize, addressSize);
		decodeImmpliedRegisterOperand(decodedInstruction.operand3, operands.operand3, prefixContext, operandSize);
		break;
	case INSTRUCTION_OPERAND_ENCODING_IMM:
		decodeImmediateOperand(decodedInstruction.operand1, operands.operand1, operandSize, stream);
		//decodedInstruction.operand1.decodedOperandType = DECODED_OPERAND_TYPE_IMMEDIATE;
		//decodedInstruction.operand1.operandData.immediate = (uint64_t)stream.consumeByte();

		decodedInstruction.operand2.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand3.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		decodedInstruction.operand4.decodedOperandType = DECODED_OPERAND_TYPE_NO_OPERAND;
		break;
	default:
		std::cerr << "An unknown operand encoding was encountered. Location: " << stream.currentLocation() << std::endl;
		break;
	};
};


void decodeInstruction(DecodedInstruction& decodedInstruction, instructionId_t instruction, addressSize_t defaultAddressSize, operandSize_t defaultOperandSize, prefixContext_t prefixContext, ExtendedPrefixData& extendedPrefixData, ByteStream& stream) {
	//set the instruction
	decodedInstruction.instruction = instruction;

	//before we can start to decode the instruction we need to know the actual address and operand sizes used in the instruciton.
	addressSize_t addressSize = getActualAddressSize(defaultAddressSize, prefixContext);
	operandSize_t operandSize = getActualOperandSize(defaultOperandSize, prefixContext);

	//next we have to go through and get the modrm/sib/displacement bytes (if any are needed).
	InstructionRawOperandData rawOperandData = getRawOperandData(instruction, addressSize, stream);

	//now we can go through and decode the operands (after getting the actual operand type)
	decodeInstructionOperands(decodedInstruction, instructionOperandEncoding[instruction], instructionOperands[instruction], prefixContext, extendedPrefixData, rawOperandData, addressSize, operandSize, stream);
	
};

DecodedInstruction Decoder::decodeNext(ByteStream& stream) {
	//a couple constants which might be moved to parameters later.
	const addressSize_t defaultAddressSize = ADDRESS_SIZE_64;
	const operandSize_t defaultOperandSize = OPERAND_SIZE_32;


	DecodedInstruction decodedInstruction;
	zeromem(&decodedInstruction, sizeof(DecodedInstruction));

	//set the startPosition for the decoded instruction.
	decodedInstruction.startPosition = stream.currentLocation();

	//first get the prefix context
	std::pair<prefixContext_t, ExtendedPrefixData> prefixContextPair = decodePrefixContext(stream);
	prefixContext_t prefixContext = prefixContextPair.first;
	ExtendedPrefixData extendedPrefixData = prefixContextPair.second;



	//next we have to get the opcode.
	// an opcode can be either 1, 2, or 3 bytes long (and a specific prefix is used to indicate the length).
	opcode_t opcode = 0;
	{
		byte cur = stream.consumeByte();
		//if we have the first kind of opcode extension byte then add it to the opcode.
		if (cur == 0x0F) {
			opcode += cur;
			opcode <<= 8;

			cur = stream.consumeByte();
			//check if we have one of the next opcode extension bytes, and if so then add it
			if (cur == 0x38 || cur == 0x3A) {
				opcode += cur;
				opcode <<= 8;

				cur = stream.consumeByte();
			};
		};
		//now that we have any opcode extensions added, add the actual opcode byte.
		opcode += cur;
	};



	//next we need to get what might be the modrm byte as it's reg field can be used as part of the opcode.
	//we dont consume the byte yet though because we don't yet know if this is actually a modrm byte.
	ModRM potentialModrm(stream.peekByte());


	instructionId_t matchedInstruction = findInstruction(opcode, prefixContext, potentialModrm, stream);

	//if the instruction we matched against required prefixes 66 and/or 67, remove them from the context.
	if(prefixContextHasFlag(instructionList[matchedInstruction].prefixContext, PREFIX_CONTEXT_PREFIX_66)){
		prefixContext = (prefixContext & (~PREFIX_CONTEXT_PREFIX_66));
	};
	if (prefixContextHasFlag(instructionList[matchedInstruction].prefixContext, PREFIX_CONTEXT_PREFIX_67)) {
		prefixContext = (prefixContext & (~PREFIX_CONTEXT_PREFIX_67));
	};

	//now that we know which instruction we are looking at, lets decode it.
	decodeInstruction(decodedInstruction, matchedInstruction, defaultAddressSize, defaultOperandSize, prefixContext, extendedPrefixData, stream);

	return decodedInstruction;
};






void instructionOperandToString(DecodedInstruction::DecodedOperand& operand, std::stringstream& stream) {
	bool typeMem_skipZero = false;


	switch (operand.decodedOperandType) {
	case DECODED_OPERAND_TYPE_NO_OPERAND:
		break;
	case DECODED_OPERAND_TYPE_IMMEDIATE:
		stream << "0x" << std::uppercase << std::hex << operand.operandData.immediate;
		break;
	case DECODED_OPERAND_TYPE_MEM:
		switch (operand.operandData.memory.size) {
		case MEMORY_OPERAND_SIZE_BYTE:
			stream << "BYTE PTR ";
			break;
		case MEMORY_OPERAND_SIZE_WORD:
			stream << "WORD PTR ";
			break;
		case MEMORY_OPERAND_SIZE_DWORD:
			stream << "DWORD PTR ";
			break;
		case MEMORY_OPERAND_SIZE_QWORD:
			stream << "QWORD PTR ";
			break;
		case MEMORY_OPERAND_SIZE_XMMWORD:
			stream << "XMMWORD PTR ";
			break;
		case MEMORY_OPERAND_SIZE_YMMWORD:
			stream << "YMMWORD PTR ";
			break;
		case MEMORY_OPERAND_SIZE_ZMMWORD:
			stream << "ZMMWORD PTR ";
			break;
		};

		if (operand.operandData.memory.segment != SEGMENT_REGISTER_NO_REGISTER) {
			stream << segmentRegisterToString[operand.operandData.memory.segment] << " : ";
		}
		stream << "[";

		if (operand.operandData.memory.scaledReg != REGISTER_NO_REGISTER) {
			stream << registerToString[operand.operandData.memory.scaledReg];
			stream << "*" << (int)(operand.operandData.memory.scalar);
			typeMem_skipZero = true;

			if (operand.operandData.memory.baseReg != REGISTER_NO_REGISTER || operand.operandData.memory.disp != 0) {
				stream << " + ";
			};
		};
		if (operand.operandData.memory.baseReg != REGISTER_NO_REGISTER) {
			stream << registerToString[operand.operandData.memory.baseReg];
			typeMem_skipZero = true;
			if (operand.operandData.memory.disp != 0) {
				stream << " + ";
			};
		};
		if (operand.operandData.memory.disp != 0 || !typeMem_skipZero) {
			stream << operand.operandData.memory.disp;
		};
		stream << "]";
		break;
	case DECODED_OPERAND_TYPE_REGISTER:
		if (operand.operandData.reg.reg != SEGMENT_REGISTER_NO_REGISTER) {
			stream << registerToString[operand.operandData.reg.reg];
			if (operand.operandData.reg.k_register != 0) {
				stream << "{k" << (int)operand.operandData.reg.k_register << "}";
			};
			if (operand.operandData.reg.z_mask_used != 0) {
				stream << "{z}";
			};
		};
		break;
	}
};

std::string Decoder::decodedInstructionToString(DecodedInstruction& decodedInstruction) {
	std::stringstream stream;
	stream << instructionName[instructionList[decodedInstruction.instruction].name];

	if (decodedInstruction.operand1.decodedOperandType != DECODED_OPERAND_TYPE_NO_OPERAND) {
		stream << " ";
		instructionOperandToString(decodedInstruction.operand1, stream);
	};
	if (decodedInstruction.operand2.decodedOperandType != DECODED_OPERAND_TYPE_NO_OPERAND) {
		stream << ", ";
		instructionOperandToString(decodedInstruction.operand2, stream);
	};
	if (decodedInstruction.operand3.decodedOperandType != DECODED_OPERAND_TYPE_NO_OPERAND) {
		stream << ", ";
		instructionOperandToString(decodedInstruction.operand3, stream);
	};
	if (decodedInstruction.operand4.decodedOperandType != DECODED_OPERAND_TYPE_NO_OPERAND) {
		stream << ", ";
		instructionOperandToString(decodedInstruction.operand4, stream);
	};

	return stream.str();
};
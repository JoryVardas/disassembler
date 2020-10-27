#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPETYPES_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPETYPES_H

#include "variant.h"

#include "x86InstructionAddressParameter.h"
#include "x86InstructionRegisterParameter.h"
#include "x86InstructionImmediateParameter.h"

using ParameterSize = std::variant<X86InstructionAddressParameterSize, RegisterSize, InstructionImmediateSize>;

#endif
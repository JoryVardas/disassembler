#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPE_H

#include <variant>
#include <memory>

#include "x86InstructionImmediateParameterPrototype.h"
#include "x86InstructionRegisterParameterPrototype.h"
#include "x86InstructionAddressParameterPrototype.h"

#include "variant.h"

using X86InstructionParameterPrototype = variant_join<X86InstructionRegisterParameterPrototype_t,
                                                      X86InstructionAddressParameterPrototype_t,
                                                      X86InstructionImmediateParameterPrototype_t>;

#endif
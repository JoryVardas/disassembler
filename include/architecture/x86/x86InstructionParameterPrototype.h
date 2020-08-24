#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPARAMETERPROTOTYPE_H

#include <variant>
#include <memory>

#include "x86InstructionImmediateParameterPrototype.h"
#include "x86InstructionRegisterParameterPrototype.h"
#include "x86InstructionAddressParameterPrototype.h"

using X86InstructionParameterPrototype = std::variant<std::shared_ptr<X86InstructionImmediateParameterPrototype>,
                                                      std::shared_ptr<X86InstructionRegisterParameterPrototype>,
                                                      std::shared_ptr<X86InstructionAddressParameterPrototype>>;

#endif
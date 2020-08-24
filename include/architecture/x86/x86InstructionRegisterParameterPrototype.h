#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H

#include <algorithm>

#include "x86InstructionRegisterParameter.h"
#include "x86InstructionRegisterParameterGroups.h"

struct X86InstructionRegisterParameterPrototype {
public:
    X86InstructionRegisterParameterPrototype();
    X86InstructionRegisterParameterPrototype(const X86InstructionRegisterParameterPrototype&);
    X86InstructionRegisterParameterPrototype(X86InstructionRegisterParameterPrototype&&);
    virtual ~X86InstructionRegisterParameterPrototype();

    virtual RegisterSize size() const = 0;
    virtual X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup&) const = 0;

    X86InstructionRegisterParameterPrototype& operator=(const X86InstructionRegisterParameterPrototype&);
    X86InstructionRegisterParameterPrototype& operator=(X86InstructionRegisterParameterPrototype&&);
};

template<RegisterSize Size>
struct X86InstructionRegisterParameterPrototypeSpecification : public X86InstructionRegisterParameterPrototype {
public:
    constexpr RegisterSize size() const override {return Size;};

    constexpr X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup& registerGroup) const override {
        return *(std::find_if(std::cbegin(registerGroup), std::cend(registerGroup), [](const X86InstructionRegisterParameter& currentRegisterParameter){
            return currentRegisterParameter.size() == Size;
        }));
    }
};

#endif
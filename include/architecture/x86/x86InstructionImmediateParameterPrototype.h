#ifndef ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H

#include "x86InstructionImmediateParameter.h"

typedef uint8_t InstructionImmediateSize;


struct X86InstructionImmediateParameterPrototype {
public:
    X86InstructionImmediateParameterPrototype();
    X86InstructionImmediateParameterPrototype(const X86InstructionImmediateParameterPrototype&);
    X86InstructionImmediateParameterPrototype(X86InstructionImmediateParameterPrototype&&);
    virtual ~X86InstructionImmediateParameterPrototype();

    virtual InstructionImmediateSize size() const = 0;
    virtual X86InstructionImmediateParameter specify(const uint64_t) const = 0;

    X86InstructionImmediateParameterPrototype& operator=(const X86InstructionImmediateParameterPrototype&);
    X86InstructionImmediateParameterPrototype& operator=(X86InstructionImmediateParameterPrototype&&);
};

template<InstructionImmediateSize Size>
struct X86InstructionImmediateParameterPrototypeSpecification : public X86InstructionImmediateParameterPrototype {
public:
    constexpr InstructionImmediateSize size() const {return Size;};

    constexpr X86InstructionImmediateParameter specify(const uint64_t value) const{
        return X86InstructionImmediateParameter(value);
    }
};

#endif
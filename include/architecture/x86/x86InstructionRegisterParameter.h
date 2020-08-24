#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETER_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETER_H

#include <instructionParameter.h>

#include "common.h"


typedef uint16_t RegisterSize;

struct X86InstructionRegisterParameter : public InstructionParameter {
public:
    X86InstructionRegisterParameter();
    X86InstructionRegisterParameter(const X86InstructionRegisterParameter&);
    X86InstructionRegisterParameter(X86InstructionRegisterParameter&&);
    X86InstructionRegisterParameter(const std::string& name, const RegisterSize size);
    ~X86InstructionRegisterParameter();

    std::string toString() const override;
    RegisterSize size() const;

    X86InstructionRegisterParameter& operator=(const X86InstructionRegisterParameter&);
    X86InstructionRegisterParameter& operator=(X86InstructionRegisterParameter&&);
private:
    std::string _name;
    RegisterSize _size;
    PADDING(6);
};

#endif
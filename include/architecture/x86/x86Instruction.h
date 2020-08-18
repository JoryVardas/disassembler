#ifndef ARCHITECTURE_X86_X86INSTRUCTION_H
#define ARCHITECTURE_X86_X86INSTRUCTION_H

#include <instruction.h>
#include "x86InstructionPrefix.h"

class X86Instruction : public Instruction {
public:
        X86Instruction();
        X86Instruction(const std::vector<X86InstructionPrefix>& prefixList);
        X86Instruction(X86Instruction&);
        X86Instruction(X86Instruction&&);
        ~X86Instruction();

        std::string toString() const override;

        void operator=(X86Instruction&) = delete;
        void operator=(X86Instruction&&) = delete;
protected:
private:
std::vector<X86InstructionPrefix> _prefixList;
};

#endif
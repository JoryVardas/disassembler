#ifndef ARCHITECTURE_X86_X86INSTRUCTION_H
#define ARCHITECTURE_X86_X86INSTRUCTION_H

#include "x86InstructionPrefix.h"
#include <instruction.h>

typedef uint32_t X86InstructionOpcode;

class X86Instruction : public Instruction {
  public:
    X86Instruction();
    X86Instruction(
        const std::string& name,
        const std::vector<X86InstructionPrefix>& prefixList,
        const std::vector<std::shared_ptr<InstructionParameter>>& parameters);
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
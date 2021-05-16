#ifndef ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETER_H
#define ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETER_H

#include <instructionParameter.h>

typedef uint8_t InstructionImmediateSize;

struct X86InstructionImmediateParameter : public InstructionParameter {
  public:
    X86InstructionImmediateParameter();
    X86InstructionImmediateParameter(const X86InstructionImmediateParameter&);
    X86InstructionImmediateParameter(X86InstructionImmediateParameter&&);
    X86InstructionImmediateParameter(const uint64_t value);
    ~X86InstructionImmediateParameter();

    std::string toString() const override;

    X86InstructionImmediateParameter&
    operator=(const X86InstructionImmediateParameter&);
    X86InstructionImmediateParameter&
    operator=(X86InstructionImmediateParameter&&);

  private:
    uint64_t _immediateValue = 0;
};

#endif
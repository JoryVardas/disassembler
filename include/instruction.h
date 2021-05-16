#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <memory>
#include <string>
#include <vector>

#include "instructionParameter.h"

class Instruction {
  public:
    Instruction();
    Instruction(Instruction&);
    Instruction(Instruction&&);

    Instruction(
        const std::string& name,
        const std::vector<std::shared_ptr<InstructionParameter>>& parameters);

    virtual ~Instruction();

    virtual std::string toString() const = 0;

    void operator=(Instruction&) = delete;
    void operator=(Instruction&&) = delete;

  protected:
    std::string _name;
    std::vector<std::shared_ptr<InstructionParameter>> _parameters;
};

#endif
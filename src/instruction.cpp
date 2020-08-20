#include <instruction.h>

Instruction::Instruction() = default;
Instruction::Instruction(Instruction&) = default;
Instruction::Instruction(Instruction&&) = default;

Instruction::Instruction(const std::string& name) :
    _name(name) {}

Instruction::~Instruction() = default;
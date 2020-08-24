#include <instruction.h>

Instruction::Instruction() = default;
Instruction::Instruction(Instruction&) = default;
Instruction::Instruction(Instruction&&) = default;

Instruction::Instruction(const std::string& name, const std::vector<std::shared_ptr<InstructionParameter>>& parameters) :
    _name(name), _parameters(parameters) {}

Instruction::~Instruction() = default;
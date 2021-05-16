#include <architecture/x86/x86Instruction.h>

#include <algorithm>
#include <sstream>

X86Instruction::X86Instruction() = default;
X86Instruction::X86Instruction(
    const std::string& name,
    const std::vector<X86InstructionPrefix>& prefixList,
    const std::vector<std::shared_ptr<InstructionParameter>>& parameters)
    : Instruction(name, parameters), _prefixList(prefixList) {}
X86Instruction::X86Instruction(X86Instruction&) = default;
X86Instruction::X86Instruction(X86Instruction&&) = default;
X86Instruction::~X86Instruction() = default;

std::string X86Instruction::toString() const {
    std::stringstream returnString;
    returnString << _name;

    if (std::size(_parameters) > 0) {
        auto curParameter = std::cbegin(_parameters);
        auto endParameter = std::cend(_parameters);

        returnString << " " << (*(curParameter++))->toString();
        std::for_each(curParameter, endParameter,
                      [&returnString](const auto& parameter) {
                          returnString << ", " << parameter->toString();
                      });
    }

    return returnString.str();
}
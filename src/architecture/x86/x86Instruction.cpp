#include <architecture\x86\x86Instruction.h>

#include <sstream>

X86Instruction::X86Instruction() = default;
X86Instruction::X86Instruction(const std::string& name, const std::vector<X86InstructionPrefix>& prefixList, const std::vector<std::shared_ptr<InstructionParameter>>& parameters) :
        Instruction(name, parameters), _prefixList(prefixList) {}
X86Instruction::X86Instruction(X86Instruction&) = default;
X86Instruction::X86Instruction(X86Instruction&&) = default;
X86Instruction::~X86Instruction() = default;
        
std::string X86Instruction::toString() const {
        std::stringstream returnString;
        returnString << "[";

        for(X86InstructionPrefix prefix : _prefixList){
                returnString << X86InstructionPrefixToString(prefix) << ", ";
        }

        returnString << "] ";
        returnString << _name << " ";

        for(const std::shared_ptr<InstructionParameter>& parameter : _parameters){
                returnString << parameter->toString() << ", ";
        }

        return returnString.str();
}
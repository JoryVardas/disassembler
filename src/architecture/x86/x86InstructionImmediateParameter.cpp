#include <architecture/x86/x86InstructionImmediateParameter.h>

#include <sstream>

X86InstructionImmediateParameter::X86InstructionImmediateParameter() = default;
X86InstructionImmediateParameter::X86InstructionImmediateParameter(const X86InstructionImmediateParameter&) = default;
X86InstructionImmediateParameter::X86InstructionImmediateParameter(X86InstructionImmediateParameter&&) = default;
X86InstructionImmediateParameter::X86InstructionImmediateParameter(const uint64_t value) : _immediateValue(value) {}
X86InstructionImmediateParameter::~X86InstructionImmediateParameter() = default;

std::string X86InstructionImmediateParameter::toString() const {
    std::stringstream retString;
    retString << std::hex << "0x" << _immediateValue;
    return retString.str();
}

X86InstructionImmediateParameter& X86InstructionImmediateParameter::operator=(const X86InstructionImmediateParameter&) = default;
X86InstructionImmediateParameter& X86InstructionImmediateParameter::operator=(X86InstructionImmediateParameter&&) = default;
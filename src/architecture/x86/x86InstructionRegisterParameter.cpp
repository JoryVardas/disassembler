#include <architecture/x86/x86InstructionRegisterParameter.h>

X86InstructionRegisterParameter::X86InstructionRegisterParameter() = default;
X86InstructionRegisterParameter::X86InstructionRegisterParameter(
    const X86InstructionRegisterParameter&) = default;
X86InstructionRegisterParameter::X86InstructionRegisterParameter(
    X86InstructionRegisterParameter&&) = default;
X86InstructionRegisterParameter::X86InstructionRegisterParameter(
    const std::string& name, const RegisterSize size)
    : _name(name), _size(size) {}
X86InstructionRegisterParameter::~X86InstructionRegisterParameter() = default;

std::string X86InstructionRegisterParameter::toString() const { return _name; }
RegisterSize X86InstructionRegisterParameter::size() const { return _size; }

X86InstructionRegisterParameter& X86InstructionRegisterParameter::operator=(
    const X86InstructionRegisterParameter&) = default;
X86InstructionRegisterParameter& X86InstructionRegisterParameter::operator=(
    X86InstructionRegisterParameter&&) = default;
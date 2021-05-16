#include <architecture/x86/x86InstructionRegisterParameterPrototype.h>

X86InstructionSingleRegisterParameterPrototypeSpecification::
    X86InstructionSingleRegisterParameterPrototypeSpecification() = default;
X86InstructionSingleRegisterParameterPrototypeSpecification::
    X86InstructionSingleRegisterParameterPrototypeSpecification(
        const X86InstructionSingleRegisterParameterPrototypeSpecification&) =
        default;
X86InstructionSingleRegisterParameterPrototypeSpecification::
    X86InstructionSingleRegisterParameterPrototypeSpecification(
        X86InstructionSingleRegisterParameterPrototypeSpecification&&) =
        default;
X86InstructionSingleRegisterParameterPrototypeSpecification::
    X86InstructionSingleRegisterParameterPrototypeSpecification(
        const std::string& registerName)
    : _registerName(registerName){};
X86InstructionSingleRegisterParameterPrototypeSpecification::
    ~X86InstructionSingleRegisterParameterPrototypeSpecification() = default;

RegisterSize
X86InstructionSingleRegisterParameterPrototypeSpecification::size() const {
    return X86InstructionRegisterParameterList.at(_registerName).size();
}
X86InstructionRegisterParameter
X86InstructionSingleRegisterParameterPrototypeSpecification::specify(
    const X86InstructionRegisterParameterGroup&) const {
    return X86InstructionRegisterParameterList.at(_registerName);
}

X86InstructionSingleRegisterParameterPrototypeSpecification&
X86InstructionSingleRegisterParameterPrototypeSpecification::operator=(
    const X86InstructionSingleRegisterParameterPrototypeSpecification&) =
    default;
X86InstructionSingleRegisterParameterPrototypeSpecification&
X86InstructionSingleRegisterParameterPrototypeSpecification::operator=(
    X86InstructionSingleRegisterParameterPrototypeSpecification&&) = default;

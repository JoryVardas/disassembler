#include <instructionParameter.h>

InstructionParameter::InstructionParameter() = default;
InstructionParameter::InstructionParameter(const InstructionParameter&) = default;
InstructionParameter::InstructionParameter(InstructionParameter&&) = default;

InstructionParameter::InstructionParameter(const InstructionParameterType type, const InstructionParameterDirection direction) :
    _parameterType(type), _parameterDirection(direction) {}

InstructionParameter::~InstructionParameter() = default;

InstructionParameterType InstructionParameter::getType() const {
    return _parameterType;
}
InstructionParameterDirection InstructionParameter::getDirection() const {
    return _parameterDirection;
}

InstructionParameter& InstructionParameter::operator=(const InstructionParameter&) = default;
InstructionParameter& InstructionParameter::operator=(InstructionParameter&&) = default;
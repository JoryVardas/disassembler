#include <immediateParameter.h>

ImmediateParameter::ImmediateParameter() = default;
ImmediateParameter::ImmediateParameter(ImmediateParameter&) = default;
ImmediateParameter::ImmediateParameter(ImmediateParameter&&) = default;
ImmediateParameter::~ImmediateParameter() = default;

std::string ImmediateParameter::toString() const{
        return std::to_string(_value);
}

ImmediateParameter& ImmediateParameter::operator=(ImmediateParameter&) = default;
ImmediateParameter& ImmediateParameter::operator=(ImmediateParameter&&) = default;
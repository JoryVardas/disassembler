#include <registerParameter.h>

RegisterParameter::RegisterParameter() = default;
RegisterParameter::RegisterParameter(RegisterParameter&) = default;
RegisterParameter::RegisterParameter(RegisterParameter&&) = default;
RegisterParameter::~RegisterParameter() = default;

std::string RegisterParameter::toString() const {
        return _name;
}

RegisterParameter& RegisterParameter::operator=(RegisterParameter&) = default;
RegisterParameter& RegisterParameter::operator=(RegisterParameter&&) = default;
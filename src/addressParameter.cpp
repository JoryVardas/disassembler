#include <addressParameter.h>

#include <sstream>

AddressParameter::AddressParameter() = default;
AddressParameter::AddressParameter(AddressParameter&) = default;
AddressParameter::AddressParameter(AddressParameter&&) = default;
AddressParameter::~AddressParameter() = default;

std::string AddressParameter::toString() const{
        std::stringstream returnString;
        returnString << "[";
        switch (_addressType){
                case AddressParameterType::REGISTER:
                        returnString << _addressRegister.toString();
                        break;
                case AddressParameterType::VALUE:
                        returnString << _addressValue;
                        break;
                case AddressParameterType::VALUE_REGISTER_SCALE:
                        returnString << _addressValue << " + " << _addressRegister.toString() << "*" << _addressScale;
        }

        returnString << "]";
        return returnString.str();
}

AddressParameter& AddressParameter::operator=(AddressParameter&) = default;
AddressParameter& AddressParameter::operator=(AddressParameter&&) = default;
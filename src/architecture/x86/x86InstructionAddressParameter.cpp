#include <architecture\x86\x86InstructionAddressParameter.h>

#include <sstream>

const std::string X86InstructionAddressParameterSizeToString(const X86InstructionAddressParameterSize addressParameterSize) {
    switch(addressParameterSize) {
        case X86InstructionAddressParameterSize::BYTE_PTR:
            return "BYTE";
        case X86InstructionAddressParameterSize::WORD_PTR:
            return "WORD";
        case X86InstructionAddressParameterSize::DWORD_PTR:
            return "DWORD";
        case X86InstructionAddressParameterSize::QWORD_PTR:
            return "QWORD";
        case X86InstructionAddressParameterSize::XMM_PTR:
            return "XMM";
        case X86InstructionAddressParameterSize::YMM_PTR:
            return "YMM";
        case X86InstructionAddressParameterSize::ZMM_PTR:
            return "ZMM";
    }

    return "UNKNOWN PTR";
}



X86InstructionAddressParameter::X86InstructionAddressParameter() = default;
X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameter&) = default;
X86InstructionAddressParameter::X86InstructionAddressParameter(X86InstructionAddressParameter&&) = default;

X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressScaleFactor scaleFactor, const X86InstructionAddressDisplacement constantDisplacement) :
    _addressSize(addressSize), _registerBase(baseRegister), _scaleFactor(scaleFactor), _constantDisplacement(constantDisplacement) {}
X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionAddressDisplacement constantDisplacement) :
    _addressSize(addressSize), _constantDisplacement(constantDisplacement) {}
X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressDisplacement constantDisplacement) :
    _addressSize(addressSize), _registerBase(baseRegister), _constantDisplacement(constantDisplacement) {}
X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionRegisterParameter& registerDisplacement, const X86InstructionAddressDisplacement constantDisplacement) :
    _addressSize(addressSize), _registerBase(baseRegister), _registerDisplacement(registerDisplacement), _constantDisplacement(constantDisplacement) {}
X86InstructionAddressParameter::X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressScaleFactor scaleFactor, const X86InstructionRegisterParameter& registerDisplacement, const X86InstructionAddressDisplacement constantDisplacement) :
    _addressSize(addressSize), _registerBase(baseRegister), _scaleFactor(scaleFactor), _registerDisplacement(registerDisplacement), _constantDisplacement(constantDisplacement) {}

X86InstructionAddressParameter::~X86InstructionAddressParameter() = default;

std::string X86InstructionAddressParameter::toString() const{
    std::stringstream returnString;
    returnString << X86InstructionAddressParameterSizeToString(_addressSize) << " [";

    if (_registerBase) returnString << _registerBase.value().toString();
    if (_scaleFactor != 1) returnString << "*" << std::to_string(_scaleFactor);
    if (_registerDisplacement) returnString << " + " << _registerDisplacement.value().toString();
    if (_constantDisplacement != 0) returnString << " + " << std::to_string(_constantDisplacement);

    returnString << "]";
    return returnString.str();
}

X86InstructionAddressParameter& X86InstructionAddressParameter::operator=(const X86InstructionAddressParameter&) = default;
X86InstructionAddressParameter& X86InstructionAddressParameter::operator=(X86InstructionAddressParameter&&) = default;
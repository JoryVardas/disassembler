#ifndef ARCHITECTURE_X86_X86INSTRUCTIONADDRESSPARAMETER_H
#define ARCHITECTURE_X86_X86INSTRUCTIONADDRESSPARAMETER_H

#include <optional>

#include <instructionParameter.h>
#include "x86InstructionRegisterParameter.h"

#include <common.h>

enum class X86InstructionAddressParameterSize {
    BYTE_PTR = 0,
    WORD_PTR,
    DWORD_PTR,
    QWORD_PTR,
    XMM_PTR,
    YMM_PTR,
    ZMM_PTR
};
const std::string X86InstructionAddressParameterSizeToString(const X86InstructionAddressParameterSize);

typedef uint8_t X86InstructionAddressScaleFactor;
typedef uint64_t X86InstructionAddressDisplacement;

struct X86InstructionAddressParameter : public InstructionParameter {
public:
    X86InstructionAddressParameter();
    X86InstructionAddressParameter(const X86InstructionAddressParameter&);
    X86InstructionAddressParameter(X86InstructionAddressParameter&&);

    X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressScaleFactor scaleFactor = 1, const X86InstructionAddressDisplacement constantDisplacement = 0);
    X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionAddressDisplacement constantDisplacement);
    X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressDisplacement constantDisplacement);
    X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionRegisterParameter& registerDisplacement, const X86InstructionAddressDisplacement constantDisplacement = 0);
    X86InstructionAddressParameter(const X86InstructionAddressParameterSize addressSize, const X86InstructionRegisterParameter& baseRegister, const X86InstructionAddressScaleFactor scaleFactor, const X86InstructionRegisterParameter& registerDisplacement, const X86InstructionAddressDisplacement constantDisplacement = 0);

    ~X86InstructionAddressParameter();

    std::string toString() const override;

    X86InstructionAddressParameter& operator=(const X86InstructionAddressParameter&);
    X86InstructionAddressParameter& operator=(X86InstructionAddressParameter&&);
private:
    X86InstructionAddressParameterSize _addressSize = X86InstructionAddressParameterSize::BYTE_PTR;
    PADDING(4);
    std::optional<X86InstructionRegisterParameter> _registerBase;
    X86InstructionAddressScaleFactor _scaleFactor = 1;
    PADDING(7);
    std::optional<X86InstructionRegisterParameter> _registerDisplacement;
    X86InstructionAddressDisplacement _constantDisplacement = 0;
};

#endif
#ifndef ARCHITECTURE_X86_X86INSTRUCTIONADDRESSPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONADDRESSPARAMETERPROTOTYPE_H

#include <algorithm>
#include <memory>

#include "x86InstructionAddressParameter.h"
#include "x86InstructionRegisterParameterList.h"
#include "x86Modrm.h"
#include "x86Environment.h"
#include "variant.h"
#include "x86InstructionParameterPrototypeTypes.h"

template<X86InstructionAddressParameterSize Size>
struct X86InstructionAddressParameterPrototypeSpecification {
public:
    constexpr X86InstructionAddressParameterSize size() const {return Size;};

    constexpr X86InstructionAddressParameter specify(X86Environment::X86AddressMode addressMode, modrm_t modrm, sib_t sib, X86InstructionAddressDisplacement displacement) const {
        // Check if the modrm RM encodes a register instead of an address.
        if (getModrmMod(modrm) == std::byte(3)) return X86InstructionAddressParameter();

        const std::optional<X86InstructionRegisterParameter> baseRegister = [&addressMode, &modrm, &sib]() -> std::optional<X86InstructionRegisterParameter> {
            if(addressMode == X86Environment::X86AddressMode::X16){
                switch(static_cast<uint8_t>(getModrmRM(modrm))){
                    case 0:
                    case 1:
                        return X86InstructionRegisterParameterList.at("BX");
                    case 2:
                    case 3:
                        return X86InstructionRegisterParameterList.at("BP");
                    case 4:
                        return X86InstructionRegisterParameterList.at("SI");
                    case 5:
                        return X86InstructionRegisterParameterList.at("DI");
                    case 6:
                        if(getModrmMod(modrm) == std::byte(0))
                            return std::optional<X86InstructionRegisterParameter>();
                        else
                            return X86InstructionRegisterParameterList.at("BP");
                    case 7:
                        return X86InstructionRegisterParameterList.at("BX");
                }
            }
            else {
                switch(static_cast<uint8_t>(getModrmRM(modrm))){
                    case 0:
                        return X86InstructionRegisterParameterList.at("EAX");
                    case 1:
                        return X86InstructionRegisterParameterList.at("ECX");
                    case 2:
                        return X86InstructionRegisterParameterList.at("EDX");
                    case 3:
                        return X86InstructionRegisterParameterList.at("EBX");
                    case 4:
                        switch(static_cast<uint8_t>(getSibIndex(sib))){
                            case 0:
                                return X86InstructionRegisterParameterList.at("EAX");
                            case 1:
                                return X86InstructionRegisterParameterList.at("ECX");
                            case 2:
                                return X86InstructionRegisterParameterList.at("EDX");
                            case 3:
                                return X86InstructionRegisterParameterList.at("EBX");
                            case 4:
                                return std::optional<X86InstructionRegisterParameter>();
                            case 5:
                                return X86InstructionRegisterParameterList.at("EBP");
                            case 6:
                                return X86InstructionRegisterParameterList.at("ESI");
                            case 7:
                                return X86InstructionRegisterParameterList.at("EDI");
                        }
                    case 5:
                        if (getModrmMod(modrm) == std::byte(0))
                            return std::optional<X86InstructionRegisterParameter>();
                        else
                            return X86InstructionRegisterParameterList.at("EBP");
                    case 6:
                        return X86InstructionRegisterParameterList.at("ESI");
                    case 7:
                        return X86InstructionRegisterParameterList.at("EDI");
                }
            }
            return std::optional<X86InstructionRegisterParameter>();
        }();

        const std::optional<X86InstructionRegisterParameter> registerDisplacement = [&addressMode, &modrm, &sib]() -> std::optional<X86InstructionRegisterParameter> {
            if (addressMode == X86Environment::X86AddressMode::X16){
                switch(static_cast<uint8_t>(getModrmRM(modrm))){
                    case 0:
                        return X86InstructionRegisterParameterList.at("SI");
                    case 1:
                        return X86InstructionRegisterParameterList.at("DI");
                    case 2:
                        return X86InstructionRegisterParameterList.at("SI");
                    case 3:
                        return X86InstructionRegisterParameterList.at("DI");
                    default:
                        return std::optional<X86InstructionRegisterParameter>();
                }
            }
            else {
                if(getModrmRM(modrm) != std::byte(4))
                    return std::optional<X86InstructionRegisterParameter>();
                else {
                    switch (static_cast<uint8_t>(getSibBase(sib))){
                        case 0:
                            return X86InstructionRegisterParameterList.at("EAX");
                        case 1:
                            return X86InstructionRegisterParameterList.at("ECX");
                        case 2:
                            return X86InstructionRegisterParameterList.at("EDX");
                        case 3:
                            return X86InstructionRegisterParameterList.at("EBX");
                        case 4:
                            return X86InstructionRegisterParameterList.at("ESP");
                        case 5:
                            if (getModrmMod(modrm) == std::byte(0))
                                return std::optional<X86InstructionRegisterParameter>();
                            else
                                return X86InstructionRegisterParameterList.at("EBP");
                        case 6:
                            return X86InstructionRegisterParameterList.at("ESI");
                        case 7:
                            return X86InstructionRegisterParameterList.at("EDI");
                    }
                }
            }
            return std::optional<X86InstructionRegisterParameter>();
        }();

        const X86InstructionAddressScaleFactor scale = static_cast<X86InstructionAddressScaleFactor>(std::byte(1) << static_cast<uint8_t>(getSibScale(sib)));
        
        if (baseRegister.has_value() && registerDisplacement.has_value()){
            return X86InstructionAddressParameter(Size, baseRegister.value(), scale, registerDisplacement.value(), displacement);
        }
        else if (baseRegister.has_value()){
            return X86InstructionAddressParameter(Size, baseRegister.value(), scale, displacement);
        }
        else if (registerDisplacement.has_value()){
            // I'm not sure if this state is possible in practice
            return X86InstructionAddressParameter();
        }
        else {
            return X86InstructionAddressParameter(Size, displacement);
        }
    }
};

using X86InstructionAddressParameterPrototype_t = std::variant<X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::BYTE_PTR>,
                                                               X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::WORD_PTR>,
                                                               X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::DWORD_PTR>,
                                                               X86InstructionAddressParameterPrototypeSpecification<X86InstructionAddressParameterSize::QWORD_PTR>>;

const auto x86InstructionAddressParameterPrototypeGetSize = [](const auto & addressPrototype)->ParameterSize {
    return addressPrototype.size();
};
struct x86InstructionAddressParameterPrototypeSpecify{
    
    template<X86InstructionAddressParameterSize T>
    std::shared_ptr<InstructionParameter> operator() (const X86InstructionAddressParameterPrototypeSpecification<T>& ref, const X86Environment::X86AddressMode addressMode, const modrm_t modrm, const sib_t sib, const X86InstructionAddressDisplacement displacement) const {
        return std::make_shared<X86InstructionAddressParameter>(ref.specify(addressMode, modrm, sib, displacement));
    }
    
    template <typename T>
    std::shared_ptr<InstructionParameter> operator() (const T&, const X86Environment::X86AddressMode, const modrm_t, const sib_t, const X86InstructionAddressDisplacement) const {
        return nullptr;
    }
};

#endif
#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H

#include <algorithm>
#include <memory>
#include "variant.h"

#include "x86InstructionRegisterParameter.h"
#include "x86InstructionRegisterParameterGroups.h"

#include "x86InstructionParameterPrototypeTypes.h"

template<RegisterSize Size>
struct X86InstructionRegisterParameterPrototypeSpecification {
public:
    constexpr RegisterSize size() const {return Size;};

    constexpr X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup& registerGroup) const {
        return *(std::find_if(std::cbegin(registerGroup), std::cend(registerGroup), [](const X86InstructionRegisterParameter& currentRegisterParameter){
            return currentRegisterParameter.size() == Size;
        }));
    }
};

struct X86InstructionSingleRegisterParameterPrototypeSpecification {
public:
    X86InstructionSingleRegisterParameterPrototypeSpecification();
    X86InstructionSingleRegisterParameterPrototypeSpecification(const X86InstructionSingleRegisterParameterPrototypeSpecification&);
    X86InstructionSingleRegisterParameterPrototypeSpecification(X86InstructionSingleRegisterParameterPrototypeSpecification&&);
    X86InstructionSingleRegisterParameterPrototypeSpecification(const std::string& registerName);
    ~X86InstructionSingleRegisterParameterPrototypeSpecification();

    RegisterSize size() const;
    X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup& registerGroup) const;
    
    X86InstructionSingleRegisterParameterPrototypeSpecification& operator=(const X86InstructionSingleRegisterParameterPrototypeSpecification&);
    X86InstructionSingleRegisterParameterPrototypeSpecification& operator=(X86InstructionSingleRegisterParameterPrototypeSpecification&&);
private:
    std::string _registerName;
};

using X86InstructionRegisterParameterPrototype_t = std::variant<X86InstructionSingleRegisterParameterPrototypeSpecification,
                                                              X86InstructionRegisterParameterPrototypeSpecification<8>,
                                                              X86InstructionRegisterParameterPrototypeSpecification<16>,
                                                              X86InstructionRegisterParameterPrototypeSpecification<32>>;

const auto x86InstructionRegisterParameterPrototypeGetSize = [](const auto & registerPrototype)->ParameterSize {
    return registerPrototype.size();
};

auto x86InstructionRegisterParameterPrototypeSpecify = make_visitor(
    []<RegisterSize T>(const X86InstructionRegisterParameterPrototypeSpecification<T>& ref, const X86InstructionRegisterParameterGroup& registerGroup) ->std::shared_ptr<InstructionParameter>{
        return std::make_shared<X86InstructionRegisterParameter>(ref.specify(registerGroup));
    },
    [](const X86InstructionSingleRegisterParameterPrototypeSpecification& ref, const X86InstructionRegisterParameterGroup& registerGroup) ->std::shared_ptr<InstructionParameter>{
        return std::make_shared<X86InstructionRegisterParameter>(ref.specify(registerGroup));
    },
    [](const auto&, const X86InstructionRegisterParameterGroup&)->std::shared_ptr<InstructionParameter>{
        return nullptr;
    }
);

#endif
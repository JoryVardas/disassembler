#ifndef ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONREGISTERPARAMETERPROTOTYPE_H

#include <algorithm>
#include <memory>
#include "variant.h"

#include "x86InstructionRegisterParameter.h"
#include "x86InstructionRegisterParameterGroups.h"

#include "x86InstructionParameterPrototypeTypes.h"

struct X86InstructionRegisterParameterPrototype {
public:
    X86InstructionRegisterParameterPrototype();
    X86InstructionRegisterParameterPrototype(const X86InstructionRegisterParameterPrototype&);
    X86InstructionRegisterParameterPrototype(X86InstructionRegisterParameterPrototype&&);
    virtual ~X86InstructionRegisterParameterPrototype();

    virtual RegisterSize size() const = 0;
    virtual X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup&) const = 0;

    X86InstructionRegisterParameterPrototype& operator=(const X86InstructionRegisterParameterPrototype&);
    X86InstructionRegisterParameterPrototype& operator=(X86InstructionRegisterParameterPrototype&&);
};

template<RegisterSize Size>
struct X86InstructionRegisterParameterPrototypeSpecification : public X86InstructionRegisterParameterPrototype {
public:
    constexpr RegisterSize size() const override {return Size;};

    constexpr X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup& registerGroup) const override {
        return *(std::find_if(std::cbegin(registerGroup), std::cend(registerGroup), [](const X86InstructionRegisterParameter& currentRegisterParameter){
            return currentRegisterParameter.size() == Size;
        }));
    }
};

struct X86InstructionSingleRegisterParameterPrototypeSpecification : public X86InstructionRegisterParameterPrototype {
public:
    X86InstructionSingleRegisterParameterPrototypeSpecification();
    X86InstructionSingleRegisterParameterPrototypeSpecification(const X86InstructionSingleRegisterParameterPrototypeSpecification&);
    X86InstructionSingleRegisterParameterPrototypeSpecification(X86InstructionSingleRegisterParameterPrototypeSpecification&&);
    X86InstructionSingleRegisterParameterPrototypeSpecification(const std::string& registerName);
    ~X86InstructionSingleRegisterParameterPrototypeSpecification();

    RegisterSize size() const override;
    X86InstructionRegisterParameter specify(const X86InstructionRegisterParameterGroup& registerGroup) const override;
    
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
struct x86InstructionRegisterParameterPrototypeSpecify{
    
    template<RegisterSize T>
    std::shared_ptr<InstructionParameter> operator() (const X86InstructionRegisterParameterPrototypeSpecification<T>& ref, const X86InstructionRegisterParameterGroup& registerGroup) const {
        return std::make_shared<X86InstructionRegisterParameter>(ref.specify(registerGroup));
    }
    std::shared_ptr<InstructionParameter> operator() (const X86InstructionSingleRegisterParameterPrototypeSpecification& ref, const X86InstructionRegisterParameterGroup& registerGroup) const;
    
    template <typename T>
    std::shared_ptr<InstructionParameter> operator() (const T&, const X86InstructionRegisterParameterGroup&) const {
        return nullptr;
    }
};

#endif
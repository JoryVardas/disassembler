#ifndef ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H

#include <memory>
#include "x86InstructionImmediateParameter.h"
#include "variant.h"
#include "x86InstructionParameterPrototypeTypes.h"


template<InstructionImmediateSize Size>
struct X86InstructionImmediateParameterPrototypeSpecification {
public:
    constexpr InstructionImmediateSize size() const {return Size;};

    constexpr X86InstructionImmediateParameter specify(const uint64_t value) const{
        return X86InstructionImmediateParameter(value);
    }
};

using X86InstructionImmediateParameterPrototype_t = std::variant<X86InstructionImmediateParameterPrototypeSpecification<8>,
                                                                 X86InstructionImmediateParameterPrototypeSpecification<16>,
                                                                 X86InstructionImmediateParameterPrototypeSpecification<32>>;

const auto x86InstructionImmediateParameterPrototypeGetSize = [](const auto & immediatePrototype)->ParameterSize {
    return immediatePrototype.size();
};
struct x86InstructionImmediateParameterPrototypeSpecify{

    template<InstructionImmediateSize T>
    std::shared_ptr<InstructionParameter> operator() (const X86InstructionImmediateParameterPrototypeSpecification<T>& ref, const uint64_t& value) const {
        return std::make_shared<X86InstructionImmediateParameter>(ref.specify(value));
    }
    
    template <typename T>
    std::shared_ptr<InstructionParameter> operator() (const T&, const uint64_t&) const {
        return nullptr;
    }
};

#endif
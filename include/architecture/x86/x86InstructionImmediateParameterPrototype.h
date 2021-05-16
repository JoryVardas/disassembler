#ifndef ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONIMMEDIATEPARAMETERPROTOTYPE_H

#include "variant.h"
#include "x86InstructionImmediateParameter.h"
#include "x86InstructionParameterPrototypeTypes.h"
#include <memory>

template <InstructionImmediateSize Size>
struct X86InstructionImmediateParameterPrototypeSpecification {
  public:
    constexpr InstructionImmediateSize size() const { return Size; };

    constexpr X86InstructionImmediateParameter
    specify(const uint64_t value) const {
        return X86InstructionImmediateParameter(value);
    }
};

using X86InstructionImmediateParameterPrototype_t =
    std::variant<X86InstructionImmediateParameterPrototypeSpecification<8>,
                 X86InstructionImmediateParameterPrototypeSpecification<16>,
                 X86InstructionImmediateParameterPrototypeSpecification<32>>;

const auto x86InstructionImmediateParameterPrototypeGetSize =
    [](const auto& immediatePrototype) -> ParameterSize {
    return immediatePrototype.size();
};
auto x86InstructionImmediateParameterPrototypeSpecify = make_visitor(

    []<InstructionImmediateSize T>(
        const X86InstructionImmediateParameterPrototypeSpecification<T>& ref,
        const uint64_t& value) -> std::shared_ptr<InstructionParameter> {
        return std::make_shared<X86InstructionImmediateParameter>(
            ref.specify(value));
    },
    [](const auto&, const uint64_t&) -> std::shared_ptr<InstructionParameter> {
        return nullptr;
    });

#endif
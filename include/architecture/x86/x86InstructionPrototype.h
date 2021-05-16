#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPE_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPROTOTYPE_H

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "x86Instruction.h"
#include "x86InstructionPrefix.h"

#include <bidirectionalIterator.h>
#include <common.h>

#include "x86Environment.h"
#include "x86InstructionParameterPrototype.h"

enum class X86InstructionParameterLocation {
    CONSTANT,
    IMMEDIATE,
    MODRM_REG,
    MODRM_RM,
    IMPLIED
};

using InstructionParameterGroup = std::vector<X86InstructionParameterPrototype>;
using InstructionParameterPrototype =
    std::pair<X86InstructionParameterLocation, InstructionParameterGroup>;

struct X86InstructionPrototype {
  public:
    using customComparisonFunction = std::function<bool(
        const X86InstructionPrototype& self,
        const std::vector<X86InstructionPrefix>&, const X86InstructionOpcode,
        BidirectionalIterator<std::byte>&)>;

    X86InstructionPrototype();
    X86InstructionPrototype(const X86InstructionPrototype&);
    X86InstructionPrototype(X86InstructionPrototype&&);
    X86InstructionPrototype(const std::string& name,
                            const X86Environment::X86InstructionMode validMode,
                            const X86InstructionOpcode opcode);
    X86InstructionPrototype(
        const std::string& name,
        const X86Environment::X86InstructionMode validMode,
        const std::optional<std::vector<X86InstructionPrefix>>&
            requiredPrefixList,
        const X86InstructionOpcode opcode,
        const std::optional<customComparisonFunction>& customComparison);
    X86InstructionPrototype(
        const std::string& name,
        const X86Environment::X86InstructionMode validMode,
        const std::optional<std::vector<X86InstructionPrefix>>&
            requiredPrefixList,
        const X86InstructionOpcode opcode,
        const std::vector<InstructionParameterPrototype>&
            possibleInstructionParameters,
        const std::optional<customComparisonFunction>& customComparison);
    X86InstructionPrototype(
        const std::string& name,
        const X86Environment::X86InstructionMode validMode,
        const std::optional<std::vector<X86InstructionPrefix>>&
            requiredPrefixList,
        const X86InstructionOpcode opcode, const uint8_t modrmOpcodeExtension,
        const std::vector<InstructionParameterPrototype>&
            possibleInstructionParameters,
        const std::optional<customComparisonFunction>&
            customComparisonFunction);
    ~X86InstructionPrototype();

    bool
    isMatch(const X86Environment::X86InstructionMode currentInstructionMode,
            const std::vector<X86InstructionPrefix>& prefixList,
            const X86InstructionOpcode opcode,
            BidirectionalIterator<std::byte>& bytesToDecode) const;
    bool prefixListMatches(
        const std::vector<X86InstructionPrefix>& prefixList) const;
    bool requiresPrefix(const X86InstructionPrefix& prefix) const;
    bool requiresNoPrefix() const;
    bool opcodeMatches(const X86InstructionOpcode opcode,
                       BidirectionalIterator<std::byte> bytesToDecode) const;

    const std::string& getInstructionName() const;
    const std::vector<InstructionParameterPrototype>
    getPossibleInstructionParameters() const;
    const X86Environment::X86InstructionMode getValidMode() const;

    X86InstructionPrototype& operator=(X86InstructionPrototype&);
    X86InstructionPrototype& operator=(X86InstructionPrototype&&);

  private:
    std::string _instructionName;
    X86Environment::X86InstructionMode _validMode;
    // if optional has no value, then it is required that the instruction no
    // have any prefixes. otherwise the list contains only the required
    // prefixes.
    std::optional<std::vector<X86InstructionPrefix>> _requiredPrefixes;
    X86InstructionOpcode _instructionOpcode;
    std::optional<uint8_t> _modrmOpcodeExtensionValue;
    std::vector<InstructionParameterPrototype>
        _instructionParameterPossibilities;
    std::optional<customComparisonFunction> _customComparison;
};

#endif
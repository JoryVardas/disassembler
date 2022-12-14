#ifndef ARCHITECTURE_X86_X86INSTRUCTIONPREFIX_H
#define ARCHITECTURE_X86_X86INSTRUCTIONPREFIX_H

#include "variant.h"
#include <cstddef>
#include <optional>
#include <string>

enum class X86InstructionRawPrefix {
    // group 4
    ADDRESS_SIZE_OVERRIDE = 0x67,

    // group 3
    OPERAND_SIZE_OVERRIDE = 0x66,

    // group 2 - segment override
    CS_SEGMENT_OVERRIDE = 0x2e,
    SS_SEGMENT_OVERRIDE = 0x36,
    DS_SEGMENT_OVERRIDE = 0x3e,
    ES_SEGMENT_OVERRIDE = 0x26,
    FS_SEGMENT_OVERRIDE = 0x64,
    GS_SEGMENT_OVERRIDE = 0x65,
    // group 2 - branch hints
    BRANCH_NOT_TAKEN = 0x2e,
    BRANCH_TAKEN = 0x3e,

    // group 1
    LOCK = 0xf0,
    REPNZ = 0xf2,
    REP = 0xf3
};

struct X86InstructionRexPrefix {
    const static std::byte IdentifierMask = std::byte(0xF0);
    const static std::byte Identifier = std::byte(0x40);

    std::byte _prefix;

    X86InstructionRexPrefix(const std::byte);
    X86InstructionRexPrefix(const X86InstructionRexPrefix&);
    X86InstructionRexPrefix(X86InstructionRexPrefix&&);
    ~X86InstructionRexPrefix();

    std::byte getW() const;
    std::byte getR() const;
    std::byte getX() const;
    std::byte getB() const;

    X86InstructionRexPrefix& operator=(const X86InstructionRexPrefix&);
    X86InstructionRexPrefix& operator=(X86InstructionRexPrefix&&);
};

using X86InstructionPrefix =
    std::variant<X86InstructionRawPrefix, X86InstructionRexPrefix>;

std::optional<X86InstructionPrefix>
decodeX86InstructionPrefix(const std::byte byteToDecode);
std::string X86InstructionPrefixToString(
    const X86InstructionPrefix prefix,
    const bool useBranchHintsInsteadOfSegmentOverrides = false);

bool operator==(const X86InstructionRawPrefix& a,
                const X86InstructionPrefix& b);
bool operator==(const X86InstructionPrefix& a,
                const X86InstructionRawPrefix& b);
bool operator==(const X86InstructionPrefix& a, const X86InstructionPrefix& b);

#endif
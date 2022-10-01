#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PREFIX_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PREFIX_HELPERS_H

#include <architecture/x86/x86InstructionPrefix.h>
#include <compare>
#include <cstddef>
#include <tuple>

#include "concepts.h"

namespace Testing::Helpers {
struct prefix_t {
    std::string name;
    std::byte value;

    prefix_t(std::string n, std::byte val) : name(n), value(val){};

    bool operator==(const prefix_t&) const = default;
};

using prefix_bytes = std::vector<std::byte>;

template <typename... Ts>
requires std::same_as<prefix_t, std::tuple_element_t<0, std::tuple<Ts...>>> &&
    all_same<Ts...>
        prefix_bytes prefixesToBytes(Ts... args) {
    return prefix_bytes{(args.value)...};
};
} // namespace Testing::Helpers

#define INTERAL_DEFINE_PREFIX(name, prefix)                                    \
    Testing::Helpers::prefix_t { #name, static_cast < std::byte>(prefix) }

#define LOCK_PREFIX INTERAL_DEFINE_PREFIX(LOCK, X86InstructionRawPrefix::LOCK)
#define CS_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(CS, X86InstructionRawPrefix::CS_SEGMENT_OVERRIDE)
#define SS_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(SS, X86InstructionRawPrefix::SS_SEGMENT_OVERRIDE)
#define DS_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(DS, X86InstructionRawPrefix::DS_SEGMENT_OVERRIDE)
#define ES_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(ES_SEGMENT_OVERRIDE,                                 \
                          X86InstructionRawPrefix::ES_SEGMENT_OVERRIDE)
#define FS_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(FS, X86InstructionRawPrefix::FS_SEGMENT_OVERRIDE)
#define GS_SEGMENT_OVERRIDE_PREFIX                                             \
    INTERAL_DEFINE_PREFIX(GS, X86InstructionRawPrefix::GS_SEGMENT_OVERRIDE)
#define BRANCH_NOT_TAKEN_PREFIX                                                \
    INTERAL_DEFINE_PREFIX(BRANCH_NOT_TAKEN,                                    \
                          X86InstructionRawPrefix::BRANCH_NOT_TAKEN)
#define BRANCH_TAKEN_PREFIX                                                    \
    INTERAL_DEFINE_PREFIX(BRANCH_TAKEN, X86InstructionRawPrefix::BRANCH_TAKEN)
#define REPNZ_PREFIX                                                           \
    INTERAL_DEFINE_PREFIX(REPNZ, X86InstructionRawPrefix::REPNZ)
#define REP_PREFIX INTERAL_DEFINE_PREFIX(REP, X86InstructionRawPrefix::REP)
#define ADDRESS_SIZE_OVERRIDE_PREFIX                                           \
    INTERAL_DEFINE_PREFIX(ADDRESS_SIZE_OVERRIDE,                               \
                          X86InstructionRawPrefix::ADDRESS_SIZE_OVERRIDE)
#define OPERAND_SIZE_OVERRIDE_PREFIX                                           \
    INTERAL_DEFINE_PREFIX(OPERAND_SIZE_OVERRIDE,                               \
                          X86InstructionRawPrefix::OPERAND_SIZE_OVERRIDE)

#define LOCK_PREFIXES concatinate(LOCK_PREFIX)
#define SEGMENT_OVERRIDE_PREFIXES                                              \
    concatinate(CS_SEGMENT_OVERRIDE_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX,        \
                DS_SEGMENT_OVERRIDE_PREFIX, ES_SEGMENT_OVERRIDE_PREFIX,        \
                FS_SEGMENT_OVERRIDE_PREFIX, GS_SEGMENT_OVERRIDE_PREFIX)
#define BRANCH_PREFIXES                                                        \
    concatinate(BRANCH_NOT_TAKEN_PREFIX, BRANCH_TAKEN_PREFIX)
#define STRING_PREFIXES concatinate(REPNZ_PREFIX, REP_PREFIX)

#define ADDRESS_SIZE_PREFIXES concatinate(ADDRESS_SIZE_OVERRIDE_PREFIX)
#define OPERAND_SIZE_PREFIXES concatinate(OPERAND_SIZE_OVERRIDE_PREFIX)

#define ADDRESS_PREFIXES                                                       \
    concatinate(ADDRESS_SIZE_PREFIXES_PREFIX, SEGMENT_OVERRIDE_PREFIXES)
#define OPERAND_PREFIXES concatinate(OPERAND_SIZE_PREFIXES)

#define ALL_PREFIXES                                                           \
    concatinate(LOCK_PREFIXES, SEGMENT_OVERRIDE_PREFIXES, BRANCH_PREFIXES,     \
                STRING_PREFIXES, ADDRESS_SIZE_PREFIXES, OPERAND_SIZE_PREFIXES)

#define REX_PREFIX INTERAL_DEFINE_PREFIX(REX, std::byte{0x40})
#define REX_W_PREFIX INTERAL_DEFINE_PREFIX(REX_W, std::byte{0x48})
#define REX_R_PREFIX INTERAL_DEFINE_PREFIX(REX_R, std::byte{0x44})
#define REX_X_PREFIX INTERAL_DEFINE_PREFIX(REX_X, std::byte{0x42})
#define REX_B_PREFIX INTERAL_DEFINE_PREFIX(REX_B, std::byte{0x41})
#define REX_WR_PREFIX INTERAL_DEFINE_PREFIX(REX_WR, std::byte{0x4C})
#define REX_WX_PREFIX INTERAL_DEFINE_PREFIX(REX_WX, std::byte{0x4A})
#define REX_WB_PREFIX INTERAL_DEFINE_PREFIX(REX_WB, std::byte{0x49})
#define REX_WRX_PREFIX INTERAL_DEFINE_PREFIX(REX_WRX, std::byte{0x4E})
#define REX_WRB_PREFIX INTERAL_DEFINE_PREFIX(REX_WRB, std::byte{0x4D})
#define REX_WXB_PREFIX INTERAL_DEFINE_PREFIX(REX_WXB, std::byte{0x4B})
#define REX_WRXB_PREFIX INTERAL_DEFINE_PREFIX(REX_WRXB, std::byte{0x4F})
#define REX_RX_PREFIX INTERAL_DEFINE_PREFIX(REX_RX, std::byte{0x46})
#define REX_RB_PREFIX INTERAL_DEFINE_PREFIX(REX_RB, std::byte{0x45})
#define REX_RXB_PREFIX INTERAL_DEFINE_PREFIX(REX_RXB, std::byte{0x47})
#define REX_XB_PREFIX INTERAL_DEFINE_PREFIX(REX_XB, std::byte{0x43})

#define ALL_REX_W_PREFIXES                                                     \
    concatinate(REX_W_PREFIX, REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX,     \
                REX_WRX_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX,                \
                REX_WRXB_PREFIX)
#define ALL_REX_R_PREFIXES                                                     \
    concatinate(REX_R_PREFIX, REX_WR_PREFIX, REX_WRX_PREFIX, REX_WRB_PREFIX,   \
                REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX)
#define ALL_REX_X_PREFIXES                                                     \
    concatinate(REX_X_PREFIX, REX_WX_PREFIX, REX_WRX_PREFIX, REX_WXB_PREFIX,   \
                REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX)
#define ALL_REX_B_PREFIXES                                                     \
    concatinate(REX_B_PREFIX, REX_WB_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX,   \
                REX_WRXB_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX)

#define ALL_REX_PREFIXES                                                       \
    concatinate(REX_PREFIX, REX_W_PREFIX, REX_R_PREFIX, REX_X_PREFIX,          \
                REX_B_PREFIX, REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX,     \
                REX_WRX_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX,                \
                REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX, \
                REX_XB_PREFIX)

#define PREFIXES(...) prefixesToBytes(__VA_ARGS__)

#define PREFIX(...) GENERATE(__VA_ARGS__)

#endif
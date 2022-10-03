#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PREFIX_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PREFIX_HELPERS_H

#include <architecture/x86/x86InstructionPrefix.h>
#include <compare>
#include <cstddef>
#include <tuple>

#include "concepts.h"

namespace Testing::Helpers {
enum class PrefixGroup {
    Group1,
    Group2,
    Group3,
    Group4,
    Extended // Used for REX, VEX, and EVEX
};

struct prefix_t {
    std::string name;
    std::byte value;
    PrefixGroup group;

    prefix_t(std::string n, std::byte val, PrefixGroup g)
        : name(n), value(val), group(g){};

    bool operator==(const prefix_t&) const = default;
};

using prefix_bytes = std::vector<std::byte>;

template <typename... Ts>
    requires std::same_as<prefix_t,
                          std::tuple_element_t<0, std::tuple<Ts...>>> &&
             all_same<Ts...>
prefix_bytes prefixesToBytes(Ts... args) {
    return prefix_bytes{(args.value)...};
};
} // namespace Testing::Helpers

#define INTERNAL_DEFINE_PREFIX(varname, name, prefix, group)                   \
    const Testing::Helpers::prefix_t varname {                                 \
#name, static_cast < std::byte>(X86InstructionRawPrefix::prefix),      \
            Testing::Helpers::PrefixGroup::group                               \
    }
#define INTERNAL_DEFINE_RAW_PREFIX(varname, name, prefix, group)               \
    const Testing::Helpers::prefix_t varname {                                 \
#name, std::byte{prefix }, Testing::Helpers::PrefixGroup::group        \
    }

namespace {
INTERNAL_DEFINE_PREFIX(LOCK_PREFIX, LOCK, LOCK, Group1);
INTERNAL_DEFINE_PREFIX(CS_SEGMENT_OVERRIDE_PREFIX, CS, CS_SEGMENT_OVERRIDE,
                       Group1);
INTERNAL_DEFINE_PREFIX(SS_SEGMENT_OVERRIDE_PREFIX, SS, SS_SEGMENT_OVERRIDE,
                       Group2);
INTERNAL_DEFINE_PREFIX(DS_SEGMENT_OVERRIDE_PREFIX, DS, DS_SEGMENT_OVERRIDE,
                       Group2);
INTERNAL_DEFINE_PREFIX(ES_SEGMENT_OVERRIDE_PREFIX, ES, ES_SEGMENT_OVERRIDE,
                       Group2);
INTERNAL_DEFINE_PREFIX(FS_SEGMENT_OVERRIDE_PREFIX, FS, FS_SEGMENT_OVERRIDE,
                       Group2);
INTERNAL_DEFINE_PREFIX(GS_SEGMENT_OVERRIDE_PREFIX, GS, GS_SEGMENT_OVERRIDE,
                       Group2);
INTERNAL_DEFINE_PREFIX(BRANCH_NOT_TAKEN_PREFIX, BRANCH_NOT_TAKEN,
                       BRANCH_NOT_TAKEN, Group2);
INTERNAL_DEFINE_PREFIX(BRANCH_TAKEN_PREFIX, BRANCH_TAKEN, BRANCH_TAKEN, Group2);
INTERNAL_DEFINE_PREFIX(REPNZ_PREFIX, REPNZ, REPNZ, Group1);
INTERNAL_DEFINE_PREFIX(REP_PREFIX, REP, REP, Group1);
INTERNAL_DEFINE_PREFIX(ADDRESS_SIZE_OVERRIDE_PREFIX, ADDRESS_SIZE_OVERRIDE,
                       ADDRESS_SIZE_OVERRIDE, Group4);
INTERNAL_DEFINE_PREFIX(OPERAND_SIZE_OVERRIDE_PREFIX, OPERAND_SIZE_OVERRIDE,
                       OPERAND_SIZE_OVERRIDE, Group3);

INTERNAL_DEFINE_RAW_PREFIX(REX_PREFIX, REX, 0x40, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_W_PREFIX, REX_W, 0x48, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_R_PREFIX, REX_R, 0x44, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_X_PREFIX, REX_X, 0x42, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_B_PREFIX, REX_B, 0x41, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WR_PREFIX, REX_WR, 0x4C, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WX_PREFIX, REX_WX, 0x4A, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WB_PREFIX, REX_WB, 0x49, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WRX_PREFIX, REX_WRX, 0x4E, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WRB_PREFIX, REX_WRB, 0x4D, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WXB_PREFIX, REX_WXB, 0x4B, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_WRXB_PREFIX, REX_WRXB, 0x4F, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_RX_PREFIX, REX_RX, 0x46, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_RB_PREFIX, REX_RB, 0x45, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_RXB_PREFIX, REX_RXB, 0x47, Extended);
INTERNAL_DEFINE_RAW_PREFIX(REX_XB_PREFIX, REX_XB, 0x43, Extended);
} // namespace

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
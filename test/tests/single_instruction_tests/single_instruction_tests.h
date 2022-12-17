#ifndef TEST_SINGLE_INSTRUCTION_TESTS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_H

#include <algorithm>
#include <cstdarg>
#include <cstddef>
#include <functional>
#include <limits>
#include <ranges>
#include <vector>

#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <fmt/format.h>

#include "helpers/concepts.h"
#include "helpers/disassembler.h"
#include "helpers/formatters.h"
#include "helpers/generators/concatenate.hpp"
#include "helpers/generators/imm.hpp"
#include "helpers/generators/implied.hpp"
#include "helpers/generators/instruction.hpp"
#include "helpers/generators/not_in.hpp"
#include "helpers/generators/prefixList.hpp"
#include "helpers/generators/resettable.hpp"
#include "helpers/generators/selector.hpp"
#include "helpers/generators/x86Environment.hpp"
#include "helpers/imm.hpp"
#include "helpers/implied.hpp"
#include "helpers/instruction.hpp"
#include "helpers/parameter.hpp"
#include "helpers/prefix.h"
#include "helpers/rm.h"

using namespace Testing::Helpers::Generators;

namespace {
template <typename... Ts>
std::vector<std::byte> makeByteVectorData(Ts... parts) {
    std::vector<std::byte> stream;
    (std::ranges::copy(parts, std::back_inserter(stream)), ...);

    return stream;
}

template <typename... Ts>
Testing::Helpers::opcode_bytes makeOpcode(Ts... args) {
    return {(std::byte{static_cast<uint8_t>(args)}, ...)};
}

#define OPCODE(...) makeOpcode(__VA_ARGS__)

} // namespace

#define IMM_TO_BYTES(disassembler, name)                                       \
    makeImmediateParameterByteData(                                            \
        DISASSEMBLER_ENDIANNESS_NATIVE(disassembler), name)

#define MAKE_BYTE_STREAM(name, ...)                                            \
    std::vector<std::byte> name##_data{                                        \
        std::move(makeByteVectorData(__VA_ARGS__))};                           \
                                                                               \
    BidirectionalIterator<std::byte> name {                                    \
        std::data(name##_data), static_cast<int64_t>(std::size(name##_data))   \
    }

#define CONDITIONAL_SECTION(expression, ...)                                   \
    if (expression)                                                            \
    SECTION(__VA_ARGS__)

using parameter_generator =
    std::unique_ptr<ResettableGenerator<Testing::Helpers::Parameter>>;

namespace PREFIXES_DETAIL_ {
using namespace Testing::Helpers;
using PrefixList = std::vector<prefix_t>;
namespace {
auto makePrefixListGenerator() {
    return Catch::Generators::value(PrefixList{});
}
// If we are passed a prefix list then it must be the NO_PREFIX_ value, so
// return a generator for it.
auto makePrefixListGenerator(PrefixList noPrefix) {
    return Catch::Generators::value(PrefixList{});
}
template <typename... Ts>
    requires std::negation_v<
        std::is_same<std::tuple_element_t<0, std::tuple<Ts...>>, PrefixList>>
auto makePrefixList(Ts... prefixList) {
    return generatePrefixList(prefixList...);
}
template <typename T, typename... Ts>
    requires std::is_same_v<T, PrefixList>
auto makePrefixList(T noPrefix, Ts... prefixList) {
    return concatenate_as<PrefixList>(Catch::Generators::value(PrefixList{}),
                                      generatePrefixList(prefixList...));
}
} // namespace
} // namespace PREFIXES_DETAIL_

#define PREFIXES_(...) PREFIXES_DETAIL_::makePrefixList(__VA_ARGS__)

#define NO_PREFIX_                                                             \
    std::vector<Testing::Helpers::prefix_t> {}

#define LOCK_PREFIXES_ LOCK_PREFIX
#define SEGMENT_OVERRIDE_PREFIXES_                                             \
    CS_SEGMENT_OVERRIDE_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX,                    \
        DS_SEGMENT_OVERRIDE_PREFIX, ES_SEGMENT_OVERRIDE_PREFIX,                \
        FS_SEGMENT_OVERRIDE_PREFIX, GS_SEGMENT_OVERRIDE_PREFIX
#define BRANCH_PREFIXES_ BRANCH_NOT_TAKEN_PREFIX, BRANCH_TAKEN_PREFIX
#define STRING_PREFIXES_ REPNZ_PREFIX, REP_PREFIX

#define ADDRESS_SIZE_PREFIXES_ ADDRESS_SIZE_OVERRIDE_PREFIX
#define OPERAND_SIZE_PREFIXES_ OPERAND_SIZE_OVERRIDE_PREFIX

#define ADDRESS_PREFIXES_ ADDRESS_SIZE_PREFIXES_, SEGMENT_OVERRIDE_PREFIXES_
#define OPERAND_PREFIXES_ OPERAND_SIZE_PREFIXES_

#define ALL_RAW_PREFIXES_                                                      \
    LOCK_PREFIXES_, SEGMENT_OVERRIDE_PREFIXES_, BRANCH_PREFIXES_,              \
        STRING_PREFIXES_, ADDRESS_SIZE_PREFIXES_, OPERAND_SIZE_PREFIXES_

#define ALL_REX_W_PREFIXES_                                                    \
    REX_W_PREFIX, REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX, REX_WRX_PREFIX, \
        REX_WRB_PREFIX, REX_WXB_PREFIX, REX_WRXB_PREFIX
#define ALL_REX_R_PREFIXES_                                                    \
    REX_R_PREFIX, REX_WR_PREFIX, REX_WRX_PREFIX, REX_WRB_PREFIX,               \
        REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX
#define ALL_REX_X_PREFIXES_                                                    \
    REX_X_PREFIX, REX_WX_PREFIX, REX_WRX_PREFIX, REX_WXB_PREFIX,               \
        REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX
#define ALL_REX_B_PREFIXES_                                                    \
    REX_B_PREFIX, REX_WB_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX,               \
        REX_WRXB_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX

#define ALL_REX_PREFIXES_                                                      \
    REX_PREFIX, REX_W_PREFIX, REX_R_PREFIX, REX_X_PREFIX, REX_B_PREFIX,        \
        REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX, REX_WRX_PREFIX,           \
        REX_WRB_PREFIX, REX_WXB_PREFIX, REX_WRXB_PREFIX, REX_RX_PREFIX,        \
        REX_RB_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX

#define IMM8_ make_resettable(Catch::Generators::take(1, randomIMM<uint8_t>()))
#define IMM16_                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint16_t>()))
#define IMM32_                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint32_t>()))
#define IMM64_                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint64_t>()))

#define IMPLIED_(val) make_resettable(makeImplied(val))

#define SWITCH_(...)                                                           \
    std::make_unique<InstructionGenerator::ParameterGeneratorSelectorType>(    \
        __VA_ARGS__)
#define IF_(condition, true_, false_)                                          \
    std::make_unique<InstructionGenerator::ParameterGeneratorSelectorType>(    \
        OPT_(condition, true_), OPT_(IF__NOT(condition), false_))
#define IF__NOT(condition)                                                     \
    [](const auto& curParameter, const auto& prefixList,                       \
       const auto& environment) -> bool {                                      \
        return !condition(curParameter, prefixList, environment);              \
    }
#define ELSE_(...) __VA_ARGS__
#define OPT_(...)                                                              \
    InstructionGenerator::ParameterGeneratorSelectorType::                     \
        SelectorGeneratorPair {                                                \
        __VA_ARGS__                                                            \
    }

#define CONDITION_(...) __VA_ARGS__
#define ON_NEVER_                                                              \
    CONDITION_([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool { return false; })
#define ON_ALWAYS_                                                             \
    CONDITION_([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool { return true; })

namespace {
auto calculateAddressMode(const auto& curParameter, const auto& prefixList,
                          const auto& environment) {
    auto mode = environment._defaultAdressMode;

    if (curParameter.isAffectedByAddressSize()) {
        bool overridePrefix =
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX);
        if (environment._defaultInstructionMode ==
            X86Environment::X86InstructionMode::LEGACY) {
            if (mode == X86Environment::X86AddressMode::X16 && overridePrefix)
                mode = X86Environment::X86AddressMode::X32;
            else if (mode == X86Environment::X86AddressMode::X32 &&
                     overridePrefix)
                mode = X86Environment::X86AddressMode::X16;
        } else if (environment._defaultInstructionMode ==
                   X86Environment::X86InstructionMode::X64) {
            if (mode == X86Environment::X86AddressMode::X64 && overridePrefix)
                mode = X86Environment::X86AddressMode::X32;
            else if (mode == X86Environment::X86AddressMode::X32 &&
                     overridePrefix)
                mode = X86Environment::X86AddressMode::X64;
        }
    }
    return mode;
}
auto calculateParameterMode(const auto& curParameter, const auto& prefixList,
                            const auto& environment) {
    auto mode = environment._defaultParameterMode;

    if (curParameter.isAffectedByOperandSize()) {
        bool overridePrefix =
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX);
        if (environment._defaultInstructionMode ==
            X86Environment::X86InstructionMode::LEGACY) {
            if (mode == X86Environment::X86ParameterMode::X16 && overridePrefix)
                mode = X86Environment::X86ParameterMode::X32;
            else if (mode == X86Environment::X86ParameterMode::X32 &&
                     overridePrefix)
                mode = X86Environment::X86ParameterMode::X16;
        } else if (environment._defaultInstructionMode ==
                   X86Environment::X86InstructionMode::X64) {
            // The rex prefix will override the operand size override prefix.
            if (std::ranges::count_if(prefixList, [](const auto& prefix) {
                    return ((prefix.value & std::byte{0x48}) ==
                            std::byte{0x48});
                }) != 0) {
                mode = X86Environment::X86ParameterMode::X64;
            } else if (mode == X86Environment::X86ParameterMode::X16 &&
                       overridePrefix)
                mode = X86Environment::X86ParameterMode::X32;
            else if (mode == X86Environment::X86ParameterMode::X32 &&
                     overridePrefix)
                mode = X86Environment::X86ParameterMode::X16;
        }
    }
    return mode;
}
}; // namespace

#define SWITCH_LAMBDA_(func, type, size)                                       \
    CONDITION_([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool {                           \
        return func(curParameter, prefixList, environment) ==                  \
               X86Environment::type::size;                                     \
    })
#define SWITCH_ADDRESS_LAMBDA_(size)                                           \
    SWITCH_LAMBDA_(calculateAddressMode, X86AddressMode, size)
#define SWITCH_PARAMETER_LAMBDA_(size)                                         \
    SWITCH_LAMBDA_(calculateParameterMode, X86ParameterMode, size)

#define ON_X16_ADDRESS_ SWITCH_ADDRESS_LAMBDA_(X16)
#define ON_X32_ADDRESS_ SWITCH_ADDRESS_LAMBDA_(X32)
#define ON_X64_ADDRESS_ SWITCH_ADDRESS_LAMBDA_(X64)

#define ON_X16_PARAMETER_ SWITCH_PARAMETER_LAMBDA_(X16)
#define ON_X32_PARAMETER_ SWITCH_PARAMETER_LAMBDA_(X32)
#define ON_X64_PARAMETER_ SWITCH_PARAMETER_LAMBDA_(X64)

#define IF_X64_DISASSEMBLER_(disassembler, ...)                                \
    [disassembler_env]()                                                       \
        -> std::optional<                                                      \
            Catch::Generators::GeneratorWrapper<Testing::Helpers::prefix_t>> { \
        if (disassembler_env._defaultInstructionMode ==                        \
            X86Environment::X86InstructionMode::X64)                           \
            return concatenate_as<Testing::Helpers::prefix_t>(__VA_ARGS__);    \
        else                                                                   \
            return std::nullopt;                                               \
    }()

#define INSTRUCTION_(...) __VA_ARGS__

#define DECODE_INSTRUCTION_(disassembler, ...)                                 \
    Testing::Helpers::Instruction generated_instruction =                      \
        GENERATE_COPY(generate_instruction(__VA_ARGS__, disassembler##_env));  \
    INFO(fmt::format("{}", disassembler##_env));                               \
    INFO(fmt::format("Prefix list: {{ {} }}",                                  \
                     fmt::join(generated_instruction.getPrefixList(), ", "))); \
    INFO(fmt::format("Bytes: {{ {:#x} }}",                                     \
                     fmt::join(generated_instruction.getBytes(), ", ")));      \
    BidirectionalIterator<std::byte> generated_instruction_iterator{           \
        std::data(generated_instruction.getBytes()),                           \
        static_cast<int64_t>(std::size(generated_instruction.getBytes()))};    \
    std::unique_ptr<Instruction> decoded_instruction =                         \
        disassembler.decodeInstruction(generated_instruction_iterator);        \
    REQUIRE(decoded_instruction->toString() ==                                 \
            generated_instruction.getString());

#endif
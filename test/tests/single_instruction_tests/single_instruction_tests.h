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
// using namespace Testing::Helpers;

// using opcode_bytes = std::vector<std::byte>;
// using parameter_bytes = std::vector<std::byte>;

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
//
// parameter_bytes makeImmediateParameterByteData(bool disassemblerIsNative,
//                                               imm immVal) {
//    return parameter_bytes{immToBytes(immVal, disassemblerIsNative)};
//}

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
//
// template <typename T>
// using ParameterModeSwitchOption =
//    std::pair<X86Environment::X86ParameterMode, T>;
//
// namespace {
// template <typename T>
// ParameterModeSwitchOption<T>
// toParameterModeSwitchOption(X86Environment::X86ParameterMode mode, T val) {
//    return {mode, val};
//};
// template <typename T, typename... Ts>
// std::vector<T> toParameterModeSwitchVector(T arg1, Ts... args) {
//    std::vector<T> tmp{{arg1, args...}};
//    return tmp;
//};
//
// template <typename T>
// T parameterModeSwitch(X86Environment environment,
//                      std::vector<ParameterModeSwitchOption<T>> vals) {
//    auto found = std::ranges::find_if(vals, [&](const auto& cur) {
//        return cur.first == environment._defaultParameterMode;
//    });
//    if (found != std::ranges::end(vals))
//        return (*found).second;
//    else
//        return T{};
//}
//} // namespace
//
//#define PARAMETER_MODE_SWITCH(disassembler, ...) \
//    parameterModeSwitch(disassembler##_env, \
//                        toParameterModeSwitchVector(__VA_ARGS__))
//
//#define ON_X16(...) \
//    toParameterModeSwitchOption(PARAMETER_MODE_X16, \
//                                std::make_tuple(__VA_ARGS__))
//#define ON_X32(...) \
//    toParameterModeSwitchOption(PARAMETER_MODE_X32, \
//                                std::make_tuple(__VA_ARGS__))
//#define ON_X64(...) \
//    toParameterModeSwitchOption(PARAMETER_MODE_X64, \
//                                std::make_tuple(__VA_ARGS__))
//
//#define DECODE_INSTRUCTION(disassembler, name, ...) \
//    MAKE_BYTE_STREAM(byteStream, __VA_ARGS__); \
//    std::unique_ptr<Instruction> name = \
//        disassembler.decodeInstruction(byteStream)
//
// using instruction_bytes = std::vector<std::byte>;

// struct _empty_parameter {};
// using parameter = std::variant<_empty_parameter, imm>;

// struct parameter
using parameter_generator =
    std::unique_ptr<ResettableGenerator<Testing::Helpers::Parameter>>;
// GeneratorSelector<X86Environment, parameter>;

namespace {
//
// std::vector<std::byte> getParameterBytes(const imm& val,
//                                         bool isDisassemblerNativeEndian) {
//    return immToBytes(val, isDisassemblerNativeEndian);
//}
// std::vector<std::byte> getParameterBytes(const _empty_parameter& val,
//                                         bool isDisassemblerNativeEndian) {
//    throw std::logic_error("Attempt to get the bytes of an empty parameter");
//}

} // namespace

// using parameter_generator_type =
//     GeneratorSelector<Parameter, parameter_info, X86Environment>;
// using parameter_generator_selector =
// std::unique_ptr<parameter_generator_type>; using ParameterOrSelector =
//     std::variant<parameter_generator, parameter_generator_selector>;

#define _PREFIXES(...)                                                         \
    Catch::Generators::chunk(                                                  \
        1, concatenate_as<std::optional<Testing::Helpers::prefix_t>>(          \
               __VA_ARGS__))

#define _NO_PREFIX                                                             \
    std::optional<Testing::Helpers::prefix_t> { std::nullopt }

#define _LOCK_PREFIXES                                                         \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(LOCK_PREFIX)
#define _SEGMENT_OVERRIDE_PREFIXES                                             \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        CS_SEGMENT_OVERRIDE_PREFIX, SS_SEGMENT_OVERRIDE_PREFIX,                \
        DS_SEGMENT_OVERRIDE_PREFIX, ES_SEGMENT_OVERRIDE_PREFIX,                \
        FS_SEGMENT_OVERRIDE_PREFIX, GS_SEGMENT_OVERRIDE_PREFIX)
#define _BRANCH_PREFIXES                                                       \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        BRANCH_NOT_TAKEN_PREFIX, BRANCH_TAKEN_PREFIX)
#define _STRING_PREFIXES                                                       \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(REPNZ_PREFIX,    \
                                                              REP_PREFIX)

#define _ADDRESS_SIZE_PREFIXES                                                 \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        ADDRESS_SIZE_OVERRIDE_PREFIX)
#define _OPERAND_SIZE_PREFIXES                                                 \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        OPERAND_SIZE_OVERRIDE_PREFIX)

#define _ADDRESS_PREFIXES                                                      \
    concatinate(                                                               \
        Catch::Generators::as<std::optional<Testing::Helpers::prefix_t>>{},    \
        _ADDRESS_SIZE_PREFIXES, _SEGMENT_OVERRIDE_PREFIXES)
#define _OPERAND_PREFIXES                                                      \
    concatinate(                                                               \
        Catch::Generators::as<std::optional<Testing::Helpers::prefix_t>>{},    \
        _OPERAND_SIZE_PREFIXES)

#define _ALL_RAW_PREFIXES                                                      \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        _LOCK_PREFIXES, _SEGMENT_OVERRIDE_PREFIXES, _BRANCH_PREFIXES,          \
        _STRING_PREFIXES, _ADDRESS_SIZE_PREFIXES, _OPERAND_SIZE_PREFIXES)

#define _ALL_REX_W_PREFIXES                                                    \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        REX_W_PREFIX, REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX,             \
        REX_WRX_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX, REX_WRXB_PREFIX)
#define _ALL_REX_R_PREFIXES                                                    \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        REX_R_PREFIX, REX_WR_PREFIX, REX_WRX_PREFIX, REX_WRB_PREFIX,           \
        REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX)
#define _ALL_REX_X_PREFIXES                                                    \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        REX_X_PREFIX, REX_WX_PREFIX, REX_WRX_PREFIX, REX_WXB_PREFIX,           \
        REX_WRXB_PREFIX, REX_RX_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX)
#define _ALL_REX_B_PREFIXES                                                    \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        REX_B_PREFIX, REX_WB_PREFIX, REX_WRB_PREFIX, REX_WXB_PREFIX,           \
        REX_WRXB_PREFIX, REX_RB_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX)

#define _ALL_REX_PREFIXES                                                      \
    concatenate_as<std::optional<Testing::Helpers::prefix_t>>(                 \
        REX_PREFIX, REX_W_PREFIX, REX_R_PREFIX, REX_X_PREFIX, REX_B_PREFIX,    \
        REX_WR_PREFIX, REX_WX_PREFIX, REX_WB_PREFIX, REX_WRX_PREFIX,           \
        REX_WRB_PREFIX, REX_WXB_PREFIX, REX_WRXB_PREFIX, REX_RX_PREFIX,        \
        REX_RB_PREFIX, REX_RXB_PREFIX, REX_XB_PREFIX)

#define _IMM8 make_resettable(Catch::Generators::take(1, randomIMM<uint8_t>()))
#define _IMM16                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint16_t>()))
#define _IMM32                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint32_t>()))
#define _IMM64                                                                 \
    make_resettable(Catch::Generators::take(1, randomIMM<uint64_t>()))

#define _IMPLIED(val) make_resettable(makeImplied(val))

#define _SWITCH(...)                                                           \
    std::make_unique<InstructionGenerator::ParameterGeneratorSelectorType>(    \
        __VA_ARGS__)
#define _OPT(...)                                                              \
    InstructionGenerator::ParameterGeneratorSelectorType::                     \
        SelectorGeneratorPair {                                                \
        __VA_ARGS__                                                            \
    }

#define _CONDITION(...)                                                        \
    __VA_ARGS__ /*[](const auto& environment) -> bool { __VA_ARGS__; }*/
#define _ON_NEVER                                                              \
    _CONDITION([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool { return false; })
#define _ON_ALWAYS                                                             \
    _CONDITION([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool { return true; })
#define _ON_X16                                                                \
    _CONDITION([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool {                           \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X16 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X16 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X32 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X32 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        return false;                                                          \
    })

#define _ON_X32                                                                \
    _CONDITION([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool {                           \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X16 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X16 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X32 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X32 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X64 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X64 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) != 0) \
            return true;                                                       \
        return false;                                                          \
    })
#define _ON_X64                                                                \
    _CONDITION([](const auto& curParameter, const auto& prefixList,            \
                  const auto& environment) -> bool {                           \
        if (environment._defaultAdressMode ==                                  \
                X86Environment::X86AddressMode::X64 &&                         \
            curParameter.isAffectedByAddressSize() &&                          \
            std::ranges::count(prefixList, ADDRESS_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultParameterMode ==                               \
                X86Environment::X86ParameterMode::X64 &&                       \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count(prefixList, OPERAND_SIZE_OVERRIDE_PREFIX) == 0) \
            return true;                                                       \
        if (environment._defaultInstructionMode ==                             \
                X86Environment::X86InstructionMode::X64 &&                     \
            curParameter.isAffectedByOperandSize() &&                          \
            std::ranges::count_if(prefixList, [](const auto& prefix) {         \
                return prefix.has_value() &&                                   \
                       ((prefix.value().value & std::byte{0x48}) ==            \
                        std::byte{0x48});                                      \
            }) != 0)                                                           \
            return true;                                                       \
        return false;                                                          \
    })

#define _IF_X64_DISASSEMBLER(disassembler, ...)                                \
    [disassembler_env]() {                                                     \
        if (disassembler_env._defaultInstructionMode ==                        \
            X86Environment::X86InstructionMode::X64)                           \
            return __VA_ARGS__;                                                \
        else                                                                   \
            return concatenate_as<std::optional<Testing::Helpers::prefix_t>>(  \
                _NO_PREFIX);                                                   \
    }()

#define _INSTRUCTION(...) __VA_ARGS__

#define _DECODE_INSTRUCTION(disassembler, ...)                                 \
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
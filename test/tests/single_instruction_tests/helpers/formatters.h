#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_FORMATTERS_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_FORMATTERS_HELPERS_H

#include "parameter.hpp"
#include "prefix.h"
#include <architecture/x86/x86Environment.h>
#include <fmt/format.h>
#include <optional>
//
// template <typename CharT>
// struct fmt::formatter<Testing::Helpers::Parameter, CharT>
//    : public fmt::formatter<basic_string_view<CharT>> {
//    template <typename FormatContext>
//    auto format(const Testing::Helpers::Parameter& op, FormatContext& fc) {
//        return fmt::formatter<basic_string_view<CharT>>::format(op.toString(),
//                                                                fc);
//    }
//};
template <typename CharT>
struct fmt::formatter<X86Environment, CharT>
    : public fmt::formatter<basic_string_view<CharT>> {
    template <typename FormatContext>
    auto format(const X86Environment& env, FormatContext& fc) {
        return fmt::format_to(
            fc.out(),
            "X86Environment {{\n\tInstruction Mode: {}\n\tOperand Mode: "
            "{}\n\tAddress Mode: {}\n\tEndianness: {} \n}}",
            getInstructionMode(env), getOperandMode(env), getAddressMode(env),
            getEndianness(env));
    }

  private:
    auto getInstructionMode(const X86Environment& env) {
        switch (env._defaultInstructionMode) {
        case (X86Environment::X86InstructionMode::LEGACY):
            return "LEGACY";
        case (X86Environment::X86InstructionMode::X64):
            return "X64";
        default:
            return "UNKNOWN";
        }
    }
    auto getOperandMode(const X86Environment& env) {
        switch (env._defaultParameterMode) {
        case (X86Environment::X86ParameterMode::X16):
            return "X16";
        case (X86Environment::X86ParameterMode::X32):
            return "X32";
        case (X86Environment::X86ParameterMode::X64):
            return "X64";
        default:
            return "UNKNOWN";
        }
    }
    auto getAddressMode(const X86Environment& env) {
        switch (env._defaultAdressMode) {
        case (X86Environment::X86AddressMode::X16):
            return "X16";
        case (X86Environment::X86AddressMode::X32):
            return "X32";
        case (X86Environment::X86AddressMode::X64):
            return "X64";
        default:
            return "UNKNOWN";
        }
    }
    auto getEndianness(const X86Environment& env) {
        switch (env._endianness) {
        case (std::endian::little):
            return "LITTLE";
        case (std::endian::big):
            return "BIG";
        default:
            return "UNKNOWN";
        }
    }
};

template <typename T, typename CharT>
struct fmt::formatter<std::optional<T>, CharT>
    : public fmt::formatter<basic_string_view<CharT>> {
    template <typename FormatContext>
    auto format(const std::optional<T>& opt, FormatContext& fc) {
        if (opt)
            return fmt::format_to(fc.out(), "{}", opt.value());
        else
            return fmt::formatter<basic_string_view<CharT>>::format("nullopt",
                                                                    fc);
    }
};

template <typename CharT>
struct fmt::formatter<Testing::Helpers::prefix_t, CharT>
    : public fmt::formatter<basic_string_view<CharT>> {
    template <typename FormatContext>
    auto format(const Testing::Helpers::prefix_t& val, FormatContext& fc) {
        return fmt::formatter<basic_string_view<CharT>>::format(val.name, fc);
    }
};
#endif
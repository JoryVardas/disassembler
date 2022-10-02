#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_IMM_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_IMM_HELPERS_H

#include <cstddef>
#include <fmt/format.h>
#include <string>
#include <variant>
#include <vector>

#include "endian.hpp"
#include "parameter_info.hpp"
#include "prefix.h"

namespace Testing::Helpers {

using IMM8 = uint8_t;
using IMM16 = uint16_t;
using IMM32 = uint32_t;
using IMM64 = uint64_t;

struct IMMParameter : public ParameterType {
    explicit IMMParameter(IMM8 val) { value = val; }
    explicit IMMParameter(IMM16 val) { value = val; }
    explicit IMMParameter(IMM32 val) { value = val; }
    explicit IMMParameter(IMM64 val) { value = val; }
    IMMParameter() = delete;
    IMMParameter(const IMMParameter&) = default;
    IMMParameter(IMMParameter&&) = default;
    ~IMMParameter() = default;

    std::string toString(std::vector<prefix_t>) const override {
        return std::visit(
            [](const auto& val) { return fmt::format("{:#x}", val); }, value);
    }
    std::vector<std::byte>
    toByteVector(std::endian outputEndianness) const override {
        return std::visit(
            [&](const auto& arg) {
                using IMM_TYPE = std::decay_t<decltype(arg)>;
                if (outputEndianness == std::endian::big)
                    return immToBytesHelper<IMM_TYPE>(toBigEndian(arg));
                return immToBytesHelper<IMM_TYPE>(toLittleEndian(arg));
            },
            value);
    }
    ParameterRequires getRequires() const override {
        return ParameterRequires::IMMEDIATE;
    }

    std::byte getModRM() const override { return std::byte{0x00}; }

    IMMParameter& operator=(const IMMParameter&) = default;
    IMMParameter& operator=(IMMParameter&&) = default;

  private:
    std::variant<IMM8, IMM16, IMM32, IMM64> value;

    template <typename IMM_TYPE, std::size_t IMM_SIZE = sizeof(IMM_TYPE)>
    std::vector<std::byte> immToBytesHelper(IMM_TYPE val) const {
        union U {
            IMM_TYPE value;
            std::array<std::uint8_t, IMM_SIZE> bytes;
        } src;

        src.value = val;
        std::vector<std::byte> ret;
        ret.reserve(IMM_SIZE);
        std::transform(src.bytes.begin(), src.bytes.end(),
                       std::back_inserter(ret),
                       [](const std::uint8_t& val) { return std::byte{val}; });
        return ret;
    }
};

} // namespace Testing::Helpers
#endif
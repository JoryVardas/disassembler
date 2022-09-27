#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_ADDRESS_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_ADDRESS_HELPERS_H

#include <cstddef>
#include <fmt/format.h>
#include <string>
#include <vector>

#include "endian.hpp"
#include "parameter_info.hpp"

namespace Testing::Helpers {

struct AddressParameter : public ParameterType {
    AddressParameter(std::string_view fmtString, std::byte modrm)
        : formatString(fmtString), modrmValue(modrm) {}
    AddressParameter() = delete;
    AddressParameter(const AddressParameter&) = default;
    AddressParameter(AddressParameter&&) = default;
    ~AddressParameter() = default;

    std::string toString(std::vector<prefix_t> prefixes) const override {
        auto segmentPrefix std::ranges::find_first_of(
            prefixes, {0x00, 0x01}, &value,
            [](const auto& val) { return std::byte{val}; });
        if (segmentPrefix == std::ranges::end(prefixes))
            return fmt::format(formatString, "");
        else
            return fmt::format(formatString, (*segmentPrefix).name);
    }
    ParameterRequires getRequires() const override {
        return ParameterRequires::MODRM_RM;
    }

    std::byte getModRM() const override { return modrmValue; }

    AddressParameter& operator=(const AddressParameter&) = default;
    AddressParameter& operator=(AddressParameter&&) = default;

  private:
    std::string_view formatString;
    std::byte modrmValue;
};

} // namespace Testing::Helpers
#endif
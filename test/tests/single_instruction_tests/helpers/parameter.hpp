#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PARAMETER_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PARAMETER_HPP

#include <fmt/format.h>
#include <string>
#include <variant>

#include "imm.hpp"
#include "implied.hpp"
#include "parameter_info.hpp"
#include "prefix.h"

namespace Testing::Helpers {
struct Parameter {
    Parameter(const IMMParameter& val)
        : parameter(val), affectedByOperandSize(true) {}
    Parameter(const ImpliedParameter& val)
        : parameter(val), affectedByOperandSize(true) {}
    Parameter() = delete;
    Parameter(const Parameter&) = default;
    Parameter(Parameter&&) = default;
    ~Parameter() = default;

    bool isAffectedByOperandSize() const { return affectedByOperandSize; }
    bool isAffectedByAddressSize() const { return affectedByAddressSize; }
    auto& value() { return parameter; }
    std::string toString(std::vector<prefix_t> prefixes) const {
        return std::visit(
            [&prefixes](const auto& arg) { return arg.toString(prefixes); },
            parameter);
    }
    std::vector<std::byte> toByteVector(std::endian outputEndianness) const {
        return std::visit(
            [outputEndianness](const auto& val) {
                return val.toByteVector(outputEndianness);
            },
            parameter);
    }
    ParameterRequires getRequires() const {
        return std::visit([](const auto& val) { return val.getRequires(); },
                          parameter);
    }

    Parameter& operator=(const Parameter&) = default;
    Parameter& operator=(Parameter&&) = default;

  private:
    std::variant<IMMParameter, ImpliedParameter> parameter;
    bool affectedByOperandSize = false;
    bool affectedByAddressSize = false;
};
} // namespace Testing::Helpers

#endif

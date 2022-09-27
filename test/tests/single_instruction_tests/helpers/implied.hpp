#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_IMPLIED_HELPERS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_IMPLIED_HELPERS_H

#include <cstddef>
#include <fmt/format.h>
#include <string_view>

#include "endian.hpp"
#include "parameter_info.hpp"

namespace Testing::Helpers {

struct ImpliedParameter {
    explicit ImpliedParameter(std::string_view val) { value = val; }
    ImpliedParameter() = delete;
    ImpliedParameter(const ImpliedParameter&) = default;
    ImpliedParameter(ImpliedParameter&&) = default;
    ~ImpliedParameter() = default;

    std::string toString(std::vector<prefix_t>) const {
        return std::string{value};
    }
    std::vector<std::byte> toByteVector(std::endian outputEndianness) const {
        return {};
    }
    ParameterRequires getRequires() const { return ParameterRequires::NONE; }

    ImpliedParameter& operator=(const ImpliedParameter&) = default;
    ImpliedParameter& operator=(ImpliedParameter&&) = default;

  private:
    std::string_view value;
};

} // namespace Testing::Helpers
#endif
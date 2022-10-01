#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PARAMETER_INFO_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_PARAMETER_INFO_HPP

#include "prefix.h"

namespace Testing::Helpers {
enum class ParameterRequires { NONE, IMMEDIATE, MODRM_R, MODRM_RM };

class ParameterType {
  public:
    virtual ParameterRequires getRequires() const = 0;
    virtual std::byte getModRM() const = 0;
    virtual std::vector<std::byte> toByteVector(
        std::endian outputEndianness) const = 0;
    virtual std::string toString(std::vector<prefix_t> prefixes) const = 0;
};
} // namespace Testing::Helpers

#endif

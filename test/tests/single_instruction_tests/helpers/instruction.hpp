#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_INSTRUCTION_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_INSTRUCTION_HPP

#include "formatters.h"
#include "parameter.hpp"
#include "prefix.h"

namespace Testing::Helpers {

using opcode_bytes = std::vector<std::byte>;
using instruction_bytes = std::vector<std::byte>;
struct Instruction {
    Instruction() = default;
    Instruction(const Instruction&) = default;
    Instruction(Instruction&&) = default;
    ~Instruction() = default;

    Instruction(std::string_view name,
                std::vector<std::optional<prefix_t>> prefixes,
                opcode_bytes& opcode)
        : _prefixList(prefixes) {
        _str = fmt::format("{}", name);
        for (const auto prefix : prefixes) {
            if (prefix)
                _bytes.push_back(prefix.value().value);
        }
        std::ranges::copy(opcode, std::back_inserter(_bytes));
    }
    Instruction(std::string_view name,
                std::vector<std::optional<prefix_t>> prefixes,
                opcode_bytes& opcode, Parameter op1,
                std::endian outputEndianness)
        : _prefixList(prefixes) {
        _str = fmt::format("{} {}", name, op1.toString(prefixes));
        for (const auto prefix : prefixes) {
            if (prefix)
                _bytes.push_back(prefix.value().value);
        }
        std::ranges::copy(opcode, std::back_inserter(_bytes));
        std::ranges::copy(getAllParameterBytes(outputEndianness, op1),
                          std::back_inserter(_bytes));
    }
    Instruction(std::string_view name,
                std::vector<std::optional<prefix_t>> prefixes,
                opcode_bytes& opcode, Parameter op1, Parameter op2,
                std::endian outputEndianness)
        : _prefixList(prefixes) {
        _str = fmt::format("{} {}, {}", name, op1.toString(prefixes),
                           op2.toString(prefixes));
        for (const auto& prefix : prefixes) {
            if (prefix)
                _bytes.push_back(prefix.value().value);
        }
        std::ranges::copy(opcode, std::back_inserter(_bytes));
        std::ranges::copy(getAllParameterBytes(outputEndianness, op1, op2),
                          std::back_inserter(_bytes));
    }
    Instruction(std::string_view name,
                std::vector<std::optional<prefix_t>> prefixes,
                opcode_bytes& opcode, Parameter op1, Parameter op2,
                Parameter op3, std::endian outputEndianness)
        : _prefixList(prefixes) {
        _str = fmt::format("{} {}, {}, {}", name, op1.toString(prefixes),
                           op2.toString(prefixes), op3.toString(prefixes));
        for (const auto& prefix : prefixes) {
            if (prefix)
                _bytes.push_back(prefix.value().value);
            std::ranges::copy(
                getAllParameterBytes(outputEndianness, op1, op2, op3),
                std::back_inserter(_bytes));
        }
        std::ranges::copy(opcode, std::back_inserter(_bytes));
        std::ranges::copy(getAllParameterBytes(outputEndianness, op1, op2, op3),
                          std::back_inserter(_bytes));
    }
    Instruction(std::string_view name,
                std::vector<std::optional<prefix_t>> prefixes,
                opcode_bytes& opcode, Parameter op1, Parameter op2,
                Parameter op3, Parameter op4, std::endian outputEndianness)
        : _prefixList(prefixes) {
        _str = fmt::format("{} {}, {}, {}, {}", name, op1.toString(prefixes),
                           op2.toString(prefixes), op3.toString(prefixes),
                           op4.toString(prefixes));
        for (const auto& prefix : prefixes) {
            if (prefix)
                _bytes.push_back(prefix.value().value);
        }
        std::ranges::copy(opcode, std::back_inserter(_bytes));
        std::ranges::copy(
            getAllParameterBytes(outputEndianness, op1, op2, op3, op4),
            std::back_inserter(_bytes));
    }

    std::string_view getString() { return _str; }
    instruction_bytes& getBytes() { return _bytes; }

    Instruction& operator=(const Instruction&) = default;
    Instruction& operator=(Instruction&&) = default;

    std::vector<std::optional<prefix_t>>& getPrefixList() {
        return _prefixList;
    }

  private:
    std::string _str;
    instruction_bytes _bytes;

    std::vector<std::optional<prefix_t>> _prefixList;

    std::vector<std::byte> getAllParameterBytes(
        std::endian outputEndianness, /*bool
                                       * isDisassemblerNativeEndian,*/
        std::optional<Parameter> op1 = std::nullopt,
        std::optional<Parameter> op2 = std::nullopt,
        std::optional<Parameter> op3 = std::nullopt,
        std::optional<Parameter> op4 = std::nullopt) {
        std::vector<std::byte> ret;

        if (op1)
            std::ranges::copy(op1.value().toByteVector(outputEndianness),
                              std::back_inserter(ret));
        if (op2)
            std::ranges::copy(op2.value().toByteVector(outputEndianness),
                              std::back_inserter(ret));
        if (op3)
            std::ranges::copy(op3.value().toByteVector(outputEndianness),
                              std::back_inserter(ret));
        if (op4)
            std::ranges::copy(op4.value().toByteVector(outputEndianness),
                              std::back_inserter(ret));
        return ret;
    }
};
} // namespace Testing::Helpers
#endif

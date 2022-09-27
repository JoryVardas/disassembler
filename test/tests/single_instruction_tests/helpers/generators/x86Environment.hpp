#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_X86ENVIRONMENT_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_X86ENVIRONMENT_HPP

#include <architecture/x86/x86Environment.h>
#include <catch2/generators/catch_generators.hpp>

namespace Testing::Helpers::Generators {
class X86EnvironmentGenerator
    : public Catch::Generators::IGenerator<X86Environment> {

    uint8_t _current = 0;
    X86Environment::X86InstructionMode _mode;

    X86Environment _current_environment;

  public:
    X86EnvironmentGenerator(X86Environment::X86InstructionMode mode) {
        _mode = mode;
        if (mode == X86Environment::X86InstructionMode::X64) {
            _current = 0x08;
            _current_environment._endianness = std::endian::little;
            _current_environment._defaultAdressMode =
                X86Environment::X86AddressMode::X32;
            _current_environment._defaultParameterMode =
                X86Environment::X86ParameterMode::X32;
            _current_environment._defaultInstructionMode =
                X86Environment::X86InstructionMode::X64;
        } else {
            _current = 0x00;
            _current_environment._endianness = std::endian::little;
            _current_environment._defaultAdressMode =
                X86Environment::X86AddressMode::X16;
            _current_environment._defaultParameterMode =
                X86Environment::X86ParameterMode::X16;
            _current_environment._defaultInstructionMode =
                X86Environment::X86InstructionMode::LEGACY;
        }
    }

    X86EnvironmentGenerator() = delete;
    X86EnvironmentGenerator(const X86EnvironmentGenerator&) = delete;
    X86EnvironmentGenerator(X86EnvironmentGenerator&&) = default;
    ~X86EnvironmentGenerator() = default;
    X86EnvironmentGenerator& operator=(const X86EnvironmentGenerator&) = delete;
    X86EnvironmentGenerator& operator=(X86EnvironmentGenerator&&) = default;

    const X86Environment& get() const override { return _current_environment; }
    bool next() override {

        _current++;

        if (_mode == X86Environment::X86InstructionMode::LEGACY) {
            if (_current >= 0x08)
                return false;
        } else {
            if (_current >= 0x10)
                return false;
        }

        if ((static_cast<uint8_t>(_current) & 0x01) >= 1)
            _current_environment._endianness = std::endian::big;
        else
            _current_environment._endianness = std::endian::little;
        if ((static_cast<uint8_t>(_current) & 0x08) >= 1) {
            _current_environment._defaultInstructionMode =
                X86Environment::X86InstructionMode::X64;
            if ((static_cast<uint8_t>(_current) & 0x02) >= 1)
                _current_environment._defaultAdressMode =
                    X86Environment::X86AddressMode::X64;
            else
                _current_environment._defaultAdressMode =
                    X86Environment::X86AddressMode::X32;
            if ((static_cast<uint8_t>(_current) & 0x04) >= 1)
                _current_environment._defaultParameterMode =
                    X86Environment::X86ParameterMode::X64;
            else
                _current_environment._defaultParameterMode =
                    X86Environment::X86ParameterMode::X32;
        } else {
            _current_environment._defaultInstructionMode =
                X86Environment::X86InstructionMode::LEGACY;
            if ((static_cast<uint8_t>(_current) & 0x02) >= 1)
                _current_environment._defaultAdressMode =
                    X86Environment::X86AddressMode::X32;
            else
                _current_environment._defaultAdressMode =
                    X86Environment::X86AddressMode::X16;
            if ((static_cast<uint8_t>(_current) & 0x04) >= 1)
                _current_environment._defaultParameterMode =
                    X86Environment::X86ParameterMode::X32;
            else
                _current_environment._defaultParameterMode =
                    X86Environment::X86ParameterMode::X16;
        }
        return true;
    }
};

namespace {
Catch::Generators::GeneratorWrapper<X86Environment>
generateX86Environment(X86Environment::X86InstructionMode mode) {
    return Catch::Generators::GeneratorWrapper<X86Environment>(
        Catch::Detail::make_unique<X86EnvironmentGenerator>(mode));
}
} // namespace
} // namespace Testing::Helpers::Generators

#endif

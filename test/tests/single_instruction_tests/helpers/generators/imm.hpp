#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_IMM_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_IMM_HPP

#include <catch2/generators/catch_generators.hpp>

#include "../imm.hpp"
#include "../parameter.hpp"

namespace Testing::Helpers::Generators {

template <typename T>
class RandomIMMGenerator : public Catch::Generators::IGenerator<Parameter> {
    std::minstd_rand m_rand;
    std::uniform_int_distribution<T> dist;
    Parameter current_number;

  public:
    RandomIMMGenerator()
        : m_rand(std::random_device{}()),
          dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()),
          current_number(IMMParameter{static_cast<T>(0)}) {
        RandomIMMGenerator::next();
    }

    const Parameter& get() const override { return current_number; }
    bool next() override {
        T val = dist(m_rand);

        current_number = Parameter{IMMParameter{val}};

        return true;
    }
};

template <>
class RandomIMMGenerator<uint8_t>
    : public Catch::Generators::IGenerator<Parameter> {
    std::minstd_rand m_rand;
    std::uniform_int_distribution<uint16_t> dist;
    Parameter current_number;

  public:
    RandomIMMGenerator()
        : m_rand(std::random_device{}()), dist(0x00, 0xFF),
          current_number(IMMParameter{static_cast<uint8_t>(0)}) {
        RandomIMMGenerator::next();
    }

    const Parameter& get() const override { return current_number; }
    bool next() override {

        uint8_t val = static_cast<uint8_t>(dist(m_rand));

        current_number = Parameter{IMMParameter{val}};

        return true;
    }
};

namespace {
template <typename T>
Catch::Generators::GeneratorWrapper<Parameter> randomIMM() {
    return Catch::Generators::GeneratorWrapper<Parameter>(
        Catch::Detail::make_unique<RandomIMMGenerator<T>>());
}
} // namespace
} // namespace Testing::Helpers::Generators

#endif

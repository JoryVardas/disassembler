#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_IMPLIED_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_IMPLIED_HPP

#include <catch2/generators/catch_generators.hpp>

#include "../imm.hpp"
#include "../parameter.hpp"

namespace Testing::Helpers::Generators {

namespace {
Catch::Generators::GeneratorWrapper<Parameter>
makeImplied(std::string_view val) {
    return Catch::Generators::value(Parameter{ImpliedParameter{val}});
}
} // namespace
} // namespace Testing::Helpers::Generators

#endif

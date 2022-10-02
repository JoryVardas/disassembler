#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_CONCATENATE_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_CONCATENATE_HPP

#include <catch2/generators/catch_generators.hpp>

#include "../concepts.h"

namespace Testing::Helpers::Generators {

struct not_generator {};
template <typename> struct get_generator_type {
    using type = not_generator;
};

template <typename INNER>
struct get_generator_type<Catch::Generators::GeneratorWrapper<INNER>> {
    using type = INNER;
};
template <typename T>
using get_generator_type_t = typename get_generator_type<T>::type;

namespace {
template <typename... Gs,
          typename FIRST = std::tuple_element_t<0, std::tuple<Gs...>>,
          typename T = std::conditional_t<
              std::is_same_v<get_generator_type_t<FIRST>, not_generator>, FIRST,
              get_generator_type_t<FIRST>>>
Catch::Generators::GeneratorWrapper<T> concatenate(Gs&&... moreGenerators) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<Catch::Generators::Generators<T>>(
            std::forward<Gs>(moreGenerators)...));
};

template <typename U, typename... Gs>
Catch::Generators::GeneratorWrapper<U> concatenate_as(Gs&&... moreGenerators) {
    return Catch::Generators::GeneratorWrapper<U>(
        Catch::Detail::make_unique<Catch::Generators::Generators<U>>(
            std::forward<Gs>(moreGenerators)...));
};
} // namespace
} // namespace Testing::Helpers::Generators

#endif
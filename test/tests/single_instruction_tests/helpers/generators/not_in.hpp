#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_NOT_IN_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_NOT_IN_HPP

#include <algorithm>
#include <catch2/generators/catch_generators.hpp>
#include <ranges>

#include "../concepts.h"

namespace Testing::Helpers::Generators {

template <typename T, container_view Container,
          typename U = typename Container::value_type/*,
          typename ConstIterator = typename Container::const_iterator*/>
requires std::movable<Container> && std::same_as<T, U>
class NotInGenerator : public Catch::Generators::IGenerator<T> {
    Catch::Generators::GeneratorWrapper<T> _generator;
    Container _container;

  public:
    NotInGenerator(Catch::Generators::GeneratorWrapper<T>&& generator,
                   Container&& container)
        : _generator(std::move(generator)), _container(std::move(container)) {
        if (std::ranges::find(_container, _generator.get()) !=
            std::ranges::end(_container)) {
            if (!next())
                Catch::Generators::Detail::throw_generator_exception(
                    "No valid values found in not_in generator");
        }
    }
    NotInGenerator() = delete;
    NotInGenerator(const NotInGenerator&) = delete;
    NotInGenerator(NotInGenerator&&) = default;
    ~NotInGenerator() = default;
    NotInGenerator& operator=(const NotInGenerator&) = delete;
    NotInGenerator& operator=(const NotInGenerator&&) = default;

    const T& get() const override { return _generator.get(); }
    bool next() override {

        bool success = _generator.next();
        if (!success) {
            return false;
        }
        while ((std::ranges::find(_container, _generator.get()) !=
                std::ranges::end(_container)) &&
               (success = _generator.next()) == true)
            ;
        return success;
    }
};
namespace {
template <typename T, container_view Container,
          typename U = typename Container::value_type/*,
          typename ConstIterator = typename Container::const_iterator*/>
requires std::movable<Container> && std::same_as<T, U>
    Catch::Generators::GeneratorWrapper<T>
    not_in(Catch::Generators::GeneratorWrapper<T>&& generator,
           Container&& container) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<NotInGenerator<T, Container>>(
            std::move(generator), std::move(container)));
};
template <typename T>
Catch::Generators::GeneratorWrapper<T>
not_in(Catch::Generators::GeneratorWrapper<T>&& generator,
       Catch::Generators::GeneratorWrapper<T>&& generator2) {
    std::vector<T> tmp;
    do {
        tmp.push_back(generator2.get());
    } while (generator2.next());
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<NotInGenerator<T, std::vector<T>>>(
            std::move(generator), std::move(tmp)));
};
} // namespace
} // namespace Testing::Helpers::Generators
#endif
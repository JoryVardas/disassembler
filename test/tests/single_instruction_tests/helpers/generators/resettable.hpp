#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_RESETTABLE_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_RESETTABLE_HPP

#include <catch2/generators/catch_generators.hpp>
#include <concepts>
#include <memory>

namespace Testing::Helpers::Generators {

template <std::copyable T>
class ResettableGenerator : public Catch::Generators::IGenerator<T> {
    Catch::Generators::GeneratorWrapper<T> _generator;
    using Iterator = typename std::vector<T>::const_iterator;
    std::vector<T> _cache;
    Iterator _cur;
    bool _usingCache = false;

  public:
    ResettableGenerator(Catch::Generators::GeneratorWrapper<T>&& generator)
        : _generator(std::move(generator)) {
        _cache.push_back(_generator.get());
    }
    ResettableGenerator() = delete;
    ResettableGenerator(const ResettableGenerator&) = delete;
    ResettableGenerator(ResettableGenerator&&) = default;
    ~ResettableGenerator() = default;
    ResettableGenerator& operator=(const ResettableGenerator&) = delete;
    ResettableGenerator& operator=(const ResettableGenerator&&) = default;

    const T& get() const override {
        if (_usingCache)
            return *_cur;
        else
            return _generator.get();
    }
    bool next() override {
        if (_usingCache) {
            _cur++;
            return _cur != std::cend(_cache);
        } else {
            if (_generator.next()) {
                _cache.push_back(_generator.get());
                return true;
            } else {
                return false;
            }
        }
    }

    void reset() {
        _cur = std::cbegin(_cache);
        _usingCache = true;
    }
};

namespace {
template <typename T>
std::unique_ptr<ResettableGenerator<T>>
make_resettable(Catch::Generators::GeneratorWrapper<T>&& generator) {
    return std::make_unique<ResettableGenerator<T>>(std::move(generator));
};
} // namespace

} // namespace Testing::Helpers::Generators
#endif
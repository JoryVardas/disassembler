#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_PREFIX_LIST_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_PREFIX_LIST_HPP

#include <algorithm>
#include <catch2/generators/catch_generators.hpp>
#include <concepts>
#include <ranges>

#include "../cartesianProductView.hpp"
#include "../prefix.h"
#include "resettable.hpp"

namespace Testing::Helpers::Generators {
class PrefixListGenerator
    : public Catch::Generators::IGenerator<std::vector<prefix_t>> {
    using optionalPrefix = std::optional<prefix_t>;
    using optionalPrefixVector = std::vector<optionalPrefix>;
    using prefixVector = std::vector<prefix_t>;

    optionalPrefixVector group1Prefixes = {{std::nullopt}};
    optionalPrefixVector group2Prefixes = {{std::nullopt}};
    optionalPrefixVector group3Prefixes = {{std::nullopt}};
    optionalPrefixVector group4Prefixes = {{std::nullopt}};
    optionalPrefixVector extendedPrefixes = {{std::nullopt}};

    CartesianProductView<optionalPrefixVector, optionalPrefixVector,
                         optionalPrefixVector, optionalPrefixVector,
                         optionalPrefixVector>
        productView;
    decltype(productView.begin()) productViewIterator;
    int permutationIndex = 0;
    int permutationIndexWrapValue = 0;
    prefixVector currentValue;

  public:
    template <typename... Ts>
    PrefixListGenerator(Ts&&... prefixes)
        : productView(group1Prefixes, group2Prefixes, group3Prefixes,
                      group4Prefixes, extendedPrefixes),
          productViewIterator(productView.end()) {
        // add each prefix to the generator.
        (addPrefix(prefixes), ...);

        // The initial value for productView was set, but only contains the
        // initial prefix vectors. Now that we have added the prefixes to them
        // we need to reassign the product view.
        productView =
            CartesianProductView{group1Prefixes, group2Prefixes, group3Prefixes,
                                 group4Prefixes, extendedPrefixes};
        productViewIterator = productView.begin();

        // Calculate the permutation wrap value
        if (group1Prefixes.at(0).has_value())
            ++permutationIndexWrapValue;
        if (group2Prefixes.at(0).has_value())
            ++permutationIndexWrapValue;
        if (group3Prefixes.at(0).has_value())
            ++permutationIndexWrapValue;
        if (group4Prefixes.at(0).has_value())
            ++permutationIndexWrapValue;

        PrefixListGenerator::next();
    }

    PrefixListGenerator() = delete;
    PrefixListGenerator(const PrefixListGenerator&) = default;
    PrefixListGenerator(PrefixListGenerator&&) = default;
    ~PrefixListGenerator() = default;
    PrefixListGenerator& operator=(const PrefixListGenerator&) = default;
    PrefixListGenerator& operator=(PrefixListGenerator&&) = default;

    void addPrefix(Catch::Generators::GeneratorWrapper<prefix_t>& generator) {
        // Add all the prefixes generated by the generator to their respective
        // groups
        do {
            addPrefix(generator.get());
        } while (generator.next());
    };
    // This overload is allows an optional generator to be passed, this is
    // useful when the prefix list is conditional on some other value.
    void addPrefix(std::optional<Catch::Generators::GeneratorWrapper<prefix_t>>&
                       optionalGenerator) {
        if (optionalGenerator.has_value())
            addPrefix(optionalGenerator.value());
    }
    void addPrefix(const prefix_t& prefix) {
        // Add the prefix to its respective groups
        switch (prefix.group) {
        case PrefixGroup::Group1:
            if (!group1Prefixes.at(0).has_value())
                group1Prefixes.clear();
            group1Prefixes.push_back(prefix);
            break;
        case PrefixGroup::Group2:
            if (!group2Prefixes.at(0).has_value())
                group2Prefixes.clear();
            group2Prefixes.push_back(prefix);
            break;
        case PrefixGroup::Group3:
            if (!group3Prefixes.at(0).has_value())
                group3Prefixes.clear();
            group3Prefixes.push_back(prefix);
            break;
        case PrefixGroup::Group4:
            if (!group4Prefixes.at(0).has_value())
                group4Prefixes.clear();
            group4Prefixes.push_back(prefix);
            break;
        case PrefixGroup::Extended:
            if (!extendedPrefixes.at(0).has_value())
                extendedPrefixes.clear();
            extendedPrefixes.push_back(prefix);
            break;
        }
    };

    const prefixVector& get() const override { return currentValue; }
    bool next() override {
        if (productViewIterator == productView.end())
            return false;

        auto prefixes = *productViewIterator;
        // add the prefixes to the current prefix list
        currentValue.clear();
        if (auto val = std::get<0>(prefixes); val.has_value())
            currentValue.push_back(val.value());
        if (auto val = std::get<1>(prefixes); val.has_value())
            currentValue.push_back(val.value());
        if (auto val = std::get<2>(prefixes); val.has_value())
            currentValue.push_back(val.value());
        if (auto val = std::get<3>(prefixes); val.has_value())
            currentValue.push_back(val.value());
        // The prefixes from group 1 to 4 can appear in any order, so permute
        // the prefix list.
        std::ranges::rotate(currentValue,
                            currentValue.begin() + permutationIndex);

        // The extended prefixes must always be after groups 1-4 so we add them
        // after the permutation.
        if (auto val = std::get<4>(prefixes); val.has_value())
            currentValue.push_back(val.value());

        permutationIndex++;
        if (permutationIndex == permutationIndexWrapValue) {
            permutationIndex = 0;
            ++productViewIterator;
        }

        return true;
    }
};

namespace {
template <typename... Ts>
Catch::Generators::GeneratorWrapper<std::vector<Testing::Helpers::prefix_t>>
generatePrefixList(Ts&&... prefixes) {
    return Catch::Generators::GeneratorWrapper<
        std::vector<Testing::Helpers::prefix_t>>(
        Catch::Detail::make_unique<PrefixListGenerator>(
            std::forward<Ts>(prefixes)...));
}
} // namespace
} // namespace Testing::Helpers::Generators

#endif
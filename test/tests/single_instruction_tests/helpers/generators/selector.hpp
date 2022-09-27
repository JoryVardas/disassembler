#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_SELECTOR_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_GENERATORS_SELECTOR_HPP

#include <catch2/generators/catch_generators.hpp>
#include <tuple>

#include "../concepts.h"

namespace Testing::Helpers::Generators {

template <typename GeneratorType, typename... SelectorTypes>
class GeneratorSelector {
  public:
    using Type =
        std::remove_cvref_t<decltype(std::declval<GeneratorType>().get())>;
    using Generator = std::unique_ptr<GeneratorType>;
    using SelectorFunction =
        std::function<bool(const Type&, const SelectorTypes&...)>;
    using SelectorGeneratorInfo = std::tuple<bool, SelectorFunction, Generator>;
    using SelectorGeneratorPair = std::pair<SelectorFunction, Generator>;
    using GeneratorIndex = std::size_t;

    template <typename... InputPair>
    requires all_same<SelectorGeneratorPair, InputPair...>
    GeneratorSelector(InputPair... pairs) {
        (selectorGeneratorInfo.emplace_back(true, std::move(pairs.first),
                                            std::move(pairs.second)),
         ...);
    }

    GeneratorSelector() = delete;
    GeneratorSelector(const GeneratorSelector&) = delete;
    GeneratorSelector(GeneratorSelector&&) = default;
    ~GeneratorSelector() = default;
    GeneratorSelector& operator=(const GeneratorSelector&) = delete;
    GeneratorSelector& operator=(const GeneratorSelector&&) = default;

    const Type& get(const SelectorTypes&... args) const {
        auto selectedIndex = select(args...);
        if (selectedIndex == end())
            throw std::logic_error(
                "No generator was selected during call to get");
        // return std::get<2>(selectorGeneratorInfo.at(index))->get();
        return (std::get<2>(selectorGeneratorInfo.at(selectedIndex)))->get();
    }
    bool next(const SelectorTypes&... args) {
        auto selectedIndex = select(args...);
        if (selectedIndex == end())
            return false;
        SelectorGeneratorInfo& info = selectorGeneratorInfo.at(selectedIndex);
        std::get<0>(info) = std::get<2>(info)->next();
        return select(args...) != end();
    }

    void
    reset() requires std::is_same_v<GeneratorType, ResettableGenerator<Type>> {
        std::ranges::for_each(selectorGeneratorInfo, [](auto& cur) {
            std::get<0>(cur) = true;
            std::get<2>(cur)->reset();
        });
    }
    void reset() {}

  private:
    std::vector<SelectorGeneratorInfo> selectorGeneratorInfo;
    GeneratorIndex select(const SelectorTypes&... args) const {
        auto iter =
            std::ranges::find_if(selectorGeneratorInfo, [&](const auto& cur) {
                if (!std::get<0>(cur))
                    return false;
                else
                    return (std::get<1>(cur))(std::get<2>(cur)->get(), args...);
            });
        if (iter == std::ranges::end(selectorGeneratorInfo))
            return end();

        // return *((*iter).second);
        return std::ranges::distance(std::ranges::begin(selectorGeneratorInfo),
                                     iter);
    }

    GeneratorIndex end() const { return std::size(selectorGeneratorInfo); }
}; // namespace Testing::Helpers::Generators

} // namespace Testing::Helpers::Generators
#endif

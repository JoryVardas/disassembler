#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_CONCEPTS_H
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_CONCEPTS_H

#include <concepts>
#include <iterator>

namespace Testing::Helpers {
template <typename Container, typename T = typename Container::value_type,
          typename ConstIterator = typename Container::const_iterator,
          typename SizeType = typename Container::size_type,
          typename ConstReferenceType = typename Container::const_reference>
concept container_view =
    requires() {
        typename T;
        typename ConstIterator;
    } && std::forward_iterator<ConstIterator> &&
    requires(Container a) {
        { a.cbegin() } -> std::same_as<ConstIterator>;
        { a.cend() } -> std::same_as<ConstIterator>;
        { a.size() } -> std::same_as<SizeType>;
    } && requires(ConstIterator a) {
             { *a } -> std::same_as<ConstReferenceType>;
         };

template <typename... Ts>
concept all_same = std::conjunction_v<
    std::is_same<std::tuple_element_t<0, std::tuple<Ts...>>, Ts>...>;

} // namespace Testing::Helpers
#endif
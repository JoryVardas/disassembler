#include <type_traits>

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

template <typename... Ts> struct TypeCollection {};

template <typename... Ts> struct is_in {};
template <typename T> struct is_in<T> : std::false_type {};
template <typename T, typename... Ts>
struct is_in<T, TypeCollection<Ts...>>
    : std::disjunction<std::is_same<T, Ts>...> {};

template <typename... Ts> struct any_in {};
template <typename... TypesToCheck, typename... TypesToCheckAgainst>
struct any_in<TypeCollection<TypesToCheck...>,
              TypeCollection<TypesToCheckAgainst...>>
    : std::disjunction<
          is_in<TypesToCheck, TypeCollection<TypesToCheckAgainst...>>...> {};

template <typename... Ts> struct all_in {};
template <typename... TypesToCheck, typename... TypesToCheckAgainst>
struct all_in<TypeCollection<TypesToCheck...>,
              TypeCollection<TypesToCheckAgainst...>>
    : std::conjunction<
          is_in<TypesToCheck, TypeCollection<TypesToCheckAgainst...>>...> {};

template <typename... Ts> struct change_container;
template <template <typename...> typename NewContainer,
          template <typename> typename OldContainer, typename... Ts>
struct change_container<NewContainer<>, OldContainer<Ts...>> {
    using _type = NewContainer<Ts...>;
};

#endif
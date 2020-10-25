#include <type_traits>

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

template <typename ...Ts>
struct Collection{};

template <typename ...Ts>
struct is_in{};
template <typename T>
struct is_in<T> 
    : std::false_type
{};
template <typename T, typename ...Ts>
struct is_in<T, Collection<Ts...>> 
    : std::disjunction<std::is_same<T, Ts>...>
{};

template <typename ...Ts>
struct any_in{};
template <typename ...TypesToCheck, typename ...TypesToCheckAgainst>
struct any_in<Collection<TypesToCheck...>, Collection<TypesToCheckAgainst...>> 
    : std::disjunction<is_in<TypesToCheck, Collection<TypesToCheckAgainst...>>...>
{};

template <typename ...Ts>
struct all_in{};
template <typename ...TypesToCheck, typename ...TypesToCheckAgainst>
struct all_in<Collection<TypesToCheck...>, Collection<TypesToCheckAgainst...>> 
    : std::conjunction<is_in<TypesToCheck, Collection<TypesToCheckAgainst...>>...>
{};

#endif
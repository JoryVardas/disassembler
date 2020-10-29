#include <variant>
#include "typeTraits.h"

#ifndef VARIANT_H
#define VARIANT_H

template<typename ...Ty>
struct _variant_join_helper;
template<typename ...A, typename ...B>
struct _variant_join_helper<TypeCollection<A...>, TypeCollection<B...>>{
    using _type = TypeCollection<A..., B...>;
};

template <typename ...Ty>
struct _variant_join;
template <typename NonVariantType>
struct _variant_join<NonVariantType>{
    using _type = TypeCollection<NonVariantType>;
};
template <typename ...VariantTypes>
struct _variant_join<std::variant<VariantTypes...>>{
    using _type = TypeCollection<VariantTypes...>;
};
template <typename FirstVariant, typename ...RemainingVariants>
struct _variant_join<FirstVariant, RemainingVariants...>{
    using _firstVariantType = typename _variant_join<FirstVariant>::_type;
    using _remainingVariantType = typename _variant_join<RemainingVariants...>::_type;
    using _type = typename _variant_join_helper<_firstVariantType, _remainingVariantType>::_type;
};

template<typename ...Variants>
using variant_join = typename change_container<std::variant<>, typename _variant_join<Variants...>::_type>::_type;




template<typename ...Ty>
struct _holds_any_alternative_helper;
template<typename Variant, typename ...VariantTypes, typename ...Alternatives>
struct _holds_any_alternative_helper<Variant, std::variant<VariantTypes...>, std::variant<Alternatives...>>{
static bool _holds(Variant& var){
        static_assert(all_in<TypeCollection<Alternatives...>, TypeCollection<VariantTypes...>>::value,
                      "Can't check if a variant holds an alternative if that alternative is not one of the alternatives defined for the variant, or if the variant is defined to have multiple alternatives of the same type.");

        return (std::holds_alternative<Alternatives>(var) || ...);
    }
};

template<typename ...Alternatives, typename Variant>
bool holds_any_alternative(Variant& var){
    return _holds_any_alternative_helper<Variant, std::remove_const_t<Variant>, variant_join<Alternatives...>>::_holds(var);
}


//make_visitor is modified from https://bitbashing.io/std-visit.html by Matt Kline
template <typename... FuncTypes>
struct _make_visitor_helper;

template <typename FuncType>
struct _make_visitor_helper<FuncType> : FuncType{
    _make_visitor_helper(FuncType func) : FuncType(func) {}

    using FuncType::operator();
};

template <typename FuncType, typename... RestFuncTypes>
struct _make_visitor_helper<FuncType, RestFuncTypes...> : FuncType, _make_visitor_helper<RestFuncTypes...>{
    _make_visitor_helper(FuncType func, RestFuncTypes... rest) : FuncType(func), _make_visitor_helper<RestFuncTypes...>(rest...) {}

    using FuncType::operator();
    using _make_visitor_helper<RestFuncTypes...>::operator();
};

template <typename... FuncTypes>
auto make_visitor(FuncTypes... funcs){
    return _make_visitor_helper<FuncTypes...>(funcs...);
}

#endif
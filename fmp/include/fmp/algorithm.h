#include "core.h"
#include "base.h"

namespace fmp
{
    template<typename L, long long start, long long end, long long step = 1>
    struct range
    {
        using type = typename order<L, core::make_index_seq<start, end, step>>::type;
    };

    //(L<T0, T1, ..., Tn> -> L<T0, T1, ..., Tcount>)
    template<typename L, long long count>
    struct take
    {
        using type = typename range<L, 0, count>::type;
    };

    template<typename L, long long count>
    using take_t = typename take<L, count>::type;

    template<typename L, long long count>
    struct drop
    {
        using type = typename range<L, count, size_v<L>>::type;
    };

    //(LC, T, count) -> L<T, T, ..., T>)
    template<typename T, long long count, template<typename...>typename LC = type_list>
    struct repeat
    {
        using type = typename order<LC<T>, core::index_repeat_seq<0, count>>::type;
    };

    template<typename T, long long count, template<typename...>typename LC = type_list>
    using repeat_t = typename repeat< T, count, LC>::type;

    template<typename L, typename I, template<typename, typename>typename F>
    struct fold;

    template<template<typename...>typename LC, typename T, typename...Ts, typename I, template<typename, typename>typename F>
        requires (... && requires{ typename F<I, Ts>::type; })
    struct fold<LC<T, Ts...>, I, F>
    {
        using type = typename fold<LC<Ts...>, typename F<I, T>::type, F>::type;
    };

    template<template<typename...>typename LC, typename T, typename...Ts, typename I, template<typename, typename>typename F>
        requires (!(... && requires{ typename F<I, Ts>::type; }))
    struct fold<LC<T, Ts...>, I, F>
    {
        using type = typename fold<LC<Ts...>, F<I, T>, F>::type;
    };

    template<template<typename...>typename LC, typename I, template<typename, typename>typename F>
    struct fold<LC<>, I, F>
    {
        using type = I;
    };

    template<typename L, typename I, template<typename, typename>typename F>
    using fold_t = typename fold<L, I, F>::type;


    //(L<Ts...>, T) -> L<Ts..., T>
    template<typename L, typename T>
    struct push_back;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct push_back<LC<Ts...>, T>
    {
        using type = LC<Ts..., T>;
    };

    //(L<Ts...>, T) -> L<T, Ts...>
    template<typename L, typename T>
    struct push_front;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct push_front<LC<Ts...>, T>
    {
        using type = LC<T, Ts...>;
    };

    //L<Ts..., T> -> L<Ts...>
    template<typename L>
    struct pop_back
    {
        using type = typename range<L, 0, size_v<L>-1>::type;
    };

    //L<T, Ts...> -> L<Ts...>
    template<typename L>
    struct pop_front;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct pop_front<LC<T, Ts...>>
    {
        using type = LC<Ts...>;
    };

    //L<T0, T1, T2, ..., Tn> -> L<Tn, Tn-1, Tn-2, ..., T0>
    template<typename L>
    struct reverse
    {
        using type = typename range<L, size_v<L>-1, -1, -1>::type;
    };

    template<typename L, template<typename>typename F>
    struct filter;

    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
    struct filter<LC<Ts...>, F>
    {
        using type = typename order<LC<Ts...>, core::index_filter_seq<core::constant_seq<F<Ts>::value...>>>::type;
    };


    //(L<T0, T1, T2, ..., Tn>, T -> U) -> L<U0, U1, U2, ..., Un>
    template<typename L, template<typename>typename F>
    struct transform;

    //(L<T0, T1, T2, ..., Tn>, T -> F<T>::type -> U) -> L<U0, U1, U2, ..., Un>
    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
        requires (... && requires{ typename Ts::type; })
    struct transform<LC<Ts...>, F>
    {
        using type = LC<typename F<Ts>::type...>;
    };

    //(L<T0, T1, T2, ..., Tn>, T -> U) -> L<U0, U1, U2, ..., Un>
    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
        requires (!(... && requires{ typename Ts::type; }))
    struct transform<LC<Ts...>, F>
    {
        using type = LC<F<Ts>...>;
    };

    template<typename... Ls>
    struct concat;

    template<template<typename...>typename LC1, typename ...Ts1, template<typename...>typename LC2, typename ...Ts2, typename ...Ls>
    struct concat<LC1<Ts1...>, LC2<Ts2...>, Ls...>
    {
        using type = typename concat<LC1<Ts1..., Ts2...>, Ls...>::type;
    };

    template<typename L>
    struct concat<L>
    {
        using type = L;
    };

    template<typename L>
    struct join;

    template<template<typename...>typename LC, typename... Ts>
    struct join<LC<Ts...>>
    {
        using type = typename concat<LC<>, Ts...>::type;
    };
}
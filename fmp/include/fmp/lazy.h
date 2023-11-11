#pragma once

#include "algorithm.h"

namespace fmp
{
    /// @brief @c lazy 是一个惰性求值的类型序列操作类，可以对类型序列进行各种变换和操作，最后通过 @c type 获取结果类型。
    /// @tparam L 类型序列
    /// @tparam ...FL 变换和操作函数模板
    template<typename L, template<typename...>typename... FL>
    struct lazy;

    template<typename L, template<typename...>typename F, template<typename...>typename... FL>
    struct lazy<L, F, FL...>
    {
        template<long start, long end, long step = 1>
        using range = lazy<L, F, FL..., typename bind_value<fmp::range, start, end, step>::type>;

        template<long count>
        using take = lazy<L, F, FL..., typename bind_value<fmp::take, count>::type>;

        template<long count>
        using drop = typename lazy<L, F, FL..., typename bind_value<fmp::drop, count>::type>;

        template<template<typename, typename>typename P, typename I>
        using fold = typename lazy<L, F, FL..., typename bind_template<fmp::fold, P, I>::type>;

        template<typename T>
        using push_back = lazy<L, F, FL..., typename bind<fmp::push_back, T>::type>;

        template<typename T>
        using push_front = lazy<L, F, FL..., typename bind<fmp::push_front, T>::type>;

        using pop_back = lazy<L, F, FL..., typename bind<fmp::pop_back>::type>;

        using pop_front = lazy<L, F, FL..., typename bind<fmp::pop_front>::type>;

        using reverse = lazy<L, F, FL..., typename bind<fmp::reverse>::type>;

        template<template<typename>typename P>
        using filter = lazy<L, F, FL..., typename bind_template<fmp::filter, P>::type>;

        template<template<typename>typename P>
        using transform = lazy<L, F, FL..., typename bind_template<fmp::transform, P>::type>;

        template<typename... Ls>
        using concat = lazy<L, F, FL..., typename bind<fmp::concat, Ls...>::type>;

        template<typename... Ts>
        using append = lazy<L, F, FL..., typename bind<fmp::append, Ts...>::type>;

        using join = lazy<L, F, FL..., typename bind<fmp::join>::type>;

        template<template<typename...>typename C>
        using to = lazy<L, F, FL..., typename bind_template<fmp::to, C>::type>;

        using head = lazy<L, F, FL..., typename bind<fmp::head>::type>;

        using tail = lazy<L, F, FL..., typename bind<fmp::tail>::type>;

        template<long idx>
        using at = lazy<L, F, FL..., typename bind_value<fmp::at, idx>::type>;

        template<typename S>
        using order = lazy<L, F, FL..., typename bind<fmp::order, S>::type>;

        using type = lazy<typename F<L>::type, FL...>::type;

        constexpr static auto size = fmp::size<type>::value;

        template<template<typename>typename F>
        constexpr static bool all_of = fmp::all_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool any_of = fmp::any_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool none_of = fmp::none_of<type, F>::value;
    };

    template<typename L>
    struct lazy<L>
    {
        template<long start, long end, long step = 1>
        using range = lazy<L, typename bind_value<fmp::range, start, end, step>::type>;

        template<long count>
        using take = lazy<L, typename bind_value<fmp::take, count>::type>;

        template<long count>
        using drop = typename lazy<L, typename bind_value<fmp::drop, count>::type>;

        template<template<typename, typename>typename P, typename I>
        using fold = typename lazy<L, typename bind_template<fmp::fold, P, I>::type>;

        template<typename T>
        using push_back = lazy<L, typename bind<fmp::push_back, T>::type>;

        template<typename T>
        using push_front = lazy<L, typename bind<fmp::push_front, T>::type>;

        using pop_back = lazy<L, typename bind<fmp::pop_back>::type>;

        using pop_front = lazy<L, typename bind<fmp::pop_front>::type>;

        using reverse = lazy<L, typename bind<fmp::reverse>::type>;

        template<template<typename>typename P>
        using filter = lazy<L, typename bind_template<fmp::filter, P>::type>;

        template<template<typename>typename P>
        using transform = lazy<L, typename bind_template<fmp::transform, P>::type>;

        template<typename... Ls>
        using concat = lazy<L, typename bind<fmp::concat, Ls...>::type>;

        template<typename... Ts>
        using append = lazy<L, typename bind<fmp::append, Ts...>::type>;

        using join = lazy<L, typename bind<fmp::join>::type>;

        template<template<typename...>typename C>
        using to = lazy<L, typename bind_template<fmp::to, C>::type>;

        using head = lazy<L, typename bind<fmp::head>::type>;

        using tail = lazy<L, typename bind<fmp::tail>::type>;

        template<long idx>
        using at = lazy<L, typename bind_value<fmp::at, idx>::type>;

        template<typename S>
        using order = lazy<L, typename bind<fmp::order, S>::type>;

        using type = L;

        constexpr static auto size = fmp::size<type>::value;

        template<template<typename>typename F>
        constexpr static bool all_of = fmp::all_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool any_of = fmp::any_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool none_of = fmp::none_of<type, F>::value;
    };
}

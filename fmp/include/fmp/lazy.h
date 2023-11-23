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
        using range = lazy<L, F, FL..., bind_value<fmp::range, start, end, step>::template type>;

        template<long count>
        using take = lazy<L, F, FL..., bind_value<fmp::take, count>::template type>;

        template<long count>
        using drop = lazy<L, F, FL..., bind_value<fmp::drop, count>::template type>;

        template<template<typename, typename>typename P, typename I>
        using fold = lazy<L, F, FL..., bind_template<fmp::fold, P, I>::template type>;

        template<typename T>
        using push_back = lazy<L, F, FL..., bind<fmp::push_back, T>::template type>;

        template<typename T>
        using push_front = lazy<L, F, FL..., bind<fmp::push_front, T>::template type>;

        using pop_back = lazy<L, F, FL..., bind<fmp::pop_back>::template type>;

        using pop_front = lazy<L, F, FL..., bind<fmp::pop_front>::template type>;

        using reverse = lazy<L, F, FL..., bind<fmp::reverse>::template type>;

        template<template<typename>typename P>
        using filter = lazy<L, F, FL..., bind_template<fmp::filter, P>::template type>;

        template<template<typename>typename P>
        using transform = lazy<L, F, FL..., bind_template<fmp::transform, P>::template type>;

        template<typename... Ls>
        using concat = lazy<L, F, FL..., bind<fmp::concat, Ls...>::template type>;

        template<typename... Ts>
        using append = lazy<L, F, FL..., bind<fmp::append, Ts...>::template type>;

        using join = lazy<L, F, FL..., bind<fmp::join>::template type>;

        template<template<typename...>typename C>
        using to = lazy<L, F, FL..., bind_template<fmp::to, C>::template type>;

        using head = lazy<L, F, FL..., bind<fmp::head>::template type>;

        using tail = lazy<L, F, FL..., bind<fmp::tail>::template type>;

        template<long idx>
        using at = lazy<L, F, FL..., bind_value<fmp::at, idx>::template type>;

        template<typename S>
        using order = lazy<L, F, FL..., bind<fmp::order, S>::template type>;

        using type = typename lazy<typename F<L>::type, FL...>::type;

        template<typename T>
        constexpr static auto count = fmp::count<type, T>::value;

        template<template<typename>typename F>
        constexpr static auto count_if = fmp::count_if<type, F>::value;

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
        using range = lazy<L, bind_value<fmp::range, start, end, step>::template type>;

        template<long count>
        using take = lazy<L, bind_value<fmp::take, count>::template type>;

        template<long count>
        using drop = lazy<L, bind_value<fmp::drop, count>::template type>;

        template<template<typename, typename>typename P, typename I>
        using fold = lazy<L, bind_template<fmp::fold, P, I>::template type>;

        template<typename T>
        using push_back = lazy<L, bind<fmp::push_back, T>::template type>;

        template<typename T>
        using push_front = lazy<L, bind<fmp::push_front, T>::template type>;

        using pop_back = lazy<L, bind<fmp::pop_back>::template type>;

        using pop_front = lazy<L, bind<fmp::pop_front>::template type>;

        using reverse = lazy<L, bind<fmp::reverse>::template type>;

        template<template<typename>typename P>
        using filter = lazy<L, bind_template<fmp::filter, P>::template type>;

        template<template<typename>typename P>
        using transform = lazy<L, bind_template<fmp::transform, P>::template type>;

        template<typename... Ls>
        using concat = lazy<L, bind<fmp::concat, Ls...>::template type>;

        template<typename... Ts>
        using append = lazy<L, bind<fmp::append, Ts...>::template type>;

        using join = lazy<L, bind<fmp::join>::template type>;

        template<template<typename...>typename C>
        using to = lazy<L, bind_template<fmp::to, C>::template type>;

        using head = lazy<L, bind<fmp::head>::template type>;

        using tail = lazy<L, bind<fmp::tail>::template type>;

        template<long idx>
        using at = lazy<L, bind_value<fmp::at, idx>::template type>;

        template<typename S>
        using order = lazy<L, bind<fmp::order, S>::template type>;

        using type = L;

        template<typename T>
        constexpr static auto count = fmp::count<type, T>::value;

        template<template<typename>typename F>
        constexpr static auto count_if = fmp::count_if<type, F>::value;

        constexpr static auto size = fmp::size<type>::value;

        template<template<typename>typename F>
        constexpr static bool all_of = fmp::all_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool any_of = fmp::any_of<type, F>::value;

        template<template<typename>typename F>
        constexpr static bool none_of = fmp::none_of<type, F>::value;
    };
}

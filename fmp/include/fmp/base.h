#pragma once

namespace fmp
{
    /// @brief @c bind 将参数绑定到元函数。
    /// @tparam F 元函数
    /// @tparam ...Ts 除了 @c L 以外的参数
    template<template<typename...>typename F, typename... Ts>
    struct bind
    {
        template<typename L>
        using type = F<L, Ts...>;
    };

    /// @brief @c bind_value 将常量参数绑定到元函数。
    /// @tparam F 元函数
    /// @tparam ...values 常量参数
    template<template<typename, auto...>typename F, auto... values>
    struct bind_value
    {
        template<typename L>
        using type = F<L, values...>;
    };

    /// @brief 将参数绑定到使用模板模板参数的元函数。
    /// @tparam CF 元函数
    /// @tparam C 模板模板参数
    /// @tparam ...Ts 除了 @c L 以外的其它参数
    template<template<typename, template<typename...>typename, typename... >typename CF, template<typename...>typename C, typename...Ts>
    struct bind_template
    {
        template<typename L>
        using type = CF<L, C, Ts...>;
    };

    /// @brief 将序列转换为另一序列。
    /// @tparam L 类型序列
    /// @tparam C 另一序列序列类模板
    template<typename L, template<typename...>typename C>
    struct to;

    template<template<typename...>typename LC, typename ...Ts, template<typename...>typename C>
    struct to<LC<Ts...>, C>
    {
        using type = C<Ts...>;
    };

    /// @typedef
    /// @brief @c to_t 将序列转换为另一序列类型。
    /// @tparam L 类型序列 
    /// @tparam C 零一序列类模板
    template<typename L, template<typename...>typename C>
    using to_t = typename to<L, C>::type;

    /// @brief @c size 计算类型序列大小
    /// @tparam L 类型序列
    template<typename L>
    struct size;

    template<template<typename...>typename LC, typename ...Ts>
    struct size<LC<Ts...>>
    {
        constexpr static auto value = static_cast<long>(sizeof...(Ts));
    };

    /// @brief @c size_v 获得类型序列大小。
    /// @tparam L 类型序列
    template<typename L>
    inline constexpr long size_v = size<L>::value;

    /// @brief @c head 获得类型序列的第一个元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    template<typename L>
    struct head;

    template<template<typename...>typename LC, typename T, typename ...Ts>
    struct head<LC<T, Ts...>>
    {
        using type = T;
    };

    /// @typedef
    /// @brief @c head_t 获得类型序列的第一个元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    template<typename L>
    using head_t = typename head<L>::type;

    /// @brief @c tail 获得类型序列除了第一个元素以外的其余元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    template<typename L>
    struct tail;

    template<template<typename...>typename LC, typename T, typename ...Ts>
    struct tail<LC<T, Ts...>>
    {
        using type = LC<Ts...>;
    };

    /// @typedef
    /// @brief @c tail_t 获得类型序列除了第一个元素以外的其余元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    template<typename L>
    using tail_t = typename tail<L>::type;

    /// @brief @c at 获得类型序列中指定位置的元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    /// @tparam idx 元素位置，必须是非负整数且小于类型序列大小
    template<typename L, long idx>
        requires (0 <= idx && idx < size_v<L>)
    struct at
    {
        using type = typename at<typename tail<L>::type, idx - 1>::type;
    };

    template<typename L>
    struct at<L, 0>
    {
        using type = typename head<L>::type;
    };

    /// @typedef
    /// @brief @c at_t 获得类型序列中指定位置的元素。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    /// @tparam idx 元素位置，必须是非负整数且小于类型序列大小
    template<typename L, long idx>
    using at_t = at<L, (idx + size_v<L>) % size_v<L>>::type;

    /// @brief @c order 根据索引序列对类型序列进行重排。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    /// @tparam S 索引序列，可以是任何接受若干整数参数的类模板
    template<typename L, typename S>
    struct order;

    template<template<typename...>typename LC, typename ...Ts, template<long...>typename SC, long... idx>
    struct order<LC<Ts...>, SC<idx...>>
    {
        using type = LC<typename at<LC<Ts...>, idx>::type...>;
    };

    /// @typedef
    /// @brief @c order_t 根据索引序列对类型序列进行重排。
    /// @tparam L 类型序列，可以是任何接受若干类型参数的类模板
    /// @tparam S 索引序列，可以是任何接受若干整数参数的类模板
    template<typename L, typename S>
    using order_t = typename order<L, S>::type;
}
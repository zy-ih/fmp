namespace fmp::core
{
    /// @class constant_seq core.h "core.h"
    /// @brief @c constant_seq 表示编译时常量序列。
    /// @tparam ...vals 任意个常量序列
    template<auto... vals>
    struct constant_seq
    {
        /// @static
        /// @brief 常量序列大小
        constexpr static auto size = static_cast<long long>(sizeof...(vals));
    };

    /// @typedef
    /// @brief @c index_seq 是 @code core::constant_seq<long long...> @endcode 别名
    /// @tparam ...vals 编译时整数序列
    /// @par example
    /// @code
    /// core::index_seq<0, 1, 2, 3, 4> 
    /// @endcode
    template<long long... vals>
    using index_seq = constant_seq<vals...>;

    /// @brief @c seq_push_back 将常量加入到序列后面
    /// @tparam S 表示序列
    /// @tparam v 要加入的常量
    /// @par example
    /// @code
    /// core::seq_push_back<core::constant_seq<1, 'x', 3.4>, -89>::type //core::constant_seq<1, 'x', 3.4, -89>
    /// @endcode
    template<typename S, auto v>
    struct seq_push_back;

    template<template<auto...>typename SC, auto...vals, auto v>
    struct seq_push_back<SC<vals...>, v>
    {
        using type = SC<vals..., v>;
    };

    template<typename S, long long start, long long end, long long step>
    struct index_seq_gen
    {
        using type = typename index_seq_gen<typename seq_push_back<S, start>::type, start + step, end, step>::type;
    };

    template<typename S, long long end, long long step>
    struct index_seq_gen<S, end, end, step>
    {
        using type = S;
    };

    template<typename S, long long v, long long count>
    struct index_seq_repeat
    {
        using type = typename index_seq_repeat<typename seq_push_back<S, v>::type, v, count - 1>::type;
    };

    template<typename S, long long v>
    struct index_seq_repeat<S, v, 0>
    {
        using type = S;
    };

    template<typename S, typename FS, long long next = 0>
    struct index_seq_filter;

    template<typename S, template<bool...>typename SSC, bool... flags, long long next>
    struct index_seq_filter<S, SSC<true, flags...>, next>
    {
        using type = typename index_seq_filter<typename seq_push_back<S, next>::type, SSC<flags...>, next + 1>::type;
    };

    template<typename S, template<bool...>typename SSC, bool... flags, long long next>
    struct index_seq_filter<S, SSC<false, flags...>, next>
    {
        using type = typename index_seq_filter<S, SSC<flags...>, next + 1>::type;
    };

    template<typename S, template<bool...>typename SSC, long long next>
    struct index_seq_filter<S, SSC<>, next>
    {
        using type = S;
    };

    template<long long start, long long end, long long step = 1>
    using make_index_seq = typename index_seq_gen<index_seq<>, start, end, step>::type;

    template<long long v, long long count>
    using index_repeat_seq = typename index_seq_repeat<index_seq<>, v, count>::type;

    template<typename FS>
    using index_filter_seq = typename index_seq_filter<index_seq<>, FS>::type;
}
#pragma once
#include <type_traits>

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
        constexpr static auto size = static_cast<long>(sizeof...(vals));
    };

    /// @typedef
    /// @brief @c index_seq 是 @code core::constant_seq<long...> @endcode 别名。
    /// @tparam ...vals 编译时整数序列
    template<long... vals>
    using index_seq = constant_seq<vals...>;

    /// @brief @c seq_push_back 将常量加入到序列后面。
    /// @tparam S 表示序列
    /// @tparam v 要加入的常量
    template<typename S, auto v>
    struct seq_push_back;

    template<template<auto...>typename SC, auto...vals, auto v>
    struct seq_push_back<SC<vals...>, v>
    {
        using type = SC<vals..., v>;
    };

    /// @brief @c index_seq_gen 生成从 @c start 到 @c end (不包括)步长为 @c step 的整数序列。
    /// @tparam S 空序列
    /// @tparam start 起始值
    /// @tparam end 结束值
    /// @tparam step 步长
    template<typename S, long start, long end, long step>
    struct index_seq_gen
    {
        using type = typename index_seq_gen<typename seq_push_back<S, start>::type, start + step, end, step>::type;
    };

    template<typename S, long end, long step>
    struct index_seq_gen<S, end, end, step>
    {
        using type = S;
    };

    /// @brief @c index_seq_repeat 生成重复整数序列。
    /// @tparam S 空序列
    /// @tparam v 要重复的整数
    /// @tparam count 重复次数
    template<typename S, long v, long count>
    struct index_seq_repeat
    {
        using type = typename index_seq_repeat<typename seq_push_back<S, v>::type, v, count - 1>::type;
    };

    template<typename S, long v>
    struct index_seq_repeat<S, v, 0>
    {
        using type = S;
    };

    /// @brief @c index_seq_filter 根据掩码序列生成递增的索引序列（默认从0开始）。
    /// @tparam S 空序列
    /// @tparam FS 掩码序列
    /// @tparam next 被筛选的索引（默认从0开始）
    template<typename S, typename FS, long next = 0>
    struct index_seq_filter;

    template<typename S, template<bool...>typename SSC, bool... flags, long next>
    struct index_seq_filter<S, SSC<true, flags...>, next>
    {
        using type = typename index_seq_filter<typename seq_push_back<S, next>::type, SSC<flags...>, next + 1>::type;
    };

    template<typename S, template<bool...>typename SSC, bool... flags, long next>
    struct index_seq_filter<S, SSC<false, flags...>, next>
    {
        using type = typename index_seq_filter<S, SSC<flags...>, next + 1>::type;
    };

    template<typename S, template<bool...>typename SSC, long next>
    struct index_seq_filter<S, SSC<>, next>
    {
        using type = S;
    };

    /// @typedef
    /// @brief @c make_index_seq 生成步长为1的索引序列。
    /// @tparam start 起始值
    /// @tparam end 结束值
    /// @tparam step 步长（默认为1）
    template<long start, long end, long step = 1>
    using make_index_seq = typename index_seq_gen<index_seq<>, start, end, step>::type;

    /// @typedef
    /// @brief @c index_repeat_seq 生成重复索引序列。
    /// @tparam v 要重复的整数
    /// @tparam count 重复次数
    template<long v, long count>
    using index_repeat_seq = typename index_seq_repeat<index_seq<>, v, count>::type;

    /// @typedef
    /// @brief @c index_filter_seq 根据掩码序列生成从0开始递增的索引序列。
    /// @tparam FS 掩码序列
    template<typename FS>
    using index_filter_seq = typename index_seq_filter<index_seq<>, FS>::type;
}
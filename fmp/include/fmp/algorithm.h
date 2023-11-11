#pragma once

#include "core.h"
#include "base.h"

namespace fmp
{
    /// @brief @c range 获取下标从 @c start 到 @c end ，步长为 @c step 的元素构成的新序列。
    /// @tparam L 类型序列
    /// @tparam start 开始位置
    /// @tparam end 结束位置（不包括）
    /// @tparam step 步长
    template<typename L, long start, long end, long step = 1>
    struct range
    {
        using type = typename order<L, core::make_index_seq<start, end, step>>::type;
    };

    template<typename L, long start, long end, long step = 1>
    using range_t = typename range<L, start, end, step>::type;

    /// @brief @c take 获取类型序列的前 @c count 个元素构成的新序列。
    /// @details (L<T0, T1, ..., Tn> -> L<T0, T1, ..., Tcount>)
    /// @tparam L 类型序列
    /// @tparam count 元素个数
    template<typename L, long count>
    struct take
    {
        using type = typename range<L, 0, count>::type;
    };

    template<typename L, long count>
    using take_t = typename take<L, count>::type;

    /// @brief @c drop 跳过类型序列的前 @c count 个元素，获取剩余元素构成的新序列。
    /// @tparam L 类型序列
    /// @tparam count 元素个数
    template<typename L, long count>
    struct drop
    {
        using type = typename range<L, count, size_v<L>>::type;
    };

    template<typename L, long count>
    using drop_t = typename drop<L, count>::type;

    /// @brief @c repeat 重复类型 @c T 生成一个包含 @c count 个元素的新序列。
    /// @details (LC, T, count) -> L<T, T, ..., T>)
    /// @tparam T 类型
    /// @tparam count 元素个数
    /// @tparam LC 序列容器，默认为 type_list
    template<typename T, long count, template<typename...>typename LC = type_list>
    struct repeat
    {
        using type = typename order<LC<T>, core::index_repeat_seq<0, count>>::type;
    };

    template<typename T, long count, template<typename...>typename LC = type_list>
    using repeat_t = typename repeat< T, count, LC>::type;

    /// @brief @c fold 对类型序列进行折叠操作，从左到右依次用函数 @c F 应用到初始值 @c I 和每个元素上，得到最终结果。
    /// @tparam L 类型序列
    /// @tparam F 函数模板，接受两个类型参数，返回一个类型
    /// @tparam I 初始值类型
    template<typename L, template<typename, typename>typename F, typename I>
    struct fold;

    template<template<typename...>typename LC, typename T, typename...Ts, template<typename, typename>typename F, typename I>
        requires (... && requires{ typename F<I, Ts>::type; })
    struct fold<LC<T, Ts...>, F, I>
    {
        using type = typename fold<LC<Ts...>, F, typename F<I, T>::type>::type;
    };

    template<template<typename...>typename LC, typename T, typename...Ts, template<typename, typename>typename F, typename I>
        requires (!(... && requires{ typename F<I, Ts>::type; }))
    struct fold<LC<T, Ts...>, F, I>
    {
        using type = typename fold<LC<Ts...>, F, F<I, T>>::type;
    };

    template<template<typename...>typename LC, template<typename, typename>typename F, typename I>
    struct fold<LC<>, F, I>
    {
        using type = I;
    };

    template<typename L, template<typename, typename>typename F, typename I>
    using fold_t = typename fold<L, F, I>::type;

    /// @brief 在类型序列的末尾添加一个新的类型元素，得到一个新的类型序列。
    /// @details (L<Ts...>, T) -> L<Ts..., T>
    /// @tparam L 类型序列
    /// @tparam T 新增的类型元素
    template<typename L, typename T>
    struct push_back;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct push_back<LC<Ts...>, T>
    {
        using type = LC<Ts..., T>;
    };

    template<typename L, typename T>
    using  push_back_t = typename push_back<L, T>::type;

    /// @brief @c push_front 在类型序列的开头添加一个新的类型元素，得到一个新的类型序列。
    /// @details (L<Ts...>, T) -> L<T, Ts...>
    /// @tparam L 类型序列
    /// @tparam T 新增的类型元素
    template<typename L, typename T>
    struct push_front;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct push_front<LC<Ts...>, T>
    {
        using type = LC<T, Ts...>;
    };

    template<typename L, typename T>
    using  push_front_t = typename push_front<L, T>::type;

    /// @brief @c pop_back 移除一个类型序列的最后一个元素，得到一个新的类型序列。
    /// @details L<Ts..., T> -> L<Ts...>
    /// @tparam L 类型序列
    template<typename L>
    struct pop_back
    {
        using type = typename range<L, 0, size_v<L>-1>::type;
    };

    template<typename L>
    using pop_back_t = typename pop_back<L>::type;

    /// @brief @c pop_front 移除一个类型序列的第一个元素，得到一个新的类型序列。
    /// @details L<T, Ts...> -> L<Ts...>
    /// @tparam L 类型序列
    template<typename L>
    struct pop_front;

    template<template<typename...>typename LC, typename...Ts, typename T>
    struct pop_front<LC<T, Ts...>>
    {
        using type = LC<Ts...>;
    };

    template<typename L>
    using pop_front_t = typename pop_front<L>::type;

    /// @brief @c reverse 将一个类型序列反转顺序，得到一个新的类型序列。
    /// @details L<T0, T1, T2, ..., Tn> -> L<Tn, Tn-1, Tn-2, ..., T0>
    /// @tparam L 类型序列
    template<typename L>
    struct reverse
    {
        using type = typename range<L, size_v<L>-1, -1, -1>::type;
    };

    template<typename L>
    using reverse_t = typename reverse<L>::type;

    /// @brief @c filter 对一个类型序列中的每个元素应用谓词函数 @c F ，保留返回真值的元素，得到一个新的类型序列。
    /// @tparam L 类型序列
    /// @tparam F 谓词函数模板，接受一个类型参数，返回一个布尔值
    template<typename L, template<typename>typename F>
    struct filter;

    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
    struct filter<LC<Ts...>, F>
    {
        using type = typename order<LC<Ts...>, core::index_filter_seq<core::constant_seq<F<Ts>::value...>>>::type;
    };

    template<typename L, template<typename>typename F>
    using filter_t = typename filter<L, F>::type;

    /// @brief @c transform 对一个类型序列中的每个元素应用函数 @c F ，得到一个新的类型序列。
    /// @details (L<T0, T1, T2, ..., Tn>, T -> U) -> L<U0, U1, U2, ..., Un>
    /// @tparam L 类型序列
    /// @tparam F 函数模板，接受一个类型参数，返回一个类型
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

    template<typename L, template<typename>typename F>
    using transform_t = typename transform<L, F>::type;

    /// @brief @c concat 将多个类型序列连接起来，得到一个新的类型序列。
    /// @tparam Ls 由类型序列构成的序列
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

    template<typename... Ls>
    using concat_t = typename concat<Ls...>::type;

    /// @brief @c append 在一个类型序列的末尾添加若干个新的类型元素，得到一个新的类型序列。
    /// @tparam L 类型序列
    /// @tparam Ts 新增的类型元素
    template<typename L, typename... Ts>
    struct append
    {
        using type = typename concat<L, type_list<Ts...>>::type;
    };

    template<typename L, typename... Ts>
    using append_t = typename append<L, Ts...>::type;

    /// @brief @c join 将若干个类型序列合并为一个类型序列，相当于对每个类型序列执行 concat 操作。
    /// @tparam L 类型序列
    template<typename L>
    struct join;

    template<template<typename...>typename LC, typename... Ts>
    struct join<LC<Ts...>>
    {
        using type = typename concat<LC<>, Ts...>::type;
    };

    template<typename L>
    using join_t = typename join<L>::type;

    /// @brief @c all_of 判断类型序列中所有元素满足一元谓词F
    /// @tparam L 类型序列
    /// @tparam F 一元谓词
    template<typename L, template<typename>typename F>
    struct all_of;

    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
    struct all_of<LC<Ts...>, F>
    {
        constexpr static bool value = (true && ... && F<Ts>::value);
    };

    template<typename L, template<typename>typename F>
    inline constexpr bool all_of_v = all_of<L, F>::value;

    /// @brief @c any_of 判断类型序列中至少有一个元素满足一元谓词F
    /// @tparam L 类型序列
    /// @tparam F 一元谓词
    template<typename L, template<typename>typename F>
    struct any_of;

    template<template<typename...>typename LC, typename ...Ts, template<typename>typename F>
    struct any_of<LC<Ts...>, F>
    {
        constexpr static bool value = (false || ... || F<Ts>::value);
    };

    template<typename L, template<typename>typename F>
    inline constexpr bool any_of_v = any_of<L, F>::value;

    /// @brief @c none_of 判断类型序列中所有元素都不满足一元谓词F
    /// @tparam L 类型序列
    /// @tparam F 一元谓词
    template<typename L, template<typename>typename F>
    struct none_of
    {
        constexpr static bool value = !any_of<L, F>::value;
    };

    template<typename L, template<typename>typename F>
    inline constexpr bool none_of_v = none_of<L, F>::value;
}
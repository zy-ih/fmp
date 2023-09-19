namespace fmp
{
    template<template<typename...>typename F, typename... Ts>
    struct bind
    {
        template<typename L>
        using type = F<L, Ts...>;
    };

    template<template<typename, template<typename...>typename, typename... >typename CF, template<typename...>typename C, typename...Ts>
    struct bind_template
    {
        template<typename L>
        using type = CF<L, C, Ts...>;
    };

    template<typename L, template<typename...>typename C>
    struct to;

    template<template<typename...>typename LC, typename ...Ts, template<typename...>typename C>
    struct to<LC<Ts...>, C>
    {
        using type = C<Ts...>;
    };

    template<typename L, template<typename...>typename C>
    using to_t = typename to<L, C>::type;

    template<typename L>
    struct size;

    template<template<typename...>typename LC, typename ...Ts>
    struct size<LC<Ts...>>
    {
        constexpr static auto value = static_cast<long long>(sizeof...(Ts));
    };

    template<typename L>
    constexpr long long size_v = size<L>::value;

    template<typename L>
    struct head;

    template<template<typename...>typename LC, typename T, typename ...Ts>
    struct head<LC<T, Ts...>>
    {
        using type = T;
    };

    template<typename L>
    using head_t = typename head<L>::type;

    template<typename L>
    struct tail;

    template<template<typename...>typename LC, typename T, typename ...Ts>
    struct tail<LC<T, Ts...>>
    {
        using type = LC<Ts...>;
    };

    template<typename L>
    using tail_t = typename tail<L>::type;

    template<typename L, long long idx>
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

    template<typename L, long long idx>
    using at_t = at<L, (idx + size_v<L>) % size_v<L>>::type;

    template<typename L, typename S>
    struct order;

    template<template<typename...>typename LC, typename ...Ts, template<long long...>typename SC, long long... idx>
    struct order<LC<Ts...>, SC<idx...>>
    {
        using type = LC<typename at<LC<Ts...>, idx>::type...>;
    };

    template<typename L, typename S>
    using order_t = typename order<L, S>::type;
}
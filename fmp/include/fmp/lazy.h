#include "algorithm.h"

namespace fmp
{
    //template<typename L, template<typename...>typename... FL>
    //struct lazy;

    //template<typename L, template<typename...>typename F, template<typename...>typename... FL>
    //struct lazy<L, F, FL...>
    //{
    //    template<typename T>
    //    using push_back = lazy<L, F, FL..., typename bind<fmp::push_back, T>::type>;
    //    template<typename T>
    //    using push_front = lazy<L, F, FL..., typename bind<fmp::push_front, T>::type>;
    //    using pop_back = lazy<L, F, FL..., typename bind<fmp::pop_back>::type>;
    //    using pop_front = lazy<L, F, FL..., typename bind<fmp::pop_front>::type>;
    //    using reverse = lazy<L, F, FL..., typename bind<fmp::reverse>::type>;
    //    template<template<typename...>typename C>
    //    using reverse_to = lazy<L, F, FL..., typename fmp::bind_template<fmp::reverse_to, C>::type>;
    //    using type = lazy<typename F<L>::type, FL...>::type;
    //};

    //template<typename L>
    //struct lazy<L>
    //{
    //    template<typename T>
    //    using push_back = lazy<L, typename bind<fmp::push_back, T>::type>;
    //    template<typename T>
    //    using push_front = lazy<L, typename bind<fmp::push_front, T>::type>;
    //    using pop_back = lazy<L, typename bind<fmp::pop_back>::type>;
    //    using pop_front = lazy<L, typename bind<fmp::pop_front>::type>;
    //    using reverse = lazy<L, typename bind<fmp::reverse>::type>;
    //    template<template<typename...>typename C>
    //    using reverse_to = lazy<L, typename fmp::bind_template<fmp::reverse_to, C>::type>;
    //    using type = L;
    //};
}

#include <fmp.hpp>
#include <list>
#include <tuple>
#include <vector>

using namespace fmp;

template<typename T>
struct sizeof4
{
    constexpr static auto value = sizeof(T) == 4;
};

template<template<typename, long, typename...>typename F, long value, typename... Ts>
struct custom_bind
{
    template<typename L>              //Note: There is usually only one type parameter here, which represents a type list.
    using type = F<L, value, Ts...>;
};

static_assert(
    std::is_same_v<lazy<type_list<int, double, long>>
    ::append<char>
    ::filter<sizeof4>
    ::concat<repeat_t<int, 2, std::tuple>>
    ::to<std::tuple>
    ::type,
    std::tuple<int, long, int, int>>);


int main()
{
    using t = fmp::lazy<std::tuple<int, std::vector<int>>>::filter< fmp::bind_template<fmp::is_template_instance, std::vector>::type>::type;
    fmp::count_v<std::tuple<int, long, int, int>, int>;
}

#pragma once
#include <concepts>
#include <type_traits>
namespace fmp
{
	template<typename, template<typename...>typename TC>
	struct is_template_instance : ::std::false_type { };

	template<template<typename...>typename TC, typename... Ts>
	struct is_template_instance<TC<Ts...>, TC> : ::std::true_type {};

	template<typename T, template<typename...>typename TC>
	constexpr bool is_template_instance_v = is_template_instance<T, TC>::value;
}

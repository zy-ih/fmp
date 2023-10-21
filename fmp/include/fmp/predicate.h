#pragma once
namespace fmp
{
	template<typename, template<typename...>typename TC>
	struct is_template_instance
	{
		constexpr static bool value = false;
	};

	template<template<typename...>typename TC, typename... Ts>
	struct is_template_instance<TC<Ts...>, TC>
	{
		constexpr static bool value = true;
	};

	template<typename T, template<typename...>typename TC>
	constexpr bool is_template_instance_v = is_template_instance<T, TC>::value;
}

#pragma once
namespace fmp
{
	template<typename, template<typename...>typename TC>
	struct is_template_instance_type
	{
		constexpr static bool value = false;
	};

	template<template<typename...>typename TC, typename... Args>
	struct is_template_instance_type<TC<Args...>, TC>
	{
		constexpr static bool value = true;
	};

	template<typename T, template<typename...>typename TC>
	constexpr bool is_template_instance_v = is_template_instance_type<T, TC>::value;
}
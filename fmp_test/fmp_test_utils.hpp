#pragma once
#include <iostream>
namespace fmp::test {
	struct lifetime_test_type
	{
		lifetime_test_type() noexcept
		{
			try { std::cerr << "\tdefault construct\n"; }
			catch (...) {}
		}
		lifetime_test_type(lifetime_test_type const&) noexcept
		{
			try { std::cerr << "\tcopy construct\n"; }
			catch (...) {}
		}
		lifetime_test_type(lifetime_test_type&&) noexcept
		{
			try { std::cerr << "\tmove construct\n"; }
			catch (...) {}
		}
		lifetime_test_type& operator=(lifetime_test_type const&) noexcept
		{
			try { std::cerr << "\tcopy assign\n"; }
			catch (...) {}
			return *this;
		}
		lifetime_test_type& operator=(lifetime_test_type&&) noexcept
		{
			try { std::cerr << "\tmove assign\n"; }
			catch (...) {}
			return *this;
		}
		~lifetime_test_type() noexcept
		{
			try { std::cerr << "\tdestroy assign\n"; }
			catch (...) {}
		}
	};
}
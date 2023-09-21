#include "fmp_test_utils.hpp"

#define FWD(arg) std::forward<decltype(arg)>(arg)

template<typename T>
void test_FWD(T&& arg) noexcept
{
	auto tmp = FWD(arg);
}

#define TEST(expr) ((std::cout <<  #expr << " {\n" ),expr,(std::cout << "}\n\n"))
using namespace ::fmp::test;

int main()
{
	lifetime_test_type lref{};
	const lifetime_test_type clref{};
	const lifetime_test_type& clref2 = clref;

	TEST(test_FWD(lref));
	TEST(test_FWD(clref));
	TEST(test_FWD(clref2));
	TEST(test_FWD(lifetime_test_type{}));
	TEST(test_FWD(std::move(lref)));

}

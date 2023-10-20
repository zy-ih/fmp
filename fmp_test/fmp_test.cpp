#include <fmp.hpp>
#include <list>
#include <tuple>

using namespace fmp;

template<typename T>
struct sizeof4
{
    constexpr static auto value = sizeof(T) == 4;
};

int main()
{
    constexpr lazy<type_list<int, double>>::append<char>::filter<sizeof4>::concat<repeat_t<int, 3, std::tuple>>::to<std::tuple>::type point4d{0, 2, 3, 4};

    constexpr auto r = std::get<2>(point4d);

}

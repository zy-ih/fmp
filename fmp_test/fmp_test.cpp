#include <fmp.hpp>
#include <list>
#include <tuple>

using namespace fmp;

template<typename T>
struct sizeof4
{
    constexpr static auto value = sizeof(T) == 4;
};

static_assert(
    std::is_same_v<lazy<type_list<int, double>>
    ::append<char>
    ::filter<sizeof4>
    ::concat<repeat_t<int, 3, std::tuple>>
    ::to<std::tuple>
    ::type,
    std::tuple<int, int, int, int>>);

int main()
{

}

#include <fmp.hpp>
#include <vector>
#include <list>
#include <tuple>
using namespace fmp;
static_assert(is_template_instance_v<std::vector<int>, std::vector>);
static_assert(is_template_instance_v<std::vector<double>, std::vector>);
static_assert(is_template_instance_v<std::list<double>, std::list>);
static_assert(is_template_instance_v<std::tuple<double>, std::tuple>);

int main()
{
}

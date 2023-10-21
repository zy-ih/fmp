## fmp
fmp is a functional-style C++ template metaprogramming library used for type transformation.

It requires at least enabling the C++20 option as it makes use of concept syntax. 
The library itself doesn't depend on any other library or even the standard library. 
All available functionalities are in the `fmp` namespace, and you only need to include "fmp/fmp.hpp" to use them.
### Sneak Peek
```cpp
#include <tuple>
#include <type_traits>
#include <fmp/fmp.hpp>

template<typename T>
struct sizeof4 {
    constexpr static auto value = sizeof(T) == 4;
};

static_assert(
    std::is_same_v<fmp::lazy<type_list<int, double, long>>
       ::append<char>
       ::filter<sizeof4>
       ::concat<repeat_t<int, 2, std::tuple>>
       ::to<std::tuple>
       ::type,
    std::tuple<int, long, int, int>>);
```
### Utility
#### type_list
`type_list` is a class template that represents a sequence of types and is used for type computations. 
`fmp` can use any class template with a variable number of parameters, including but not limited to `std::tuple`, `boost::mp11::mp_list`.

    using type = fmp::type_list<int, double, std::string, int, std::vector<int>>;
#### lazy
`lazy` applies type functions to `type_list` by using it as a template parameter and lazily applying them to `type_list` through chained calls.
```cpp
using type = fmp::lazy<std::tuple<char, int, std::vector<int>>>
                ::filter<fmp::bind_template<fmp::is_template_instance, std::vector>::type>
                ::type;
static_assert(std::is_same_v<type, std::vector<int>>);
```
#### bind
`bind` is used to extend type functions in `lazy`.
Typically, type functions have several template parameters, with the first parameter always representing the type list.
`bind` can bind all remaining parameters to the type function, resulting in a new type function that only accepts a type list.

`bind_template` and `bind_value` are variations of `bind`. They correspond to the cases of template template parameter and non-type template parameters, respectively.
Template parameters can be complex and varied. If you want to extend `lazy`, the existing variations of `bind` may not be sufficient, and you may need to define your own `bind`.
```cpp
// Bind a constant and multiple template parameters to the type function F.
template<typename F, long value, typename... Ts>
struct custom_bind
{
    // Note: There is usually only one type parameter here, which represents a type list.
    template<typename L>
    using type = F<L, value, Ts...>;
};
```
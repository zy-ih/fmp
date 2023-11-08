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
`lazy` applies type functions to type list by using it as a template parameter and lazily applying them to type list through chained calls.
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
### Algorithm 
The following implementations all have alias templates in xxx_t or xxx_v C++ Standard Template Library style.

#### append
`append` adds a type to the end of a type list.
```cpp
using type = fmp::append<std::tuple<int, char>, double>::type;
static_assert(std::is_same_v<type, std::tuple<int, char, double>>);
```

#### at
`at` returns the type at index `idx` in type list.
```cpp
using type = fmp::at<std::tuple<int, char, double>, 1>::type;
static_assert(std::is_same_v<type, char>);
```

#### concat
`concat` concatenates multiple type lists into one.
```cpp
using type = fmp::concat<std::tuple<int, char>, std::tuple<double>, std::tuple<float>>::type;
static_assert(std::is_same_v<type, std::tuple<int, char, double, float>>);
```

#### drop
`drop` removes the first `count` types from a type list.
```cpp
using type = fmp::drop<std::tuple<int, char, double>, 2>::type;
static_assert(std::is_same_v<type, std::tuple<double>>);
```

#### filter
`filter` removes all types from a type list that do not satisfy a predicate.
```cpp
using type = fmp::filter<std::tuple<int, float, double>, std::is_integral>::type;
static_assert(std::is_same_v<type, std::tuple<int>>);
```

#### fold
`fold` applies a binary function to each element of a type list, starting with an initial value.
```cpp
template<typename T1, typename T2>
struct add {
    using type = decltype(std::declval<T1>() + std::declval<T2>());
};

using type = fmp::fold<std::tuple<int, float>, add>::type;
static_assert(std::is_same_v<type, float>);
```

#### head
`head` returns the first type in a type list.
```cpp
using type = fmp::head<std::tuple<int, char>>::type;
static_assert(std::is_same_v<type, int>);
```

#### join
`join` flattens a nested type list.
```cpp
using type = fmp::join<std::tuple<std::tuple<int>, std::tuple<char>>>::type;
static_assert(std::is_same_v<type, std::tuple<int, char>>);
```

#### order
`order` sorts a type list according to a specified index list. Specifically, it returns a new type list where the `i`-th element is the element at index `order[i]` in the original type list. For example, for a type list `std::tuple<int, char, double>` and an index list `std::index_sequence<2, 0, 1>`, `order` returns the type list `std::tuple<double, int, char>`. Note that `order` does not modify the original type list but returns a new sorted type list. If there are duplicate elements in the index list, there will be duplicate elements in the returned type list. If there are elements in the index list that are out of bounds of the original type list, a compile-time error will be raised.
```cpp
using type = fmp::order<fmp::type_list<int, char, double>, fmp::core::make_index_seq<fmp::size_v<L>-1, -1, -1>>::type;
static_assert(std::is_same_v<type, fmp::type_list<double, char, int>>);
```

#### pop_back
`pop_back` removes the last type from a type list.
```cpp
using type = fmp::pop_back<std::tuple<int, char>>::type;
static_assert(std::is_same_v<type, std::tuple<int>>);
```

#### pop_front
`pop_front` removes the first type from a type list.
```cpp
using type = fmp::pop_front<std::tuple<int, char>>::type;
static_assert(std::is_same_v<type, std::tuple<char>>);
```

#### push_back
`push_back` adds a type to the end of a type list.
```cpp
using type = fmp::push_back<std::tuple<int>, char>::type;
static_assert(std::is_same_v<type, std::tuple<int, char>>);
```

#### push_front
`push_front` adds a type to the beginning of a type list.
```cpp
using type = fmp::push_front<std::tuple<int>, char>::type;
static_assert(std::is_same_v<type, std::tuple<char, int>>);
```

#### range
`range` generates an integer sequence from `start`, inclusive to `end`, exclusive with step size of `step`.
```cpp
using type = fmp::range<std::tuple<int, double, char, char>, 1L, 3L>::type;
static_assert(std::is_same_v<type, std::tuple<double, char>>);
```

#### repeat
`repeat` generates a type list with length of `count`, where each element is of type `T`.
```cpp
using type = fmp::repeat<char, 3, fmp::type_list>::type;
static_assert(std:: is_same_v<type, fmp::type_list<char, char, char>>);
```

#### reverse
`reverse` reverses the order of types in a type list.
```cpp
using type = fmp::reverse<std::tuple<char, int, double>>::type;
static_assert(std::is_same_v<type,std::tuple<double, int, char>>);
```

#### size
Returns the number of types in a type list.
```cpp
inline constexpr auto v = fmp::size<std::variant<int, char, double>>::value;
static_assert(v == 3);
```

#### take
`take` returns the first `count` types from a type list.
```cpp
using type = fmp::take<std::tuple<int, char, double>, 2>::type;
static_assert(std::is_same_v<type, std::tuple<int, char>>);
```

#### to
`to` converts a type list to another template class.
```cpp
using type = fmp::to<std::tuple<int, char>, std::pair>::type;
static_assert(std::is_same_v<type, std::pair<int, char>>);
```

#### transform
`transform` applies a unary function to each element of a type list.
```cpp
template<typename T>
struct add_pointer {
    using type = T*;
};

using type = fmp::transform<std::tuple<int, char>, add_pointer>::type;
static_assert(std::is_same_v<type, std::tuple<int*, char*>>);
```
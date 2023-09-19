// fmp_test.cpp: 定义应用程序的入口点。
//

#include <iostream>
#include <algorithm>
#include <ranges>
#include <fmp.hpp>



int main()
{
    //fmp::transform<std::tuple<int, double, char>, A>::type x;

    //fmp::transform<std::tuple<int, double, char>, F>::type y;


    //fmp::order<std::tuple<int, double, char>, fmp::core::make_index_seq<-1, -4, -1>>::type;
    //fmp::take_t<std::tuple<int, double, char>, 2>;
    //fmp::repeat<double, 3>::type;
    //fmp::order<fmp::type_list<double>, fmp::core::index_repeat_seq<0, 3>>::type;

    fmp::fold<std::tuple<int, char, double>, fmp::type_list<>, fmp::push_back>::type;
    fmp::reverse<std::tuple<int, char, double>>::type;
}

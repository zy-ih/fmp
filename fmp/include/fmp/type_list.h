namespace fmp
{
    /// @brief @c type_list 表示类型列表。
    /// @details kasasd
    /// @tparam ...Ts 类型序列
    /// @par example
    /// @code{.c++}
    /// type_list<int, char, std::string>
    /// @endcode
    template<typename...>
    struct type_list;
}
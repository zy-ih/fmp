# CMakeList.txt: fmp_test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。

add_executable (fmp_test "fmp_test.cpp")
add_executable (fmp_test_FWD  "fmp_test_FWD.cpp" "fmp_test_utils.hpp" )

target_compile_features(fmp_test PUBLIC c_std_17 cxx_std_23)
target_compile_features(fmp_test_FWD PUBLIC c_std_17 cxx_std_23)

target_link_libraries(fmp_test PRIVATE fmp)

# TODO: 如有需要，请添加测试并安装目标。
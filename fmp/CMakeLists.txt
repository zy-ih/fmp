add_library(fmp INTERFACE)


set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
target_include_directories(fmp INTERFACE include)
target_compile_features(fmp INTERFACE c_std_17 cxx_std_23)
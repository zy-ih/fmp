add_library(fmp INTERFACE)


target_include_directories(fmp INTERFACE include)
target_compile_features(fmp INTERFACE c_std_17 cxx_std_23)
add_library(add_shared SHARED add.cpp)
target_compile_definitions(add_shared PRIVATE EXPORT)
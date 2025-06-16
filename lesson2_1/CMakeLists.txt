add_subdirectory(add)

include_directories(./lib)

#link_libraries(D:/LLM/CMake_Learn/lesson2_1/lib/libadd_static.a)
link_directories(D:/LLM/CMake_Learn/lesson2_1/lib)
add_executable(lesson2_1 main.cpp)
target_link_libraries(lesson2_1 libadd_static.a)
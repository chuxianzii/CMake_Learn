add_subdirectory(add)

include_directories(./bin)

#link_libraries(D:/LLM/CMake_Learn/lesson2_1/lib/libadd_static.a)
link_directories(D:/LLM/CMake_Learn/lesson2_2/bin)
add_executable(lesson2_2 main.cpp)
target_link_libraries(lesson2_2 libadd_shared.dll.a)
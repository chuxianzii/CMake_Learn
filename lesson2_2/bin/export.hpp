#pragma once

#ifdef EXPORT
#define CMAKE_LEARN_API __declspec(dllexport)
#else
#define CMAKE_LEARN_API __declspec(dllimport)
#endif
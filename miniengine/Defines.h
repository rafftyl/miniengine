#pragma once
#ifdef MINIENGINE_EXPORTS
#define MINI_API __declspec(dllexport)
#else
#define MINI_API __declspec(dllimport)
#endif

#pragma once

#ifdef KEYBOARDINSPECTOR_EXPORTS
#define KEYBOARDINSPECTOR_API __declspec(dllexport)
#else
#define KEYBOARDINSPECTOR_API __declspec(dllimport)
#endif
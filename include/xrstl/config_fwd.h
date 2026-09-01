#pragma once

#include "config.h"

#include "xrstldef.h"

// Function forward declarations. This is to avoid includes as one of our priorities is to make compile times
// very fast. Here we can do compiler checks, mangling, whatever we need to conform to the target compiler
// Some functions are well defined across compilers, whereas some are poorly defined such as memchr and wmemchr
// which is unfortunate. We'll provide our own implementations of these instead

#if defined(_MSC_VER)
	#define xrstl_dllimport __declspec(dllimport)

	#if _MSC_VER <= 1600
	#define xrstl_1600_dllimport __declspec(dllimport)
	#endif
#else
	#define xrstl_dllimport
#endif

#if !defined(xrstl_dllimport)
	#define xrstl_dllimport
#endif

#if !defined(xrstl_1600_dllimport)
	#define xrstl_1600_dllimport
#endif

extern "C"
{
	xrstl::size_t strlen(const char* str);
	void* memset(void* dst, int val, xrstl::size_t size);
	void* memcpy(void* destination, void const* source, xrstl::size_t size);

	xrstl_dllimport xrstl::size_t wcslen(const wchar_t* str);

	wchar_t* wmemset(wchar_t* ptr, wchar_t wc, xrstl::size_t num);

	xrstl_1600_dllimport void* memmove(void* destination, const void* source, xrstl::size_t num);

	xrstl_dllimport int tolower(int c);
	xrstl_dllimport int toupper(int c);
}
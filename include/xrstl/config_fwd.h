#pragma once

#include "config.h"

#include "xrstldef.h"

// Function forward declarations. This is to avoid includes as one of our priorities is to make compile times
// very fast. Here we can do compiler checks, mangling, whatever we need to conform to the target compiler

extern "C"
{
	// <string.h

	xrstl::size_t strlen(const char* str);

#if defined(_WIN32)
	__declspec(dllimport)
#endif
	xrstl::size_t wcslen(const wchar_t* str);

	void* memset(void* dst, int val, xrstl::size_t size);

	/*__declspec(dllimport)*/ const void* memchr(const void* ptr, int value, xrstl::size_t num);

	void* memcpy(void* destination, void const* source, xrstl::size_t size);

	/*__declspec(dllimport)*/ void* memmove(void* destination, const void* source, xrstl::size_t num);

	// <wchar.h>

	wchar_t* wmemset(wchar_t* ptr, wchar_t wc, xrstl::size_t num);

	const wchar_t* wmemchr(const wchar_t* ptr, wchar_t wc, xrstl::size_t num);
}

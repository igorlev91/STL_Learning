#pragma once

#if defined(_MSVC_LANG)

	#define xrstl_cppversion _MSVC_LANG

#elif defined(__cplusplus)

	#define xrstl_cppversion __cplusplus

#endif

#if defined(__clang__)

	#define xrstl_CLANG

#elif defined(__GNUG__)

	#define xrstl_GCC

#elif defined(_MSC_VER)

	#define xrstl_MSVC

#endif

#if defined(__clang__) || defined(__GNUG__)

	#define xrstl_finline inline __attribute__((always_inline))

#elif defined(_MSC_VER)

	#define xrstl_finline __forceinline

#endif

#if defined(__cpp_if_constexpr)

	#define xrstl_constexpr constexpr

#else

	#define xrstl_constexpr

#endif

#if defined(_MSC_VER) && _MSC_VER < 1900

	#define xrstl_noexcept

#else

	#define xrstl_noexcept noexcept

#endif

#define xrstl_nodiscard [[nodiscard]]

#if defined(__cpp_if_constexpr)

	#define xrstl_constexpr_if(x) if constexpr(x)

#else

	#if defined(_MSC_VER)
		
		// warning C4127: conditional expression is constant
		// Disable because we always use these in a template context
		// Builds that don't support constexpr optimize them away
		#define xrstl_constexpr_if(x) \
		__pragma(warning(push)) \
		__pragma(warning(disable : 4127)) \
		if(x) \
		__pragma(warning(pop))

	#else

		#define xrstl_constexpr_if(x) if(x)

	#endif

#endif

#if xrstl_cppversion == 201402L
	#define xrstl_VARIADIC_TEMPLATES
#endif

#define xrstl_ENABLE_ASSERT

#if defined(xrstl_ENABLE_ASSERT)

inline void xrstl_assert_impl(bool condition)
{
	if (!condition)
	{
		int* p = (int*)(int)(0xDEADBEEF);
		*p = 0;
	}
}

#define xrstl_assert(x) xrstl_assert_impl((x))

#else

#define xrstl_assert(x)

#endif

#if defined(_M_ARM) || defined(__arm__) || defined(_M_ARM64) || defined(__aarch64__)

	#define xrstl_ARM

#elif defined(_WIN32)

	#define xrstl_X86_64

#endif

#if defined(_WIN32)

	#define xrstl_WINDOWS

#elif defined(__linux__)

	#define xrstl_LINUX

#endif
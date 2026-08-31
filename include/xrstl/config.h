#pragma once

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

#define xrstl_ENABLE_ASSERT
#if __cplusplus == 201402L || _MSVC_LANG == 201402L
	#define xrstl_VARIADIC_TEMPLATES
#endif

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

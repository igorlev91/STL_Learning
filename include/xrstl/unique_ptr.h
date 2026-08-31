#pragma once

#include "xrstldef.h"

#include "config.h"

// unique_ptr
//
// This is a simple replacement for std::unique_ptr, functionally the same
// but with a very small compile time footprint
// The move-only semantics remain the same
//
// unique_ptr doesn't allocate memory, the pointer is supplied externally
// but it does deallocate memory, so care has to be take to allocate and 
// deallocate in a consistent manner

namespace xrstl
{
	template<typename T>
	class unique_ptr
	{
	public:

		typedef T element_type;

		xrstl_constexpr unique_ptr() xrstl_noexcept : m_ptr(nullptr) {}

		xrstl_constexpr explicit unique_ptr(T* ptr) xrstl_noexcept : m_ptr(ptr) {}

		xrstl_constexpr unique_ptr(xrstl::nullptr_t) xrstl_noexcept : m_ptr(nullptr) {}

		xrstl_constexpr unique_ptr(unique_ptr&& uptr) xrstl_noexcept
		{
			m_ptr = uptr.m_ptr;
			uptr.m_ptr = nullptr;
		}

		xrstl_constexpr unique_ptr& operator = (xrstl::nullptr_t) xrstl_noexcept
		{
			destroy();
			return *this;
		}

		xrstl_constexpr unique_ptr& operator = (unique_ptr&& uptr) xrstl_noexcept
		{
			m_ptr = uptr.m_ptr;
			uptr.m_ptr = nullptr;
			return *this;
		}

		xrstl_constexpr T* operator ->() const xrstl_noexcept
		{
			return m_ptr;
		}

		xrstl_constexpr ~unique_ptr() xrstl_noexcept
		{
			destroy();
		}

	private:

		xrstl_constexpr unique_ptr(const unique_ptr& uptr) xrstl_noexcept;
		xrstl_constexpr unique_ptr& operator = (const unique_ptr& uptr) xrstl_noexcept;
		xrstl_constexpr unique_ptr& operator = (T* ptr) xrstl_noexcept;

		void destroy() xrstl_noexcept
		{
			if (m_ptr)
			{
				delete m_ptr;
				m_ptr = nullptr;
			}
		}

		T* m_ptr;
	};
};
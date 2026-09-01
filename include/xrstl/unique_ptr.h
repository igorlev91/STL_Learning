#pragma once

#include "config.h"

#include "xrstldef.h"

#include "type_utils.h"

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
	template<typename UniquePtr, typename T>
	class unique_ptr_base
	{
	public:

		typedef T element_type;
		typedef T* pointer;

		xrstl_constexpr unique_ptr_base() xrstl_noexcept : m_ptr(nullptr) {}

		xrstl_constexpr explicit unique_ptr_base(T* ptr) xrstl_noexcept : m_ptr(ptr) {}

		xrstl_constexpr unique_ptr_base(xrstl::nullptr_t) xrstl_noexcept : m_ptr(nullptr) {}

		xrstl_constexpr unique_ptr_base(unique_ptr_base&& uptr) xrstl_noexcept
		{
			m_ptr = uptr.m_ptr;
			uptr.m_ptr = nullptr;
		}

		xrstl_constexpr unique_ptr_base& operator = (xrstl::nullptr_t) xrstl_noexcept
		{
			static_cast<UniquePtr&>(*this).reset(nullptr);
			return *this;
		}

		xrstl_constexpr unique_ptr_base& operator = (unique_ptr_base&& uptr) xrstl_noexcept
		{
			m_ptr = uptr.m_ptr;
			uptr.m_ptr = nullptr;
			return *this;
		}

		xrstl_constexpr T* operator ->() const xrstl_noexcept
		{
			return m_ptr;
		}

		bool operator!() const xrstl_noexcept
		{
			return (m_ptr == nullptr);
		}

		~unique_ptr_base() xrstl_noexcept
		{
			static_cast<UniquePtr&>(*this).reset(nullptr);
		}

		typedef T* (unique_ptr_base<UniquePtr, T>::* boolean)() const;

		operator boolean() const xrstl_noexcept
		{
			// Return anything that isn't easily castable but is guaranteed to be non-null, such as the get function pointer
			return m_ptr ? &unique_ptr_base<UniquePtr, T>::get : nullptr;
		}

		T* get() const
		{
			return m_ptr;
		}

		bool operator == (const unique_ptr_base& other) { return m_ptr == other.m_ptr; }
		bool operator != (const unique_ptr_base& other) { return m_ptr != other.m_ptr; }
		bool operator <  (const unique_ptr_base& other) { return m_ptr <  other.m_ptr; }
		bool operator <= (const unique_ptr_base& other) { return m_ptr <= other.m_ptr; }
		bool operator >  (const unique_ptr_base& other) { return m_ptr >  other.m_ptr; }
		bool operator >= (const unique_ptr_base& other) { return m_ptr >= other.m_ptr; }

		bool operator == (pointer ptr) { return m_ptr == ptr; }
		bool operator != (pointer ptr) { return m_ptr != ptr; }
		bool operator <  (pointer ptr) { return m_ptr <  ptr; }
		bool operator <= (pointer ptr) { return m_ptr <= ptr; }
		bool operator >  (pointer ptr) { return m_ptr >  ptr; }
		bool operator >= (pointer ptr) { return m_ptr >= ptr; }

		bool operator == (xrstl::nullptr_t) { return m_ptr == nullptr; }
		bool operator != (xrstl::nullptr_t) { return m_ptr != nullptr; }
		bool operator <  (xrstl::nullptr_t) { return m_ptr <  nullptr; }
		bool operator <= (xrstl::nullptr_t) { return m_ptr <= nullptr; }
		bool operator >  (xrstl::nullptr_t) { return m_ptr >  nullptr; }
		bool operator >= (xrstl::nullptr_t) { return m_ptr >= nullptr; }

	protected:

		pointer m_ptr;

	private:

		xrstl_constexpr unique_ptr_base(const unique_ptr_base& uptr) xrstl_noexcept;
		xrstl_constexpr unique_ptr_base& operator = (const unique_ptr_base& uptr) xrstl_noexcept;
		xrstl_constexpr unique_ptr_base& operator = (T* ptr) xrstl_noexcept;
	};

	// unique_ptr for scalar types

	template<typename T>
	class unique_ptr : public unique_ptr_base<unique_ptr<T>, T>
	{
	public:

		typedef unique_ptr_base<unique_ptr<T>, T> base;

		xrstl_constexpr unique_ptr() xrstl_noexcept : base() {}

		xrstl_constexpr explicit unique_ptr(T* ptr) xrstl_noexcept : base(ptr) {}

		xrstl_constexpr unique_ptr(xrstl::nullptr_t) xrstl_noexcept : base(nullptr) {}

		xrstl_constexpr unique_ptr(unique_ptr&& uptr) xrstl_noexcept : base(xrstl::move(uptr)) {}

		xrstl_constexpr unique_ptr& operator = (xrstl::nullptr_t) xrstl_noexcept { base::operator = (nullptr); return *this; }

		xrstl_constexpr unique_ptr& operator = (unique_ptr&& uptr) xrstl_noexcept { base::operator = (xrstl::move(uptr)); return *this; }

		xrstl_constexpr void reset(xrstl::nullptr_t) xrstl_noexcept
		{
			delete base::m_ptr;
			base::m_ptr = nullptr;
		}

		xrstl_constexpr void reset(typename base::pointer ptr = base::pointer()) xrstl_noexcept
		{
			delete base::m_ptr;
			base::m_ptr = ptr;
		}
	};

	// unique_ptr for arrays

	template<typename T>
	class unique_ptr<T[]> : public unique_ptr_base<unique_ptr<T[]>, T>
	{
	public:

		typedef unique_ptr_base<unique_ptr<T[]>, T> base;

		xrstl_constexpr unique_ptr() xrstl_noexcept : base() {}

		xrstl_constexpr explicit unique_ptr(T* ptr) xrstl_noexcept : base(ptr) {}

		xrstl_constexpr unique_ptr(xrstl::nullptr_t) xrstl_noexcept : base(nullptr) {}

		xrstl_constexpr unique_ptr(unique_ptr&& uptr) xrstl_noexcept : base(xrstl::move(uptr)) {}

		xrstl_constexpr unique_ptr& operator = (xrstl::nullptr_t) xrstl_noexcept { base::operator = (nullptr); return *this; }

		xrstl_constexpr unique_ptr& operator = (unique_ptr&& uptr) xrstl_noexcept { base::operator = (xrstl::move(uptr)); return *this; }

		xrstl_constexpr void reset(xrstl::nullptr_t) xrstl_noexcept
		{
			delete[] base::m_ptr;
			base::m_ptr = nullptr;
		}

		xrstl_constexpr void reset(typename base::pointer ptr = base::pointer()) xrstl_noexcept
		{
			delete[] base::m_ptr;
			base::m_ptr = ptr;
		}
	};
};
#pragma once

#include "config.h"

#include "xrstldef.h"

#include "string_common.h"

namespace xrstl
{
	template<typename T>
	class basic_string_view
	{
	public:

		typedef T        value_type;
		typedef T&       reference;
		typedef const T& const_reference;
		typedef T*       pointer;
		typedef const T* const_pointer;
		typedef const T* iterator;
		typedef const T* const_iterator;
		typedef size_t   size_type;

		static const xrstl_constexpr size_type npos = (size_type)-1;

		basic_string_view() xrstl_noexcept : m_data(nullptr), m_length(0) {}

		basic_string_view(const_pointer ptr) xrstl_noexcept : m_data(ptr), m_length(string_length(ptr)) {}

		basic_string_view(const_pointer ptr, size_type size) : m_data(ptr), m_length(size) {}

		basic_string_view(const_pointer begin, const_pointer end) : m_data(begin), m_length(end - begin) {}

		xrstl_constexpr reference at(size_type i) xrstl_noexcept
		{
			xrstl_assert(i < m_length);
			return m_data[i];
		}

		xrstl_constexpr const_reference at(size_type i) const xrstl_noexcept
		{
			xrstl_assert(i < m_length);
			return m_data[i];
		}

		xrstl_constexpr reference back() xrstl_noexcept
		{
			xrstl_assert(m_length > 0);
			return m_data[m_length - 1];
		}

		xrstl_constexpr const_reference back() const xrstl_noexcept
		{
			xrstl_assert(m_length > 0);
			return m_data[m_length - 1];
		}

		xrstl_constexpr iterator begin() xrstl_noexcept { return m_data; }
		xrstl_constexpr const_iterator begin() const xrstl_noexcept { return m_data; }

		xrstl_constexpr const_iterator cbegin() const xrstl_noexcept { return m_data; }
		xrstl_constexpr const_iterator cend() const xrstl_noexcept { return m_data + m_length; }

		xrstl_constexpr int compare(const basic_string_view& sv) const xrstl_noexcept
		{
			return xrstl::string_compare(m_data, m_length, sv.m_data, sv.m_length);
		}

		xrstl_constexpr pointer data() xrstl_noexcept { return m_data; }
		xrstl_constexpr const_pointer data() const xrstl_noexcept { return m_data; }

		xrstl_constexpr bool empty() const xrstl_noexcept { return m_length == 0; }

		xrstl_constexpr iterator end() xrstl_noexcept { return m_data + m_length; }
		xrstl_constexpr const_iterator end() const xrstl_noexcept { return m_data + m_length; }

		xrstl_constexpr bool ends_with(value_type c) { return find(c, 0) == (m_length - 1); }

		xrstl_constexpr bool ends_with(const basic_string_view& sv) { return find(sv.m_data, m_length - sv.m_length) == (m_length - sv.m_length); }

		//-----
		// find
		//-----

		size_t find(value_type c, size_t pos = 0) const xrstl_noexcept
		{
			xrstl_assert(pos < m_length);
			const_pointer ptr = (const_pointer)string_find_char(m_data + pos, c, m_length - pos);
			return ptr ? (size_t)(ptr - m_data) : npos;
		}

		size_t find(const_pointer needle_string, size_t pos, size_t needle_length) const xrstl_noexcept
		{
			xrstl_assert(pos < m_length);

			const_pointer found_string = string_find(m_data + pos, m_length - pos, needle_string, needle_length);

			if (found_string)
			{
				return (size_t)(found_string - m_data);
			}
			else
			{
				return npos;
			}
		}

		size_t find(const_pointer needle_string, size_t pos = 0) const xrstl_noexcept
		{
			return find(needle_string, pos, string_length(needle_string));
		}

		size_t find(const basic_string_view& needle_sv, size_t pos = 0) const xrstl_noexcept
		{
			return find(needle_sv.m_data, pos, needle_sv.m_length);
		}

		xrstl_constexpr reference front() xrstl_noexcept { m_data; }
		xrstl_constexpr const_reference front() const xrstl_noexcept { m_data; }

		// Returns the length of the string, in terms of number of characters
		xrstl_constexpr size_type length() const xrstl_noexcept { return m_length; }

		xrstl_constexpr size_type max_size() const xrstl_noexcept { return (size_type)-1; }

		xrstl_constexpr size_type size() const xrstl_noexcept { return length(); }

		xrstl_constexpr bool starts_with(value_type c) { return find(c, 0) == 0; }

		xrstl_constexpr bool starts_with(const basic_string_view& sv) { return find(sv.m_data, 0) == 0; }

		xrstl_constexpr basic_string_view substr(size_t pos, size_t length = npos) const xrstl_noexcept
		{
			xrstl_assert(pos < m_length);
			return basic_string_view(m_data + pos, clamp_length(pos, length));
		}

		//----------
		// Operators
		//----------

		xrstl_constexpr reference operator [](size_type i)
		{
			xrstl_assert(i < m_length);
			return m_data[i];
		}

		xrstl_constexpr const_reference operator [](size_type i) const xrstl_noexcept
		{
			xrstl_assert(i < m_length);
			return m_data[i];
		}

		xrstl_constexpr bool operator == (const basic_string_view& sv) xrstl_noexcept
		{
			return compare(sv) == 0;
		}

		xrstl_constexpr bool operator != (const basic_string_view& sv) xrstl_noexcept
		{
			return compare(sv) != 0;
		}

	private:

		// Given a position and a length, return the length that fits the string
		xrstl_constexpr size_type clamp_length(size_type pos, size_type length) const xrstl_noexcept
		{
			return xrstl::string_clamp_length(m_length, pos, length);
		}

		const_pointer m_data;

		size_type m_length;
	};

	typedef basic_string_view<char> string_view;

	typedef basic_string_view<wchar_t> wstring_view;
};
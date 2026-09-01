#pragma once

#include "config.h"

#include "xrstldef.h"

namespace xrstl
{
	template<typename T, size_t N = 1>
	class array
	{
	public:

		xrstl_constexpr T* begin() { return m_data; }
		xrstl_constexpr const T* begin() const { return m_data; }
		xrstl_constexpr const T* cbegin() const { return m_data; }

		xrstl_constexpr T* end() { return m_data + N; }
		xrstl_constexpr const T* end() const { return m_data + N; }
		xrstl_constexpr const T* cend() const { return m_data + N; }

		xrstl_constexpr bool empty() const { return N == 0; }
		xrstl_constexpr size_t size() const { return N; }
		xrstl_constexpr size_t max_size() const { return N; }

		xrstl_constexpr T* data() { return m_data; }
		xrstl_constexpr T* const data() const { return m_data; }

		xrstl_constexpr T& operator[](size_t i) { return m_data[i]; }
		xrstl_constexpr const T& operator[](size_t i) const { return m_data[i]; }

		xrstl_constexpr T& at(size_t i) { return m_data[i]; }
		xrstl_constexpr const T& at(size_t i) const { return m_data[i]; }

		// Public to allow braced initialization
		T m_data[N ? N : 1];
	};
}
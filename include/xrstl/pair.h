#pragma once

#include "config.h"

#include "type_utils.h"

namespace xrstl
{
	template<typename T1, typename T2>
	class pair
	{
	public:

		typedef T1 first_type;
		typedef T2 second_type;

		xrstl_constexpr pair() xrstl_noexcept : first(T1()), second(T2()) {}
		xrstl_constexpr pair(const T1& first, const T2& second) xrstl_noexcept : first(first), second(second) {}
		xrstl_constexpr pair(const T1& first, T2&& second) xrstl_noexcept : first(first), second(xrstl::move(second)) {}
		xrstl_constexpr pair(T1&& first, const T2& second) xrstl_noexcept : first(xrstl::move(first)), second(second) {}
		xrstl_constexpr pair(T1&& first, T2&& second) xrstl_noexcept : first(xrstl::move(first)), second(xrstl::move(second)) {}

		template<typename O1, typename O2>
		xrstl_constexpr pair(const O1& first, const O2& second) xrstl_noexcept : first(first), second(second) {}

		template<typename O1, typename O2>
		xrstl_constexpr pair(O1&& first, O2&& second) xrstl_noexcept : first(xrstl::forward<O1>(first)), second(xrstl::forward<O2>(second)) {}

		template<typename O1, typename O2>
		xrstl_constexpr pair(const pair<O1, O2>& other) xrstl_noexcept : first(other.first), second(other.second) {}

		template<typename O1, typename O2>
		xrstl_constexpr pair(pair<O1, O2>&& other) xrstl_noexcept : first(xrstl::forward<O1>(other.first)), second(xrstl::forward<O2>(other.second)) {}

		xrstl_constexpr bool operator == (const pair& other) const { return first == other.first && second == other.second; }
		xrstl_constexpr bool operator != (const pair& other) const { return !(*this == other); }
		xrstl_constexpr bool operator < (const pair& other) const { return first < other.first || (!(first < other.first) && second < other.second); }
		xrstl_constexpr bool operator <= (const pair& other) const { return !(other < *this); }
		xrstl_constexpr bool operator > (const pair& other) const { return other < *this; }
		xrstl_constexpr bool operator >= (const pair& other) const { return !(*this < other); }

		T1 first;
		T2 second;
	};

	template<typename T1, typename T2>
	xrstl_constexpr pair<T1, T2> make_pair(T1&& first, T2&& second)
	{
		return pair<T1, T2>(first, second);
	}
};
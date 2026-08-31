#pragma once

#include "config.h"

namespace xrstl
{
	template <typename T> struct remove_reference { typedef T type; };

	template <typename T> struct remove_reference<T&> { typedef T type; };

	template <typename T> struct remove_reference<T&&> { typedef T type; };

	template <typename T>
	xrstl_constexpr T&& forward(typename xrstl::remove_reference<T>::type& x) xrstl_noexcept
	{
		return static_cast<T&&>(x);
	}

	template <typename T>
	xrstl_constexpr typename xrstl::remove_reference<T>::type&& move(T&& x) xrstl_noexcept
	{
		return static_cast<typename xrstl::remove_reference<T>::type&&>(x);
	}

	// Swap for standard values
	template <typename T>
	xrstl_constexpr static void swap(T& a, T& b) xrstl_noexcept
	{
		T temp(xrstl::move(a));
		a = xrstl::move(b);
		b = xrstl::move(temp);
	}

	template <class Iter1, class Iter2>
	xrstl_constexpr void iter_swap(Iter1 left, Iter2 right) xrstl_noexcept
	{
		swap(*left, *right);
	}

	// This swap is specific for arrays
	template<typename T, int N>
	xrstl_constexpr void swap(T(&left)[N], T(&right)[N]) xrstl_noexcept
	{
		if (&left != &right)
		{
			T* iterLeft = left;
			T* endLeft = left + N;
			T* iterRight = right;
			while (iterLeft != endLeft)
			{
				xrstl::iter_swap(iterLeft, iterRight); // Swap the pointers
				++iterLeft;
				++iterRight;
			}
		}
	}
};
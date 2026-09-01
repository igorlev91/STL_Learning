#pragma once

#include "config.h"

#include "xrstldef.h"

namespace xrstl
{
	// true_type/false_type

	template<typename T, T Value>
	struct integral_constant { static const T value = Value; };

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	// remove_x

	template <typename T> struct remove_reference { typedef T type; };

	template <typename T> struct remove_reference<T&> { typedef T type; };

	template <typename T> struct remove_reference<T&&> { typedef T type; };

	template <typename T>           struct remove_const { typedef T type; };
	template <typename T>           struct remove_const<const T> { typedef T type; };
	template <typename T>           struct remove_const<const T[]> { typedef T type[]; };
	template <typename T, size_t N> struct remove_const<const T[N]> { typedef T type[N]; };

	template <typename T>           struct remove_volatile { typedef T type; };
	template <typename T>           struct remove_volatile<volatile T> { typedef T type; };
	template <typename T>           struct remove_volatile<volatile T[]> { typedef T type[]; };
	template <typename T, size_t N> struct remove_volatile<volatile T[N]> { typedef T type[N]; };

	template <typename T> struct remove_cv { typedef typename xrstl::remove_volatile<typename xrstl::remove_const<T>::type>::type type; };

	// enable_if

	template<bool Test, typename T = void> struct enable_if;
	template<typename T> struct enable_if<true, T> { typedef T type; };

	// conditional

	template<bool Test, typename T1, typename T2> struct conditional { typedef T2 type; }; // Type is T2 when Test is false
	template<typename T1, typename T2> struct conditional<true, T1, T2> { typedef T1 type; }; // Type is T1 when Test is true
	
	// is_array

	template<typename T> struct is_array : false_type {};
	template<typename T, size_t N> struct is_array<T[N]> : true_type {};
	template<typename T> struct is_array<T[]> : true_type {};

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

	// Swap for iterators
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
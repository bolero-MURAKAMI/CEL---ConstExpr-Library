// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_CSTDLIB_HPP)
#define SSCRISK_CEL_CSTDLIB_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// cstdlib.hpp

// ref: C   JISX3010：2003 (ISO/IEC 9899：1999) 7.20
//      C++ ISO/IEC FDIS 14882 N3290 26.8

#include<cstdlib>
#include<cstddef>
#include<type_traits>

namespace sscrisk{ namespace cel{

// 7.20.6.1  abs，labs，及び llabs 関数
constexpr int abs(int j)
{
 return j < 0 ? -j : j;
}

constexpr long labs(long j)
{
 return j < 0 ? -j : j;
}

constexpr long long llabs(long long j)
{
 return j < 0 ? -j : j;
}

constexpr long abs(long j)
{
 return labs(j);
}

constexpr long long abs(long long j)
{
 return llabs(j);
}

namespace detail{

#define DIV_T_TRAITS_IMPL(DIV_T) typedef DIV_T type;                    \
 static constexpr std::size_t offsetof_quot = offsetof(DIV_T, quot),    \
  offsetof_rem = offsetof(DIV_T, rem)

template<class T>struct div_t_traits{};
template<>struct div_t_traits<int>{DIV_T_TRAITS_IMPL(std::div_t);};
template<>struct div_t_traits<long>{DIV_T_TRAITS_IMPL(std::ldiv_t);};
template<>struct div_t_traits<long long>{DIV_T_TRAITS_IMPL(std::lldiv_t);};

#undef DIV_T_TRAITS_IMPL

extern void* enabler;

template<class T, typename std::enable_if<div_t_traits<T>::offsetof_quot == 0>::type*& = enabler>
constexpr typename div_t_traits<T>::type div_impl(T const & numer, T const & denom)
{
 return {numer / denom, numer % denom};
}

template<class T, typename std::enable_if<div_t_traits<T>::offsetof_rem == 0>::type*& = enabler>
constexpr typename div_t_traits<T>::type div_impl(T const & numer, T const & denom)
{
 return {numer % denom, numer / denom};
}

}

// 7.20.6.2  div，ldiv，及び lldiv 関数
constexpr std::div_t div(int numer, int denom)
{
 return detail::div_impl(numer, denom);
}

constexpr std::ldiv_t ldiv(long numer, long denom)
{
 return detail::div_impl(numer, denom);
}

constexpr std::lldiv_t lldiv(long long  numer, long long denom)
{
 return detail::div_impl(numer, denom);
}

constexpr std::ldiv_t div(long numer, long denom)
{
 return ldiv(numer, denom);
}

constexpr std::lldiv_t div(long long numer, long long denom)
{
 return lldiv(numer, denom);
}

}}

#endif

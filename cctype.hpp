// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_CCTYPE_HPP)
#define SSCRISK_CEL_CCTYPE_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// cctype.hpp

// ref: C   JISX3010：2003 (ISO/IEC 9899：1999) 7.4
//      C++ ISO/IEC FDIS 14882 N3290 21.7

// Supported only ASCII.

#include<cstdio>
#include<limits>
#include<stdexcept>

namespace sscrisk{ namespace cel{

namespace detail{

constexpr unsigned alpha = 1 << 0;
constexpr unsigned blank = 1 << 1;
constexpr unsigned cntrl = 1 << 2;
constexpr unsigned digit = 1 << 3;
constexpr unsigned graph = 1 << 4;
constexpr unsigned lower = 1 << 5;
constexpr unsigned print = 1 << 6;
constexpr unsigned punct = 1 << 7;
constexpr unsigned space = 1 << 8;
constexpr unsigned upper = 1 << 9;
constexpr unsigned xdigit = 1 << 10;
constexpr unsigned table[] = {
#include<sscrisk/cel/ascii.inl>
};

constexpr int type(int c)
{
 return 0x0 <= c && c <= 0x7F ? table[c]
  : (0x80 <= c && c <= std::numeric_limits<unsigned char>::max()) || c == EOF ? 0
  : throw std::out_of_range("Out of unsigned char range [0x0, std::numeric_limits<unsigned char>::max()]");
}

}

constexpr int isalpha(int);
constexpr int isdigit(int);

// 7.4.1.1 The isalnum function
constexpr int isalnum(int c)
{
 return isalpha(c) || isdigit(c);
}

// 7.4.1.2 The isalpha function
constexpr int isalpha(int c)
{
 return detail::type(c) & detail::alpha;
}

// 7.4.1.3 The isblank function
constexpr int isblank(int c)
{
 return detail::type(c) & detail::blank;
}

// 7.4.1.4 The iscntrl function
constexpr int iscntrl(int c)
{
 return detail::type(c) & detail::cntrl;
}

// 7.4.1.5 The isdigit function
constexpr int isdigit(int c)
{
 return detail::type(c) & detail::digit;
}

// 7.4.1.6 The isgraph function
constexpr int isgraph(int c)
{
 return detail::type(c) & detail::graph;
}

// 7.4.1.7 The islower function
constexpr int islower(int c)
{
 return detail::type(c) & detail::lower;
}

// 7.4.1.8 The isprint function
constexpr int isprint(int c)
{
 return detail::type(c) & detail::print;
}

// 7.4.1.9 The ispunct function
constexpr int ispunct(int c)
{
 return detail::type(c) & detail::punct;
}

// 7.4.1.10 The isspace function
constexpr int isspace(int c)
{
 return detail::type(c) & detail::space;
}

// 7.4.1.11 The isupper function
constexpr int isupper(int c)
{
 return detail::type(c) & detail::upper;
}

// 7.4.1.12 The isxdigit function
constexpr int isxdigit(int c)
{
 return detail::type(c) & detail::xdigit;
}

// 7.4.2.1 The tolower function
constexpr int tolower(int c)
{
 return isupper(c) ? c + (0x61/* 'a' */ - 0x41/* 'A' */) : c;
}

// 7.4.2.2 The toupper function
constexpr int toupper(int c)
{
 return islower(c) ? c - (0x61/* 'a' */ - 0x41/* 'A' */) : c;
}

}}

#endif

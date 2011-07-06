// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_STRING_HPP)
#define SSCRISK_CEL_STRING_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// string.hpp

#include<cstddef>

namespace sscrisk{ namespace cel{

  namespace detail{

   constexpr int memcmp_impl(unsigned char const * s1, unsigned char const * s2, std::size_t n)
   {
    return !n ? 0
     : *s1 == *s2 ? memcmp_impl(s1 + 1, s2 + 1, n - 1)
     : *s1 - *s2;
   }

  }

  // 7.21.4.1  memcmp 関数
  constexpr int memcmp(void const *s1, void const *s2, std::size_t n)
  {
   return detail::memcmp_impl((unsigned char const *)s1, (unsigned char const *)s2, n);
  }

  // 7.21.4.2  strcmp 関数
  constexpr int strcmp(const char *s1, const char *s2)
  {
   return !*s1 && !*s2 ? 0
    : !*s1 ? -1
    : !*s2 ? 1
    : *s1 == *s2 ? strcmp(s1 + 1, s2 + 1)
    : (unsigned char)*s1 - (unsigned char)*s2;
  }

  // 7.21.4.3  strcoll 関数
  constexpr int strcoll(const char *s1, const char *s2)
  {
   return strcmp(s1, s2);
  }

  // 7.21.4.4  strncmp 関数
  constexpr int strncmp(const char *s1, const char *s2, std::size_t n)
  {
   return !n || (!*s1 && !*s2) ? 0
    : !*s1 ? -1
    : !*s2 ? 1
    : *s1 == *s2 ? strncmp(s1 + 1, s2 + 1, n - 1)
    : (unsigned char)*s1 - (unsigned char)*s2;
  }

  namespace detail{

   constexpr void const * memchr_impl(unsigned char const * s, char c, std::size_t n)
   {
    return !n ? 0
     : *s == c ? s
     : memchr_impl(s + 1, c, n - 1);
   }

  }

  // 7.21.5.1  memchr 関数
  constexpr void const * memchr(void const * s, int c, size_t n)
  {
   return detail::memchr_impl(static_cast<unsigned char const *>(s), static_cast<unsigned char>(c), n);
  }

  constexpr void* memchr(void* s, int c, size_t n)
  {
   return const_cast<void*>(detail::memchr_impl(static_cast<unsigned char*>(s), static_cast<unsigned char>(c), n));
  }

  // 7.21.5.2  strchr 関数
  inline constexpr const char* strchr(const char* s, int c)
  {
   return *s == static_cast<char>(c) ? s
    : !*s ? nullptr
    : strchr(s + 1, c);
  }

  inline constexpr char* strchr(char* s, int c)
  {
   return const_cast<char*>(strchr(const_cast<char const *>(s), c));
  }

}}

#endif

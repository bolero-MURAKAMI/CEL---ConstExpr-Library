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

// ref: C   JISX3010：2003 (ISO/IEC 9899：1999) 7.21
//      C++ ISO/IEC FDIS 14882 N3290 21.7

#include<cstddef>

namespace sscrisk{ namespace cel{

  namespace detail{

   inline constexpr int memcmp_impl(unsigned char const * s1, unsigned char const * s2, std::size_t n)
   {
    return !n ? 0
     : *s1 == *s2 ? memcmp_impl(s1 + 1, s2 + 1, n - 1)
     : *s1 - *s2;
   }

  }

  // 7.21.4.1  memcmp 関数
  inline constexpr int memcmp(void const *s1, void const *s2, std::size_t n)
  {
   return detail::memcmp_impl((unsigned char const *)s1, (unsigned char const *)s2, n);
  }

  // 7.21.4.2  strcmp 関数
  inline constexpr int strcmp(const char *s1, const char *s2)
  {
   return !*s1 && !*s2 ? 0
    : !*s1 ? -1
    : !*s2 ? 1
    : *s1 == *s2 ? strcmp(s1 + 1, s2 + 1)
    : (unsigned char)*s1 - (unsigned char)*s2;
  }

  // 7.21.4.3  strcoll 関数
  inline constexpr int strcoll(const char *s1, const char *s2)
  {
   return strcmp(s1, s2);
  }

  // 7.21.4.4  strncmp 関数
  inline constexpr int strncmp(const char *s1, const char *s2, std::size_t n)
  {
   return !n || (!*s1 && !*s2) ? 0
    : !*s1 ? -1
    : !*s2 ? 1
    : *s1 == *s2 ? strncmp(s1 + 1, s2 + 1, n - 1)
    : (unsigned char)*s1 - (unsigned char)*s2;
  }

  namespace detail{

   inline constexpr void const * memchr_impl(unsigned char const * s, char c, std::size_t n)
   {
    return !n ? 0
     : *s == c ? s
     : memchr_impl(s + 1, c, n - 1);
   }

  }

  // 7.21.5.1  memchr 関数
  inline constexpr void const * memchr(void const * s, int c, size_t n)
  {
   return detail::memchr_impl(static_cast<unsigned char const *>(s), static_cast<unsigned char>(c), n);
  }

  inline constexpr void* memchr(void* s, int c, size_t n)
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

  namespace detail{

   inline constexpr std::size_t strcspn_impl(char const * s1, char const * s2, std::size_t n)
   {
    return !*s1 || strchr(s2, *s1) ? n
     : strcspn_impl(s1 + 1, s2, n + 1);
   }

  }

  // 7.21.5.3  strcspn 関数
  inline constexpr std::size_t strcspn(const char *s1, const char *s2)
  {
   return detail::strcspn_impl(s1, s2, 0);
  }

  // 7.21.5.4  strpbrk 関数
  inline constexpr const char* strpbrk(const char* s1, const char* s2)
  {
   return !*s1 ? nullptr
    : strchr(s2, *s1) ? s1
    : strpbrk(s1 + 1, s2);
  }

  inline constexpr char* strpbrk(char* s1, const char* s2)
  {
   return const_cast<char*>(strpbrk(const_cast<char const *>(s1), s2));
  }

  // 7.21.5.5  strrchr 関数
  inline constexpr const char* strrchr(const char* s, int c)
  {
   return *s == static_cast<char>(c) && (!*s || !strrchr(s + 1, c))? s
    : !*s ? nullptr
    : strrchr(s + 1, c);
  }

  inline constexpr char* strrchr(char* s, int c)
  {
   return const_cast<char*>(strrchr(const_cast<char const *>(s), c));
  }

  namespace detail{

   inline constexpr std::size_t strspn_impl(char const * s1, char const * s2, std::size_t n)
   {
    return !*s1 || !strchr(s2, *s1) ? n
     : strspn_impl(s1 + 1, s2, n + 1);
   }

  }

  // 7.21.5.6  strspn 関数
  inline constexpr std::size_t strspn(const char *s1, const char *s2)
  {
   return detail::strspn_impl(s1, s2, 0);
  }

  // 7.21.5.7  strstr 関数
  inline constexpr const char* strstr(const char* s1, const char* s2)
  {
   return !*s2 ? s1
    : !*s1 ? nullptr
    : *s1 == *s2 && strstr(s1 + 1, s2 + 1) ? s1
    : strstr(s1 + 1, s2);
  }

  inline constexpr char* strstr(char* s1, const char* s2)
  {
   return const_cast<char*>(strstr(const_cast<char const *>(s1), s2));
  }

  namespace detail{

   inline constexpr std::size_t strlen_impl(char const * s, std::size_t n)
   {
    return !*s ? n : strlen_impl(s + 1, n + 1);
   }

  }

  // 7.21.6.3  strlen 関数
  inline constexpr std::size_t strlen(const char *s)
  {
   return detail::strlen_impl(s, 0);
  }

}}

#endif

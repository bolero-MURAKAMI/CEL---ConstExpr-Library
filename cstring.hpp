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
  constexpr int memcmp(const void *s1, const void *s2, std::size_t n)
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
}}

#endif

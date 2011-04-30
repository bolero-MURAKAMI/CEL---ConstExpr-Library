// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_UTILITY_HPP)
#define SSCRISK_CEL_UTILITY_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// utility.hpp

namespace sscrisk{ namespace cel{

  template <class T1, class T2>
  struct pair
  {
   typedef T1 first_type;
   typedef T2 second_type;
   T1 first;
   T2 second;
   constexpr pair(const pair&) = default;
   constexpr pair()
    : first(), second()
   {}
   constexpr pair(const T1& x, const T2& y)
    : first(x), second(y)
   {}
   template<class U, class V>
   constexpr pair(const pair<U, V>& p)
    : first(p.first), second(p.second)
   {}
  };

}}


#endif

// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_ITERATOR_HPP)
#define SSCRISK_CEL_ITERATOR_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// iterator.hpp

#include<iterator>

namespace sscrisk{ namespace cel{

  // 24.4.4 Iterator operations
  template<class Iterator>
  constexpr typename std::iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last)
  {
   return first == last ? 0 : 1 + distance(first + 1, last);
  }

}}

#endif

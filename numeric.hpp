// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_NUMERIC_HPP)
#define SSCRISK_CEL_NUMERIC_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// numeric.hpp

#include<iterator>
#include<sscrisk/cel/functional.hpp>

namespace sscrisk{ namespace cel{

  // 26.7.2 Accumulate
  template<class Iterator, class T>
  constexpr T accumulate(Iterator first, Iterator last, T init)
  {
   return accumulate(first, last, init, plus<typename std::iterator_traits<Iterator>::value_type>());
  }

  template<class Iterator, class T, class BinaryOperation>
  constexpr T accumulate(Iterator first, Iterator last, T init, BinaryOperation binary_op)
  {
   return first == last ? init : accumulate(first + 1, last, binary_op(init, *first), binary_op);
  }

}}

#endif

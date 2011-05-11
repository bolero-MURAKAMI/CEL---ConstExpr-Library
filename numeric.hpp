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

  // 26.7.3 Inner product
  template<class Iterator1, class Iterator2, class T>
  constexpr T inner_product(Iterator1 first1, Iterator1 last1, Iterator2 first2, T init)
  {
   return inner_product(first1, last1, first2, init,
                        plus<typename std::iterator_traits<Iterator1>::value_type>(),
                        multiplies<typename std::iterator_traits<Iterator1>::value_type>());
  }

  template<class Iterator1, class Iterator2, class T, class BinaryOperation1, class BinaryOperation2>
  constexpr T inner_product(Iterator1 first1, Iterator1 last1, Iterator2 first2, T init,
                            BinaryOperation1 binary_op1, BinaryOperation2 binary_op2)
  {
   return first1 == last1 ? init
    : inner_product(first1 + 1, last1, first2 + 1, binary_op1(init, binary_op2(*first1, *first2)),
                    binary_op1, binary_op2);
  }

}}

#endif

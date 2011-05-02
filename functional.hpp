// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_FUNCTIONAL_ITERATOR_HPP)
#define SSCRISK_CEL_FUNCTIONAL_ITERATOR_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// iterator.hpp

#include<functional>

namespace sscrisk{ namespace cel{

  // 20.8.5, comparisons:
  template <class T> struct equal_to
  {
   constexpr bool operator()(const T& x, const T& y) const
   {
    return x == y;
   }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class Fn>
  class binder2nd : public std::unary_function<typename Fn::first_argument_type, typename Fn::result_type>
  {
  protected:
   Fn op;
   typename Fn::second_argument_type value;
  public:
   constexpr binder2nd(const Fn& x, const typename Fn::second_argument_type& y)
    : op(x), value(y)
   {}
   constexpr typename Fn::result_type operator()(const typename Fn::first_argument_type& x)const
   {
    return op(x, value);
   }
  };

  template <class Fn, class T>
  constexpr binder2nd<Fn> bind2nd(const Fn& op, const T& x)
  {
   return binder2nd<Fn>(op, typename Fn::second_argument_type(x));
  }

}}

#endif

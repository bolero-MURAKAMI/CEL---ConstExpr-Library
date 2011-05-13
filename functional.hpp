// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_FUNCTIONAL_HPP)
#define SSCRISK_CEL_FUNCTIONAL_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// functional.hpp

#include<functional>

namespace sscrisk{ namespace cel{

  // 20.8.4 Arithmetic operations
  template<class T>
  struct plus
  {
   constexpr T operator()(T const & x, T const & y)const{ return x + y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T result_type;
  };

  template<class T>
  struct minus
  {
   constexpr T operator()(T const & x, T const & y)const{ return x - y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T result_type;
  };

  template<class T>
  struct multiplies
  {
   constexpr T operator()(T const & x, T const & y)const{ return x * y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T result_type;
  };

  template<class T>
  struct divides
  {
   constexpr T operator()(T const & x, T const & y)const{ return x / y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T result_type;
  };

  template<class T>
  struct modulus
  {
   constexpr T operator()(T const & x, T const & y)const{ return x % y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T result_type;
  };

  template<class T>
  struct negate
  {
   constexpr T operator()(T const & x)const{ return -x; }
   typedef T argument_type;
   typedef T result_type;
  };

  // 20.8.5 Comparisons
  template<class T>
  struct equal_to
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x == y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class T>
  struct not_equal_to
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x != y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class T>
  struct greater
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x > y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class T>
  struct less
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x < y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class T>
  struct greater_equal
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x >= y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  template<class T>
  struct less_equal
  {
   constexpr bool operator()(T const & x, T const & y)const{ return x <= y; }
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef bool result_type;
  };

  // D.9.1 Class template binder1st
  template<class Fn>
  class binder1st : public std::unary_function<typename Fn::second_argument_type, typename Fn::result_type>
  {
  protected:
   Fn op;
   typename Fn::first_argument_type value;
  public:
   constexpr binder1st(Fn const & x, typename Fn::first_argument_type const & y)
    : op(x), value(y)
   {}
   constexpr typename Fn::result_type operator()(typename Fn::second_argument_type const & x)const
   {
    return op(value, x);
   }
  };

  // D.9.2 bind1st
  template<class Fn, class T>
  constexpr binder1st<Fn> bind1st(Fn const & fn, T const & x)
  {
   return binder1st<Fn>(fn, typename Fn::first_argument_type(x));
  }

  // D.9.3 Class template binder2nd
  template<class Fn>
  class binder2nd : public std::unary_function<typename Fn::first_argument_type, typename Fn::result_type>
  {
  protected:
   Fn op;
   typename Fn::second_argument_type value;
  public:
   constexpr binder2nd(Fn const & x, typename Fn::second_argument_type const & y)
    : op(x), value(y)
   {}
   constexpr typename Fn::result_type operator()(typename Fn::first_argument_type const & x)const
   {
    return op(x, value);
   }
  };

  // D.9.4 bind2nd
  template<class Fn, class T>
  constexpr binder2nd<Fn> bind2nd(Fn const & op, T const & x)
  {
   return binder2nd<Fn>(op, typename Fn::second_argument_type(x));
  }

}}

#endif

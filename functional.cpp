// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/functional.hpp>

int main()
{
 using namespace sscrisk::cel;
 {
  constexpr auto arithmetic = plus<int>();
  assert(arithmetic(7, 3) == 10);
 }
 {
  constexpr auto arithmetic = minus<int>();
  assert(arithmetic(7, 3) == 4);
 }
 {
  constexpr auto arithmetic = multiplies<int>();
  assert(arithmetic(7, 3) == 21);
 }
 {
  constexpr auto arithmetic = divides<int>();
  assert(arithmetic(7, 3) == 2);
 }
 {
  constexpr auto arithmetic = modulus<int>();
  assert(arithmetic(7, 3) == 1);
 }
 {
  constexpr auto arithmetic = negate<int>();
  assert(arithmetic(7) == -7);
 }
 {
  constexpr auto comp = equal_to<int>();
  constexpr bool test = comp(0, 0);
  assert(test == true);
  assert(comp(1, 0) == false);
  assert(comp(0, 1) == false);
 }
 {
  constexpr auto comp = not_equal_to<int>();
  constexpr bool test = comp(0, 0);
  assert(test == false);
  assert(comp(1, 0) == true);
  assert(comp(0, 1) == true);
 }
 {
  constexpr auto comp = greater<int>();
  constexpr bool test = comp(0, 0);
  assert(test == false);
  assert(comp(1, 0) == true);
  assert(comp(0, 1) == false);
 }
 {
  constexpr auto comp = less<int>();
  constexpr bool test = comp(0, 0);
  assert(test == false);
  assert(comp(1, 0) == false);
  assert(comp(0, 1) == true);
 }
 {
  constexpr auto comp = greater_equal<int>();
  constexpr bool test = comp(0, 0);
  assert(test == true);
  assert(comp(1, 0) == true);
  assert(comp(0, 1) == false);
 }
 {
  constexpr auto comp = less_equal<int>();
  constexpr bool test = comp(0, 0);
  assert(test == true);
  assert(comp(1, 0) == false);
  assert(comp(0, 1) == true);
 }
 {
  constexpr auto binder = binder1st<modulus<int>>(modulus<int>(), 7);
  assert(binder(3) == 1);
 }
 {
  constexpr auto binder = bind1st(modulus<int>(), 7);
  assert(binder(3) == 1);
 }
 {
  constexpr auto binder = binder2nd<modulus<int>>(modulus<int>(), 7);
  assert(binder(3) == 3);
 }
 {
  constexpr auto binder = bind2nd(modulus<int>(), 7);
  assert(binder(3) == 3);
 }
}

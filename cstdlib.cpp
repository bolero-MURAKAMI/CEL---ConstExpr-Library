// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<limits>
#include<sscrisk/cel/cstdlib.hpp>

template<class T, T (&F)(T)>
void abs_test()
{
  constexpr T test1 = F(0);
  assert(test1 == 0);
  constexpr T test2 = F(1);
  assert(test2 == 1);
  constexpr T test3 = F(-1);
  assert(test3 == 1);
  constexpr T test4 = F(std::numeric_limits<T>::max());
  assert(test4 == std::numeric_limits<T>::max());
  constexpr T test5 = F(std::numeric_limits<T>::min() + 1);
  assert(test5 == std::numeric_limits<T>::max());
}
 
int main()
{
 namespace c = sscrisk::cel;

 // abs
 {
  abs_test<int, c::abs>();
  abs_test<long, c::labs>();
  abs_test<long long, c::llabs>();
  abs_test<long, c::abs>();
  abs_test<long long, c::abs>();
 }

 // div
 {
  {
   constexpr std::div_t test1 = c::div(0, 1);
   assert(test1.quot == 0);
   assert(test1.rem == 0);
   constexpr std::div_t test2 = c::div(23, 7);
   assert(test2.quot == 3);
   assert(test2.rem == 2);
   constexpr std::div_t test3 = c::div(-23, 7);
   assert(test3.quot == -3);
   assert(test3.rem == -2);
   constexpr std::div_t test4 = c::div(23, -7);
   assert(test4.quot == -3);
   assert(test4.rem == 2);
   constexpr std::div_t test5 = c::div(-23, -7);
   assert(test5.quot == 3);
   assert(test5.rem == -2);
   constexpr std::div_t test6 = c::div(std::numeric_limits<int>::max(), 1);
   assert(test6.quot == std::numeric_limits<int>::max());
   assert(test6.rem == 0);
   constexpr std::div_t test7 = c::div(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
   assert(test7.quot == 1);
   assert(test7.rem == 0);
  }
  {
   constexpr ldiv_t test1 = c::ldiv(0L, 1L);
   assert(test1.quot == 0);
   assert(test1.rem == 0);
   constexpr ldiv_t test2 = c::ldiv(23L, 7L);
   assert(test2.quot == 3);
   assert(test2.rem == 2);
   constexpr ldiv_t test3 = c::ldiv(-23L, 7L);
   assert(test3.quot == -3);
   assert(test3.rem == -2);
   constexpr ldiv_t test4 = c::ldiv(23L, -7L);
   assert(test4.quot == -3);
   assert(test4.rem == 2);
   constexpr ldiv_t test5 = c::ldiv(-23L, -7L);
   assert(test5.quot == 3);
   assert(test5.rem == -2);
   constexpr ldiv_t test6 = c::ldiv(std::numeric_limits<long>::max(), 1L);
   assert(test6.quot == std::numeric_limits<long>::max());
   assert(test6.rem == 0);
   constexpr ldiv_t test7 = c::ldiv(std::numeric_limits<long>::max(), std::numeric_limits<long>::max());
   assert(test7.quot == 1);
   assert(test7.rem == 0);
  }
  {
   constexpr lldiv_t test1 = c::lldiv(0LL, 1LL);
   assert(test1.quot == 0);
   assert(test1.rem == 0);
   constexpr lldiv_t test2 = c::lldiv(23LL, 7LL);
   assert(test2.quot == 3);
   assert(test2.rem == 2);
   constexpr lldiv_t test3 = c::lldiv(-23LL, 7LL);
   assert(test3.quot == -3);
   assert(test3.rem == -2);
   constexpr lldiv_t test4 = c::lldiv(23LL, -7LL);
   assert(test4.quot == -3);
   assert(test4.rem == 2);
   constexpr lldiv_t test5 = c::lldiv(-23LL, -7LL);
   assert(test5.quot == 3);
   assert(test5.rem == -2);
   constexpr lldiv_t test6 = c::lldiv(std::numeric_limits<long long>::max(), 1LL);
   assert(test6.quot == std::numeric_limits<long long>::max());
   assert(test6.rem == 0);
   constexpr lldiv_t test7 = c::lldiv(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max());
   assert(test7.quot == 1);
   assert(test7.rem == 0);
  }
  {
   constexpr ldiv_t test1 = c::div(0L, 1L);
   assert(test1.quot == 0);
   assert(test1.rem == 0);
   constexpr ldiv_t test2 = c::div(23L, 7L);
   assert(test2.quot == 3);
   assert(test2.rem == 2);
   constexpr ldiv_t test3 = c::div(-23L, 7L);
   assert(test3.quot == -3);
   assert(test3.rem == -2);
   constexpr ldiv_t test4 = c::div(23L, -7L);
   assert(test4.quot == -3);
   assert(test4.rem == 2);
   constexpr ldiv_t test5 = c::div(-23L, -7L);
   assert(test5.quot == 3);
   assert(test5.rem == -2);
   constexpr ldiv_t test6 = c::div(std::numeric_limits<long>::max(), 1L);
   assert(test6.quot == std::numeric_limits<long>::max());
   assert(test6.rem == 0);
   constexpr ldiv_t test7 = c::div(std::numeric_limits<long>::max(), std::numeric_limits<long>::max());
   assert(test7.quot == 1);
   assert(test7.rem == 0);
  }
  {
   constexpr lldiv_t test1 = c::div(0LL, 1LL);
   assert(test1.quot == 0);
   assert(test1.rem == 0);
   constexpr lldiv_t test2 = c::div(23LL, 7LL);
   assert(test2.quot == 3);
   assert(test2.rem == 2);
   constexpr lldiv_t test3 = c::div(-23LL, 7LL);
   assert(test3.quot == -3);
   assert(test3.rem == -2);
   constexpr lldiv_t test4 = c::div(23LL, -7LL);
   assert(test4.quot == -3);
   assert(test4.rem == 2);
   constexpr lldiv_t test5 = c::div(-23LL, -7LL);
   assert(test5.quot == 3);
   assert(test5.rem == -2);
   constexpr lldiv_t test6 = c::div(std::numeric_limits<long long>::max(), 1LL);
   assert(test6.quot == std::numeric_limits<long long>::max());
   assert(test6.rem == 0);
   constexpr lldiv_t test7 = c::div(std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max());
   assert(test7.quot == 1);
   assert(test7.rem == 0);
  }
 }
}

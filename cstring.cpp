// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/cstring.hpp>

int main()
{
 using namespace sscrisk::cel;

 // memcmp
 {
  static constexpr unsigned char a[]{0, 0, 0, 0}, b[]{0, 0, 0, 1}, c[]{0, 0, 1, 0};
  constexpr int test1 = memcmp((void*)&a, (void*)&a, 4);
  assert(test1 == 0);
  constexpr int test2 = memcmp((void*)&a, (void*)&b, 4);
  assert(test2 < 0);
  constexpr int test3 = memcmp((void*)&a, (void*)&c, 4);
  assert(test3 < 0);
  constexpr int test4 = memcmp((void*)&b, (void*)&a, 4);
  assert(test4 > 0);
  constexpr int test5 = memcmp((void*)&b, (void*)&b, 4);
  assert(test5 == 0);
  constexpr int test6 = memcmp((void*)&b, (void*)&c, 4);
  assert(test6 < 0);
  constexpr int test7 = memcmp((void*)&c, (void*)&a, 4);
  assert(test7 > 0);
  constexpr int test8 = memcmp((void*)&c, (void*)&b, 4);
  assert(test8 > 0);
  constexpr int test9 = memcmp((void*)&c, (void*)&c, 4);
  assert(test9 == 0);
 }

 // strcmp
 {
  constexpr int test1 = strcmp("", "");
  assert(test1 == 0);
  constexpr int test2 = strcmp("0", "");
  assert(test2 > 0);
  constexpr int test3 = strcmp("", "0");
  assert(test3 < 0);
  constexpr int test4 = strcmp("0", "0");
  assert(test4 == 0);
  constexpr int test5 = strcmp("0", "1");
  assert(test5 < 0);
  constexpr int test6 = strcmp("1", "0");
  assert(test6 > 0);
  constexpr int test7 = strcmp("00", "0");
  assert(test7 > 0);
  constexpr int test8 = strcmp("0", "00");
  assert(test8 < 0);
 }

 // strcoll
 {
  constexpr int test = strcoll("", "");
  assert(test == 0);
 }
}

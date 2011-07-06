// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/cstring.hpp>
#include<initializer_list>
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

 // strncmp
 {
  constexpr int test1 = strncmp("01234", "012345", 5);
  assert(test1 == 0);
  constexpr int test2 = strncmp("01234", "012345", 6);
  assert(test2 < 0);
 }

 // memchr
 {
  static constexpr unsigned char a[]{0, 1, 2, 3, 4};
  constexpr void const * p = memchr(a, 4, 5);
  constexpr unsigned char c = *static_cast<unsigned char const *>(p);
  assert(c == 4);
  constexpr void const * q = memchr(a, 5, 5);
  assert(q == nullptr);
 }

 // strchr
 {
  static constexpr char a[]{"01232"};
  constexpr char const * test1 = strchr(a, '0');
  assert(test1 == a + 0);
  assert(*test1 == '0');
  constexpr char const * test2 = strchr(a, '2');
  assert(test2 == a + 2);
  assert(*test2 == '2');
  constexpr char const * test3 = strchr(a, '6');
  assert(test3 == nullptr);
  char b[]{""};
  assert(strchr(b, '\0') == b);
 }
}

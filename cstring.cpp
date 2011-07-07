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

 // strcspn
 {
  constexpr std::size_t test1 = strcspn("", "");
  assert(test1 == 0);
  constexpr std::size_t test2 = strcspn("", "0");
  assert(test2 == 0);
  constexpr std::size_t test3 = strcspn("0", "");
  assert(test3 == 1);
  constexpr std::size_t test4 = strcspn("0", "0");
  assert(test4 == 0);
  constexpr std::size_t test5 = strcspn("0123456789", &"975"[0]); // g++ 4.7.0 20110702 のバグよけ
  assert(test5 == 5);
  constexpr std::size_t test6 = strcspn("0123456789", "01234567");
  assert(test6 == 0);
  constexpr std::size_t test7 = strcspn("0123456789", "123456789");
  assert(test7 == 1);
 }

 // strstrpbrk
 {
  constexpr char const * test1 = strpbrk("", "");
  assert(test1 == nullptr);
  constexpr char const * test2 = strpbrk("0", "");
  assert(test2 == nullptr);
  constexpr char const * test3 = strpbrk("", "0");
  assert(test3 == nullptr);
  constexpr char const * test4 = strpbrk("0", "0");
  assert(test4 != nullptr);
  assert(*test4 == '0');
  constexpr char const * test5 = strpbrk("0", "1");
  assert(test5 == nullptr);
  constexpr char const * test6 = strpbrk("01234", &"6543"[0]); // g++ 4.7.0 20110702 のバグよけ
  assert(test6 != nullptr);
  assert(*test6 == '3');
 }

 // strrchr
 {
  static constexpr char a[]{"0123232"};
  constexpr char const * test1 = strrchr(a, '0');
  assert(test1 == a + 0);
  assert(*test1 == '0');
  constexpr char const * test2 = strrchr(&a[0], '2'); // g++ 4.7.0 20110702 のバグよけ
  assert(test2 == a + 6);
  assert(*test2 == '2');
  constexpr char const * test3 = strrchr(a, '6');
  assert(test3 == nullptr);
  char b[]{""};
  assert(strrchr(b, '\0') == b);
 }

 // strspn
 {
  constexpr std::size_t test1 = strspn("", "");
  assert(test1 == 0);
  constexpr std::size_t test2 = strspn("", "0");
  assert(test2 == 0);
  constexpr std::size_t test3 = strspn("0", "");
  assert(test3 == 0);
  constexpr std::size_t test4 = strspn("0", "0");
  assert(test4 == 1);
  constexpr std::size_t test5 = strspn("0123", &"210"[0]); // g++ 4.7.0 20110702 のバグよけ
  assert(test5 == 3);
  constexpr std::size_t test6 = strspn("0123", "123");
  assert(test6 == 0);
 }

 // strstr
 {
  constexpr char const * test1 = strstr("", "");
  assert(test1 != nullptr);
  assert(*test1 == '\0');
  constexpr char const * test2 = strstr("0", "");
  assert(test2 != nullptr);
  assert(*test2 == '0');
  constexpr char const * test3 = strstr("", "0");
  assert(test3 == nullptr);
  constexpr char const * test4 = strstr(&"012301230123"[0], "301"); // g++ 4.7.0 20110702 のバグよけ
  assert(test4 != nullptr);
  assert(*test4 == '3');
  constexpr char const * test5 = strstr("012301230123", "124");
  assert(test5 == nullptr);
  char b[]{"012345"};
  char const * test6 = strstr(b, "012345");
  assert(test6 == b);
 }
}

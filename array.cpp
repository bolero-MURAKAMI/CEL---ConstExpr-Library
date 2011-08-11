// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/array.hpp>

int main()
{
 using sscrisk::cel::array;
 // fill
 {
  array<int, 10> a{{64}};
  a.fill(42);
  assert(a[0] == 42);
  assert(a[9] == 42);
 }
 // swap
 {
  array<int, 2> a{{0, 1}};
  array<int, 2> b{{1, 2}};
  std::swap(a, b);
  assert(a[0] == 1);
  assert(a[1] == 2);
  assert(b[0] == 0);
  assert(b[1] == 1);
 }
 // begin
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.begin();
   assert(*test == 0);
  }
  {
   static constexpr array<int, 2> a{{0, 1}};
   constexpr auto test = a.begin();
   assert(*test == 0);
  }
 }
 // end
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.end();
   assert(test - a.begin() == 2);
  }
  {
   static constexpr array<int, 2> a{{0, 1}};
   constexpr auto test = a.end();
   assert(test - a.begin() == 2);
  }
 }
 // rbegin
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.rbegin();
   assert(*test == 1);
  }
  {
   array<int, 2> const a{{0, 1}};
   auto test = a.rbegin();
   assert(*test == 1);
  }
 }
 // rend
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.rend();
   assert(test - a.rbegin() == 2);
  }
  {
   array<int, 2> const a{{0, 1}};
   auto test = a.rend();
   assert(test - a.rbegin() == 2);
  }
 }
 // cbegin
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.cbegin();
   assert(*test == 0);
  }
  {
   static constexpr array<int, 2> a{{0, 1}};
   auto test = a.cbegin();
   assert(*test == 0);
  }
 }
 // cend
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.cend();
   assert(test - a.cbegin() == 2);
  }
  {
   static constexpr array<int, 2> a{{0, 1}};
   constexpr auto test = a.cend();
   assert(test - a.cbegin() == 2);
  }
 }
 // crbegin
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.crbegin();
   assert(*test == 1);
  }
  {
   array<int, 2> const a{{0, 1}};
   auto test = a.crbegin();
   assert(*test == 1);
  }
 }
 // crend
 {
  {
   array<int, 2> a{{0, 1}};
   auto test = a.crend();
   assert(test - a.crbegin() == 2);
  }
  {
   array<int, 2> const a{{0, 1}};
   auto test = a.crend();
   assert(test - a.crbegin() == 2);
  }
 }
 // size
 {
  constexpr array<int, 0> a{{}};
  constexpr auto test1 = a.size();
  assert(test1 == 0);
  constexpr array<int, 1> b{{}};
  constexpr auto test2 = b.size();
  assert(test2 == 1);
 }
 // max_size
 {
  constexpr array<int, 0> a{{}};
  constexpr auto test1 = a.max_size();
  assert(test1 == 0);
  constexpr array<int, 2> b{{}};
  constexpr auto test2 = b.max_size();
  assert(test2 == 2);
 }
 // empty
 {
  constexpr array<int, 0> a{{}};
  constexpr auto test1 = a.empty();
  assert(test1 == true);
  constexpr array<int, 3> b{{}};
  constexpr auto test2 = b.empty();
  assert(test2 == false);
 }
 // operator[]
 {
  {
   array<int, 1> a{{42}};
   auto test = a[0];
   assert(test == 42);
  }
  {
   constexpr array<int, 2> a{{42, 64}};
   constexpr auto test1 = a[0];
   assert(test1 == 42);
   constexpr auto test2 = a[1];
   assert(test2 == 64);
  }
 }
 // at
 {
  {
   array<int, 1> a{{42}};
   auto test = a.at(0);
   assert(test == 42);
   try
   {
    auto& test = a.at(2);
    assert(!&test);
   }
   catch(std::out_of_range const &)
   {}
  }
  {
   array<int, 2> const a{{42, 64}};
   auto test1 = a.at(0);
   assert(test1 == 42);
   auto test2 = a.at(1);
   assert(test2 == 64);
   try
   {
    auto& test = a.at(3);
    assert(!&test);
   }
   catch(std::out_of_range)
   {}
  }
 }
 // front
 {
  {
   array<int, 2> a{{42, 64}};
   auto test = a.front();
   assert(test == 42);
  }
  {
   constexpr array<int, 2> a{{42, 64}};
   constexpr auto test = a.front();
   assert(test == 42);
  }
 }
 // back
 {
  {
   array<int, 2> a{{42, 64}};
   auto test = a.back();
   assert(test == 64);
  }
  {
   constexpr array<int, 2> a{{42, 64}};
   constexpr auto test = a.back();
   assert(test == 64);
  }
 }
 // data
 {
  {
   array<int, 2> a{{42, 64}};
   auto test = a.data();
   assert(*test == 42);
  }
  {
   static constexpr array<int, 2> a{{42, 64}};
   constexpr auto test = a.data();
   assert(*test == 42);
  }
 }
 // operator==
 {
  {
   array<int, 0> a, b;
   bool test = a == b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a == b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a == b;
   assert(test == false);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a == b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a == b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a == b;
   assert(test == false);
  }
 }
 // operator!=
 {
  {
   array<int, 0> a, b;
   bool test = a != b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a != b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a != b;
   assert(test == true);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a != b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a != b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a != b;
   assert(test == true);
  }
 }
 // operator<
 {
  {
   array<int, 0> a, b;
   bool test = a < b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a < b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a < b;
   assert(test == true);
  }
  {
   array<int, 1> a{{64}}, b{{42}};
   bool test = a < b;
   assert(test == false);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a < b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a < b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a < b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{64}}, b{{42}};
   constexpr bool test = a < b;
   assert(test == false);
  }
 }
 // operator>
 {
  {
   array<int, 0> a, b;
   bool test = a > b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a > b;
   assert(test == false);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a > b;
   assert(test == false);
  }
  {
   array<int, 1> a{{64}}, b{{42}};
   bool test = a > b;
   assert(test == true);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a > b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a > b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a > b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{64}}, b{{42}};
   constexpr bool test = a > b;
   assert(test == true);
  }
 }
 // operator<=
 {
  {
   array<int, 0> a, b;
   bool test = a <= b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a <= b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a <= b;
   assert(test == true);
  }
  {
   array<int, 1> a{{64}}, b{{42}};
   bool test = a <= b;
   assert(test == false);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a <= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a <= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a <= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{64}}, b{{42}};
   constexpr bool test = a <= b;
   assert(test == false);
  }
 }
 // operator>=
 {
  {
   array<int, 0> a, b;
   bool test = a >= b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{42}};
   bool test = a >= b;
   assert(test == true);
  }
  {
   array<int, 1> a{{42}}, b{{64}};
   bool test = a >= b;
   assert(test == false);
  }
  {
   array<int, 1> a{{64}}, b{{42}};
   bool test = a >= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 0> a{{}}, b{{}};
   constexpr bool test = a >= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{42}};
   constexpr bool test = a >= b;
   assert(test == true);
  }
  {
   static constexpr array<int, 1> a{{42}}, b{{64}};
   constexpr bool test = a >= b;
   assert(test == false);
  }
  {
   static constexpr array<int, 1> a{{64}}, b{{42}};
   constexpr bool test = a >= b;
   assert(test == true);
  }
 }
 // tuple_size
 {
  static_assert(std::tuple_size<array<int, 0> >::value == 0, "");
  static_assert(std::tuple_size<array<long, 1> >::value == 1, "");
  static_assert(std::tuple_size<array<unsigned, 2> >::value == 2, "");
 }
 // tuple_element
 {
  static_assert(std::is_same<std::tuple_element<0, array<int, 1>>::type, int>::value, "");
  static_assert(std::is_same<std::tuple_element<0, array<long, 1>>::type, long>::value, "");
  static_assert(std::is_same<std::tuple_element<0, array<unsigned, 1>>::type, unsigned>::value, "");
 }
 // get
 {
  {
   array<int, 1> a{{42}};
   int& test = std::get<0>(a);
   assert(test == 42);
  }
  {
   array<int, 1> a{{42}};
   int&& test = std::get<0>(std::move(a));
   assert(test == 42);
  }
  {
   static constexpr array<int, 1> a{{42}};
   constexpr int const & test = std::get<0>(a);
   assert(test == 42);
  }
 }
}

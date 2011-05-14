// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/list.hpp>
#include<sscrisk/cel/algorithm.hpp>

constexpr bool is_less_than_2(int i){return i < 2;}

int main()
{
 using namespace sscrisk::cel;

 // begin
 {
  static constexpr list<int, 1> v{9};
  constexpr auto iter = begin(v);
  assert(*iter == 9);
 }

 // end
 {
  static constexpr list<int, 1> v{8};
  constexpr auto iter1 = end(v);
  constexpr auto iter2 = iter1 - 1;
  assert(*iter2 == 8);
 }

 // size
 {
  constexpr list<int, 0> v{};
  constexpr auto test1 = size(v);
  assert(test1 == 0);
  constexpr list<int, 1> w{0};
  constexpr auto test2 = size(w);
  assert(test2 == 1);
  constexpr list<int, 2> x{0, {1}};
  constexpr auto test3 = size(x);
  assert(test3 == 2);
 }

 // empty
 {
  constexpr list<int, 0> v{};
  constexpr bool test1 = empty(v);
  assert(test1 == true);
  constexpr list<int, 1> w{0};
  constexpr bool test2 = empty(w);
  assert(test2 == false);
  constexpr list<int, 2> x{0, {1}};
  constexpr bool test3 = empty(x);
  assert(test3 == false);
 }

 // front
 {
  constexpr list<int, 1> v{0};
  constexpr auto test1 = front(v);
  assert(test1 == 0);
  constexpr list<int, 3> w{3, {2, {1}}};
  constexpr auto test2 = front(w);
  assert(test2 == 3);
 }

 // back
 {
  constexpr list<int, 1> v{0};
  constexpr auto test1 = back(v);
  assert(test1 == 0);
  constexpr list<int, 3> w{3, {2, {1}}};
  constexpr auto test2 = back(w);
  assert(test2 == 1);
 }

 // at
 {
  {
   constexpr list<int, 1> v = {0};
   constexpr auto test1 = at(v, 0);
   assert(test1 == 0);
  }
  {
   constexpr list<int, 3> v = {0, {1, {2}}};
   constexpr auto test1 = at(v, 0);
   assert(test1 == 0);
   constexpr auto test2 = at(v, 1);
   assert(test2 == 1);
   constexpr auto test3 = at(v, 2);
   assert(test3 == 2);
  }
 }

 // clear
 {
  constexpr list<int, 0> v{};
  constexpr auto test1 = clear(v);
  assert(empty(test1) == true);
  constexpr list<int, 1> w{7};
  constexpr auto test2 = clear(w);
  assert(empty(test2) == true);
  constexpr list<int, 2> x{3, {9}};
  constexpr auto test3 = clear(x);
  assert(empty(test3) == true);
 }

 // push_front
 {
  constexpr list<int, 0> zero{};
  constexpr auto one = push_front(zero, 10);
  constexpr auto test1 = at(one, 0);
  assert(test1 == 10);
  constexpr auto two = push_front(one, 20);
  constexpr auto test2 = at(two, 0);
  assert(test2 == 20);
  constexpr auto test3 = at(two, 1);
  assert(test3 == 10);
 }

 // pop_front
 {
  constexpr list<int, 1> v{0};
  constexpr auto test1 = pop_front(v);
  assert(size(test1) == 0);
  constexpr list<int, 2> w{0, {1}};
  constexpr auto test2 = pop_front(w);
  assert(size(test2) == 1);
  constexpr list<int, 3> x{0, {1, {2}}};
  constexpr auto test3 = pop_front(x);
  assert(size(test3) == 2);
 }

 // make_list
 {
  constexpr auto test1 = make_list<int>();
  assert(size(test1) == 0);
  constexpr auto test2 = make_list(141, 314, 10);
  assert(test2.next.value == 314);
  constexpr auto test3 = make_list(0, 1, 42, 2);
  assert(size(test3) == 4);
 }
 
 // list_iter
 {
  static constexpr list<int, 3> v{0, {1, {2}}};
  constexpr auto iter0 = begin(v);
  assert(*iter0 == 0);
  constexpr auto iter1 = iter0 + 1;
  assert(*iter1 == 1);
  constexpr auto iter2 = end(v);
  constexpr auto iter3 = iter2 - 1;
  assert(*iter3 == 2);
  {
   constexpr bool test1 = all_of(begin(v), end(v), is_less_than_2);
   assert(test1 == false);
   constexpr bool test2 = all_of(begin(v), end(v) - 1, is_less_than_2);
   assert(test2 == true);
  }
 }
}

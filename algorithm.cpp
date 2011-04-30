// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/algorithm.hpp>

constexpr bool is_less_than_2(int n)
{
 return n < 2;
}

constexpr bool is_greater_than_1(int n)
{
 return n > 1;
}

constexpr bool are_greater_than_2(int n, int m)
{
 return n > 2 && m > 2;
}

constexpr bool abs_equal(int n, int m)
{
 return (n >= 0 ? n : -n) == (m >= 0 ? m : -m);
}

int main()
{
 static constexpr int a[] = {0};
 static constexpr int b[] = {0, 1};
 static constexpr int c[] = {0, 1, 2};
 static constexpr int d[] = {0, 1, 2, 3};
 static constexpr int e[] = {0, 1, 2, 3, 3, 4, 5, 0};

 {
  using namespace sscrisk::cel;

  // all_of
  {
   constexpr bool test1 = all_of(a, a, is_less_than_2);
   assert(test1);
   constexpr bool test2 = all_of(a, a + 1, is_less_than_2);
   assert(test2);
   constexpr bool test3 = all_of(c, c + 3, is_less_than_2);
   assert(!test3);
  }

  // any_of
  {
   constexpr bool test = any_of(a, a, is_greater_than_1);
   assert(!test);
  }

  // none_of
  {
   constexpr bool test = none_of(a, a, is_greater_than_1);
   assert(test);
  }

  // find
  {
   constexpr int const * test = find(d, d, 0);
   assert(test == d);
  }

  // find_if
  {
   constexpr auto iter = find_if(a, a, is_greater_than_1);
   assert(iter == a);
  }

  // find_if_not
  {
   constexpr auto iter = find_if_not(a, a, is_less_than_2);
   assert(iter == a);
  }

  // adjacent_find
  {
   constexpr auto test1 = adjacent_find(a, a);
   assert(test1 == a);
   constexpr auto test2 = adjacent_find(a, a + 1);
   assert(test2 == a + 1);
   constexpr auto test3 = adjacent_find(b, b + 2);
   assert(test3 == b + 2);
   constexpr auto test4 = adjacent_find(e, e + 8);
   assert(*test4 == 3);
   assert(*(test4 + 1) == 3);
   assert(test4 - e == 3);
   constexpr auto test5 = adjacent_find(e, e + 8, are_greater_than_2);
   assert(*test5 > 2);
   assert(*(test5 + 1) > 2);
   assert(test5 - e == 3);
  }

  // count
  {
   constexpr auto test1 = count(a, a, 0);
   assert(test1 == 0);
  }

  // count_if
  {
   constexpr auto test1 = count_if(a, a, is_less_than_2);
   assert(test1 == 0);
  }

  // equal
  {
   {
    constexpr bool test1 = equal(a, a, b);
    assert(test1);
    constexpr bool test2 = equal(d, d + 4, e);
    assert(test2);
    static constexpr int f[] = {0, 1, 2, 4};
    constexpr bool test3 = equal(d, d + 4, f);
    assert(!test3);
   }
   {
    constexpr bool test1 = equal(a, a, b, abs_equal);
    assert(test1);
    constexpr bool test2 = equal(d, d + 4, e, abs_equal);
    assert(test2);
    static constexpr int f[] = {0, 1, 2, 4};
    constexpr bool test3 = equal(d, d + 4, f, abs_equal);
    assert(!test3);
    static constexpr int g[] = {0, -1, -2, -3};
    constexpr bool test4 = equal(d, d + 4, g, abs_equal);
    assert(test4);
   }
  }
 }

 // range
 {
  using namespace sscrisk::cel::range;

  // begin and end
  {
   constexpr auto beg = begin(a);
   constexpr auto ed = end(a);
   assert(ed - beg == 1);
   constexpr range_container<int const *> range(beg, ed);
   assert(!range.empty());
   constexpr range_container<int const *> range2(range.begin() + 1, range.end());
   assert(range2.empty());
  }

  // all_of
  {
   constexpr bool testa = all_of(a, is_less_than_2);
   assert(testa);
   constexpr bool testb = all_of(b, is_less_than_2);
   assert(testb);
   constexpr bool testc = all_of(c, is_less_than_2);
   assert(!testc);
   constexpr bool testd = all_of(d, is_less_than_2);
   assert(!testd);
  }

  // any_of
  {
   constexpr bool testa = any_of(a, is_greater_than_1);
   assert(!testa);
   constexpr bool testb = any_of(b, is_greater_than_1);
   assert(!testb);
   constexpr bool testc = any_of(c, is_greater_than_1);
   assert(testc);
   constexpr bool testd = any_of(d, is_greater_than_1);
   assert(testd);
  }

  // none_of
  {
   constexpr bool testa = none_of(a, is_greater_than_1);
   assert(testa);
   constexpr bool testb = none_of(b, is_greater_than_1);
   assert(testb);
   constexpr bool testc = none_of(c, is_greater_than_1);
   assert(!testc);
   constexpr bool testd = none_of(d, is_greater_than_1);
   assert(!testd);
  }

  // find
  {
   constexpr auto test1 = find(d, 0);
   assert(*test1.begin() == 0);
   constexpr auto test2 = find(d, 3);
   assert(*test2.begin() == 3);
   constexpr auto test3 = find(d, 100);
   assert(test3.end() == end(d));
   constexpr auto test4 = find(d, 3);
   constexpr auto test5 = test4.end();
   constexpr auto test6 = test4.begin();
   constexpr auto test7 = test5 - test6;
   assert(test7 == 1);
  }

  // find_if
  {
   {
    constexpr auto range = find_if(a, is_greater_than_1);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 0);
   }
   {
    constexpr auto range = find_if(b, is_greater_than_1);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 0);
   }
   {
    constexpr auto range = find_if(c, is_greater_than_1);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 1);
    assert(*first > 1);
   }
   {
    constexpr auto range = find_if(d, is_greater_than_1);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 2);
    assert(*first > 1);
   }
  }

  // find_if_not
  {
   {
    constexpr auto range = find_if_not(a, is_less_than_2);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 0);
   }
   {
    constexpr auto range = find_if_not(b, is_less_than_2);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 0);
   }
   {
    constexpr auto range = find_if_not(c, is_less_than_2);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 1);
    assert(!(*first < 2));
   }
   {
    constexpr auto range = find_if_not(d, is_less_than_2);
    constexpr auto first = range.begin(), last = range.end();
    constexpr auto diff = last - first;
    assert(diff == 2);
    assert(!(*first < 2));
   }
  }

  // adjacent_find
  {
   constexpr auto test1 = adjacent_find(a);
   assert(test1.begin() == test1.end());
   constexpr auto test2 = adjacent_find(e);
   assert(test2.end() - test2.begin() == 5);
   assert(*test2.begin() == *(test2.begin() + 1));
   constexpr auto test3 = adjacent_find(a, are_greater_than_2);
   assert(test3.begin() == test3.end());
   constexpr auto test5 = adjacent_find(e, are_greater_than_2);
   assert(*test5.begin() > 2 && *(test5.begin() + 1) > 2);
  }

  // count
  {
   constexpr auto test2 = count(a, 0);
   assert(test2 == 1);
   constexpr auto test3 = count(d, 3);
   assert(test3 == 1);
   static constexpr int e[] = {0, 1, 2, 0, 1, 2, 0};
   constexpr auto test4 = count(e, 0);
   assert(test4 == 3);
   constexpr auto test5 = count(e, 3);
   assert(test5 == 0);
  }

  // count_if
  {
   constexpr auto test2 = count_if(a, is_less_than_2);
   assert(test2 == 1);
   constexpr auto test3 = count_if(d, is_less_than_2);
   assert(test3 == 2);
   constexpr auto test4 = count_if(e, is_less_than_2);
   assert(test4 == 3);
   constexpr auto test5 = count_if(e, is_greater_than_1);
   assert(test5 == 5);
  }
 }
}

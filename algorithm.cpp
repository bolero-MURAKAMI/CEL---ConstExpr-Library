// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/algorithm.hpp>
#include<iostream>
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

constexpr bool eq(int n, int m)
{
 return n == m;
}

struct test
{
 int a, b;
};
constexpr bool operator<(test const & lhs, test const & rhs){return lhs.a < rhs.a;}

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

  // find_end
  {
   {
    constexpr auto test1 = find_end(a, a, b, b);
    assert(test1 == a);
    constexpr auto test2 = find_end(a, a + 1, b, b);
    assert(test2 == a + 1);
    constexpr auto test3 = find_end(a, a, b, b + 1);
    assert(test3 == a);
    constexpr auto test4 = find_end(a, a + 1, b, b + 1);
    assert(test4 == a);
    constexpr auto test5 = find_end(a, a + 1, b, b + 2);
    assert(test5 == a + 1);
    constexpr auto test6 = find_end(b, b + 2, a, a + 1);
    assert(test6 == b);
    constexpr auto test7 = find_end(e, e + 8, a, a + 1);
    assert(test7 == e + 7);
   }
   {
    constexpr auto eq = equal_to<int>();
    constexpr auto test1 = find_end(a, a, b, b, eq);
    assert(test1 == a);
    constexpr auto test2 = find_end(a, a + 1, b, b, eq);
    assert(test2 == a + 1);
    constexpr auto test3 = find_end(a, a, b, b + 1, eq);
    assert(test3 == a);
    constexpr auto test4 = find_end(a, a + 1, b, b + 1, eq);
    assert(test4 == a);
    constexpr auto test5 = find_end(a, a + 1, b, b + 2, eq);
    assert(test5 == a + 1);
    constexpr auto test6 = find_end(b, b + 2, a, a + 1, eq);
    assert(test6 == b);
    constexpr auto test7 = find_end(e, e + 8, a, a + 1, eq);
    assert(test7 == e + 7);
   }
  }

  // find_first_of
  {
   {
    constexpr auto test1 = find_first_of(a, a, b, b);
    assert(test1 == a);
    constexpr auto test2 = find_first_of(a, a, b, b + 2);
    assert(test2 == a);
    constexpr auto test3 = find_first_of(a, a + 1, b, b);
    assert(test3 == a + 1);
    static constexpr int f[] = {6, 5, 4, 3, 2, 1, 0};
    constexpr auto test4 = find_first_of(f, f + 7, a, a + 1);
    assert(test4 == f + 6);
    assert(*test4 == 0);
    constexpr auto test5 = find_first_of(f, f + 3, a, a + 1);
    assert(test5 == f + 3);
   }
   {
    constexpr auto eq = equal_to<int>();
    constexpr auto test1 = find_first_of(a, a, b, b, eq);
    assert(test1 == a);
    constexpr auto test2 = find_first_of(a, a, b, b + 2, eq);
    assert(test2 == a);
    constexpr auto test3 = find_first_of(a, a + 1, b, b, eq);
    assert(test3 == a + 1);
    static constexpr int f[] = {6, 5, 4, 3, 2, 1, 0};
    constexpr auto test4 = find_first_of(f, f + 7, a, a + 1, eq);
    assert(test4 == f + 6);
    assert(*test4 == 0);
    constexpr auto test5 = find_first_of(f, f + 3, a, a + 1, eq);
    assert(test5 == f + 3);
   }
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

  // mismatch
  {
   {
    constexpr auto test1 = mismatch(a, a, b);
    assert(test1.first == a);
    assert(test1.second == b);
    constexpr auto test2 = mismatch(c, c + 3, d);
    assert(test2.first == c + 3);
    assert(test2.second == d + 3);
    static constexpr int f[] = {0, 1, 2, 4};
    constexpr auto test3 = mismatch(d, d + 4, f);
    assert(test3.first == d + 3);
    assert(test3.second == f + 3);
    assert(*test3.first != *test3.second);
   }
   {
    constexpr auto test1 = mismatch(a, a, b, eq);
    assert(test1.first == a);
    assert(test1.second == b);
    constexpr auto test2 = mismatch(c, c + 3, d, eq);
    assert(test2.first == c + 3);
    assert(test2.second == d + 3);
    static constexpr int f[] = {0, 1, 2, 4};
    constexpr auto test3 = mismatch(d, d + 4, f, eq);
    assert(test3.first == d + 3);
    assert(test3.second == f + 3);
    assert(*test3.first != *test3.second);
   }
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

  // is_permutation
  {
   {
    constexpr bool test1 = is_permutation(a, a, b);
    assert(test1 == true);
    constexpr bool test2 = is_permutation(a, a + 1, b);
    assert(test2 == true);
    static constexpr int x[] = {1};
    constexpr bool test3 = is_permutation(a, a + 1, x);
    assert(test3 == false);
    constexpr bool test4 = is_permutation(b, b + 2, c);
    assert(test4 == true);
    static constexpr int y[] = {1, 0};
    constexpr bool test5 = is_permutation(b, b + 2, y);
    assert(test5 == true);
    static constexpr int g[] = {2, 0, 3, 5, 3, 1, 0, 4};
    constexpr bool test6 = is_permutation(e, e + 8, g);
    assert(test6 == true);
   }
   {
    constexpr bool test1 = is_permutation(a, a, b, equal_to<int>());
    assert(test1 == true);
    constexpr bool test2 = is_permutation(a, a + 1, b, equal_to<int>());
    assert(test2 == true);
    static constexpr int x[] = {1};
    constexpr bool test3 = is_permutation(a, a + 1, x, equal_to<int>());
    assert(test3 == false);
    constexpr bool test4 = is_permutation(b, b + 2, c, equal_to<int>());
    assert(test4 == true);
    static constexpr int y[] = {1, 0};
    constexpr bool test5 = is_permutation(b, b + 2, y, equal_to<int>());
    assert(test5 == true);
    static constexpr int g[] = {2, 0, 3, 5, 3, 1, 0, 4};
    constexpr bool test6 = is_permutation(e, e + 8, g, equal_to<int>());
    assert(test6 == true);
    // bug: bind2nd + function
    // constexpr bool test7 = is_permutation(e, e + 8, g, eq);
    // assert(test7 == true);
   }
  }

  // search
  {
   {
    constexpr auto test1 = search(a, a, b, b);
    assert(test1 == a);
    constexpr auto test2 = search(a, a + 1, b, b);
    assert(test2 == a);
    constexpr auto test3 = search(a, a, b, b + 1);
    assert(test3 == a);
    constexpr auto test4 = search(c, c + 3, d + 1, d + 3);
    assert(test4 == c + 1);
    constexpr auto test5 = search(a, a + 1, b, b + 2);
    assert(test5 == a + 1);
   }
   {
    constexpr auto test1 = search(a, a, b, b, eq);
    assert(test1 == a);
    constexpr auto test2 = search(a, a + 1, b, b, eq);
    assert(test2 == a);
    constexpr auto test3 = search(a, a, b, b + 1, eq);
    assert(test3 == a);
    constexpr auto test4 = search(c, c + 3, d + 1, d + 3, eq);
    assert(test4 == c + 1);
    constexpr auto test5 = search(a, a + 1, b, b + 2, eq);
    assert(test5 == a + 1);
   }
  }

  // search_n
  {
   {
    constexpr auto test1 = search_n(a, a, 0, 0);
    assert(test1 == a);
    constexpr auto test2 = search_n(a, a + 1, 0, 0);
    assert(test2 == a);
    constexpr auto test3 = search_n(a, a + 1, 1, 0);
    assert(test3 == a);
    constexpr auto test4 = search_n(a, a + 1, 2, 0);
    assert(test4 == a + 1);
    constexpr auto test5 = search_n(e, e + 8, 2, 3);
    assert(test5 == e + 3);
   }
   {
    constexpr auto test1 = search_n(a, a, 0, 0, eq);
    assert(test1 == a);
    constexpr auto test2 = search_n(a, a + 1, 0, 0, eq);
    assert(test2 == a);
    constexpr auto test3 = search_n(a, a + 1, 1, 0, eq);
    assert(test3 == a);
    constexpr auto test4 = search_n(a, a + 1, 2, 0, eq);
    assert(test4 == a + 1);
    constexpr auto test5 = search_n(e, e + 8, 2, 3, eq);
    assert(test5 == e + 3);
   }
  }

  // is_partitioned
  {
   constexpr bool test1 = is_partitioned(a, a, is_less_than_2);
   assert(test1 == true);
   constexpr bool test2 = is_partitioned(a, a + 1, is_less_than_2);
   assert(test2 == true);
   constexpr bool test3 = is_partitioned(b, b + 2, is_less_than_2);
   assert(test3 == true);
   constexpr bool test4 = is_partitioned(c, c + 3, is_less_than_2);
   assert(test4 == true);
   constexpr bool test5 = is_partitioned(e, e + 8, is_less_than_2);
   assert(test5 == false);
  }

  // partition_point
  {
   constexpr auto test1 = partition_point(a, a, is_less_than_2);
   assert(test1 == a);
   constexpr auto test2 = partition_point(a, a + 1, is_less_than_2);
   assert(test2 == a + 1);
   constexpr auto test3 = partition_point(b, b + 2, is_less_than_2);
   assert(test3 == b + 2);
   constexpr auto test4 = partition_point(c, c + 3, is_less_than_2);
   assert(test4 == c + 2);
   constexpr auto test5 = partition_point(d, d + 4, is_less_than_2);
   assert(test5 == d + 2);
  }

  // is_sorted
  {
   {
    constexpr bool test1 = is_sorted(a, a);
    assert(test1 == true);
    constexpr bool test2 = is_sorted(a, a + 1);
    assert(test2 == true);
    constexpr bool test3 = is_sorted(b, b + 2);
    assert(test3 == true);
    constexpr bool test4 = is_sorted(e, e + 7);
    assert(test4 == true);
    constexpr bool test5 = is_sorted(e, e + 8);
    assert(test5 == false);
   }
   {
    struct less{constexpr bool operator()(int a, int b)const{return a < b;}};
    constexpr auto comp = less();
    constexpr bool test1 = is_sorted(a, a, comp);
    assert(test1 == true);
    constexpr bool test2 = is_sorted(a, a + 1, comp);
    assert(test2 == true);
    constexpr bool test3 = is_sorted(b, b + 2, comp);
    assert(test3 == true);
    constexpr bool test4 = is_sorted(e, e + 7, comp);
    assert(test4 == true);
    constexpr bool test5 = is_sorted(e, e + 8, comp);
    assert(test5 == false);
   }
  }

  // is_sorted_until
  {
   {
    constexpr auto test1 = is_sorted_until(a, a);
    assert(test1 == a);
    constexpr auto test2 = is_sorted_until(a, a + 1);
    assert(test2 == a + 1);
    constexpr auto test3 = is_sorted_until(b, b + 2);
    assert(test3 == b + 2);
    constexpr auto test4 = is_sorted_until(e, e + 8);
    assert(test4 == e + 7);
   }
   {
    struct less{constexpr bool operator()(int a, int b)const{return a < b;}};
    constexpr auto comp = less();
    constexpr auto test1 = is_sorted_until(a, a, less());
    assert(test1 == a);
    constexpr auto test2 = is_sorted_until(a, a + 1, less());
    assert(test2 == a + 1);
    constexpr auto test3 = is_sorted_until(b, b + 2, comp);
    assert(test3 == b + 2);
    constexpr auto test4 = is_sorted_until(e, e + 8, comp);
    assert(test4 == e + 7);
   }
  }

  // lower_bound
  {
   {
    constexpr auto test1 = lower_bound(a, a, 0);
    assert(test1 == a);
    constexpr auto test2 = lower_bound(a, a + 1, 0);
    assert(test2 == a);
    constexpr auto test3 = lower_bound(a, a + 1, 1);
    assert(test3 == a + 1);
    constexpr auto test4 = lower_bound(e, e + 7, 3);
    assert(test4 == e + 3);
    constexpr auto test5 = lower_bound(e, e + 7, 4);
    assert(test5 == e + 5);
    constexpr auto test6 = lower_bound(e, e + 7, 2);
    assert(test6 == e + 2);
   }
   {
    constexpr auto comp = less<int>();
    constexpr auto test1 = lower_bound(a, a, 0, comp);
    assert(test1 == a);
    constexpr auto test2 = lower_bound(a, a + 1, 0, comp);
    assert(test2 == a);
    constexpr auto test3 = lower_bound(a, a + 1, 1, comp);
    assert(test3 == a + 1);
    constexpr auto test4 = lower_bound(e, e + 7, 3, comp);
    assert(test4 == e + 3);
    constexpr auto test5 = lower_bound(e, e + 7, 4, comp);
    assert(test5 == e + 5);
    constexpr auto test6 = lower_bound(e, e + 7, 2, comp);
    assert(test6 == e + 2);
   }
  }

  // upper_bound
  {
   {
    constexpr auto test1 = upper_bound(a, a, 0);
    assert(test1 == a);
    constexpr auto test2 = upper_bound(a, a + 1, 0);
    assert(test2 == a + 1);
    constexpr auto test3 = upper_bound(a, a + 1, 1);
    assert(test3 == a + 1);
    constexpr auto test4 = upper_bound(e, e + 7, 3);
    assert(test4 == e + 5);
    constexpr auto test5 = upper_bound(e, e + 7, 4);
    assert(test5 == e + 6);
    constexpr auto test6 = upper_bound(e, e + 7, 2);
    assert(test6 == e + 3);
   }
   {
    constexpr auto comp = less<int>();
    constexpr auto test1 = upper_bound(a, a, 0, comp);
    assert(test1 == a);
    constexpr auto test2 = upper_bound(a, a + 1, 0, comp);
    assert(test2 == a + 1);
    constexpr auto test3 = upper_bound(a, a + 1, 1, comp);
    assert(test3 == a + 1);
    constexpr auto test4 = upper_bound(e, e + 7, 3, comp);
    assert(test4 == e + 5);
    constexpr auto test5 = upper_bound(e, e + 7, 4, comp);
    assert(test5 == e + 6);
    constexpr auto test6 = upper_bound(e, e + 7, 2, comp);
    assert(test6 == e + 3);
   }
  }

  // equal_range
  {
   {
    constexpr auto test1 = equal_range(a, a, 0);
    assert(test1.first == a);
    assert(test1.second == a);
    constexpr auto test2 = equal_range(a, a + 1, 0);
    assert(test2.first == a);
    assert(test2.second == a + 1);
    constexpr auto test3 = equal_range(a, a + 1, 1);
    assert(test3.first == a + 1);
    assert(test3.second == a + 1);
    constexpr auto test4 = equal_range(e, e + 7, 3);
    assert(test4.first == e + 3);
    assert(test4.second == e + 5);
   }
   {
    constexpr auto comp = less<int>();
    constexpr auto test1 = equal_range(a, a, 0, comp);
    assert(test1.first == a);
    assert(test1.second == a);
    constexpr auto test2 = equal_range(a, a + 1, 0, comp);
    assert(test2.first == a);
    assert(test2.second == a + 1);
    constexpr auto test3 = equal_range(a, a + 1, 1, comp);
    assert(test3.first == a + 1);
    assert(test3.second == a + 1);
    constexpr auto test4 = equal_range(e, e + 7, 3, comp);
    assert(test4.first == e + 3);
    assert(test4.second == e + 5);
   }
  }

  // binary_search
  {
   {
    constexpr bool test1 = binary_search(a, a, 0);
    assert(test1 == false);
    constexpr bool test2 = binary_search(a, a + 1, 0);
    assert(test2 == true);
    constexpr bool test3 = binary_search(a, a + 1, 1);
    assert(test3 == false);
    constexpr bool test4 = binary_search(a, a + 1, -1);
    assert(test4 == false);
    constexpr bool test5 = binary_search(e, e + 7, 0);
    assert(test5 == true);
    constexpr bool test6 = binary_search(e, e + 7, 1);
    assert(test6 == true);
    constexpr bool test7 = binary_search(e, e + 7, 2);
    assert(test7 == true);
    constexpr bool test8 = binary_search(e, e + 7, 3);
    assert(test8 == true);
    constexpr bool test9 = binary_search(e, e + 7, 4);
    assert(test9 == true);
    constexpr bool test10 = binary_search(e, e + 7, 5);
    assert(test10 == true);
    constexpr bool test11 = binary_search(e, e + 7, -1);
    assert(test11 == false);
    constexpr bool test12 = binary_search(e, e + 7, 6);
    assert(test12 == false);
   }
   {
    constexpr auto comp = less<int>();
    constexpr bool test1 = binary_search(a, a, 0, comp);
    assert(test1 == false);
    constexpr bool test2 = binary_search(a, a + 1, 0, comp);
    assert(test2 == true);
    constexpr bool test3 = binary_search(a, a + 1, 1, comp);
    assert(test3 == false);
    constexpr bool test4 = binary_search(a, a + 1, -1, comp);
    assert(test4 == false);
    constexpr bool test5 = binary_search(e, e + 7, 0, comp);
    assert(test5 == true);
    constexpr bool test6 = binary_search(e, e + 7, 1, comp);
    assert(test6 == true);
    constexpr bool test7 = binary_search(e, e + 7, 2, comp);
    assert(test7 == true);
    constexpr bool test8 = binary_search(e, e + 7, 3, comp);
    assert(test8 == true);
    constexpr bool test9 = binary_search(e, e + 7, 4, comp);
    assert(test9 == true);
    constexpr bool test10 = binary_search(e, e + 7, 5, comp);
    assert(test10 == true);
    constexpr bool test11 = binary_search(e, e + 7, -1, comp);
    assert(test11 == false);
    constexpr bool test12 = binary_search(e, e + 7, 6, comp);
    assert(test12 == false);
   }
  }

  // includes
  {
   {
    constexpr bool test1 = includes(a, a, a, a);
    assert(test1 == true);
    constexpr bool test2 = includes(a, a + 1, a, a);
    assert(test2 == true);
    constexpr bool test3 = includes(a, a, a, a + 1);
    assert(test3 == false);
    constexpr bool test4 = includes(a, a + 1, a, a + 1);
    assert(test4 == true);
    constexpr bool test5 = includes(e, e + 7, d, d + 4);
    assert(test5 == true);
   }
   {
    constexpr auto comp = less<int>();
    constexpr bool test1 = includes(a, a, a, a, comp);
    assert(test1 == true);
    constexpr bool test2 = includes(a, a + 1, a, a, comp);
    assert(test2 == true);
    constexpr bool test3 = includes(a, a, a, a + 1, comp);
    assert(test3 == false);
    constexpr bool test4 = includes(a, a + 1, a, a + 1, comp);
    assert(test4 == true);
    constexpr bool test5 = includes(e, e + 7, d, d + 4, comp);
    assert(test5 == true);
   }
  }

  // is_heap_until
  {
   {
    constexpr auto test1 = is_heap_until(a, a);
    assert(test1 == a);
    constexpr auto test2 = is_heap_until(a, a + 1);
    assert(test2 == a + 1);
    constexpr auto test3 = is_heap_until(b, b + 2);
    assert(test3 == b + 1);
    static constexpr int array1[2] = {1, 0};
    constexpr auto test4 = is_heap_until(array1, array1 + 2);
    assert(test4 == array1 + 2);
    constexpr auto test5 = is_heap_until(c, c + 3);
    assert(test5 == c + 1);
    static constexpr int array2[3] = {-1, 0, 1};
    constexpr auto test6 = is_heap_until(array2, array2 + 4);
    assert(test6 == array2 + 1);
    static constexpr int array3[3] = {0, -1, 1};
    constexpr auto test7 = is_heap_until(array3, array3 + 3);
    assert(test7 == array3 + 2);
    constexpr auto test8 = is_heap_until(e, e + 8);
    assert(test8 == e + 1);
    static constexpr int arr2[] = {10, 9, 7, 8, 5, 99, 99, 99, 99, 99};
    assert(is_heap_until(arr2, arr2 + 10) == arr2 + 5);
   }
   {
    constexpr auto comp = less<int>();
    constexpr auto test1 = is_heap_until(a, a, comp);
    assert(test1 == a);
    constexpr auto test2 = is_heap_until(a, a + 1, comp);
    assert(test2 == a + 1);
    constexpr auto test3 = is_heap_until(b, b + 2, comp);
    assert(test3 == b + 1);
    static constexpr int array1[2] = {1, 0};
    constexpr auto test4 = is_heap_until(array1, array1 + 2, comp);
    assert(test4 == array1 + 2);
    constexpr auto test5 = is_heap_until(c, c + 3, comp);
    assert(test5 == c + 1);
    static constexpr int array2[3] = {-1, 0, 1};
    constexpr auto test6 = is_heap_until(array2, array2 + 4, comp);
    assert(test6 == array2 + 1);
    static constexpr int array3[3] = {0, -1, 1};
    constexpr auto test7 = is_heap_until(array3, array3 + 3, comp);
    assert(test7 == array3 + 2);
    constexpr auto test8 = is_heap_until(e, e + 8, comp);
    assert(test8 == e + 1);
    static constexpr int arr2[] = {10, 9, 7, 8, 5, 99, 99, 99, 99, 99};
    assert(is_heap_until(arr2, arr2 + 10, comp) == arr2 + 5);
   }
  }

  // is_heap
  {
   {
    constexpr bool test1 = is_heap(a, a);
    assert(test1 == true);
    constexpr bool test2 = is_heap(a, a + 1);
    assert(test2 == true);
    static constexpr int arr1[] = {10, 9, 7, 8, 5, 6, 3, 1, 4, 2};
    constexpr bool test3 = is_heap(arr1, arr1 + 10);
    assert(test3 == true);
    static constexpr int arr2[] = {10, 9, 7, 8, 5, 99, 99, 99, 99, 99};
    constexpr bool test4 = is_heap(arr2, arr2 + 10);
    assert(test4 == false);
   }
   {
    constexpr auto comp = less<int>();
    constexpr bool test1 = is_heap(a, a, comp);
    assert(test1 == true);
    constexpr bool test2 = is_heap(a, a + 1, comp);
    assert(test2 == true);
    static constexpr int arr1[] = {10, 9, 7, 8, 5, 6, 3, 1, 4, 2};
    constexpr bool test3 = is_heap(arr1, arr1 + 10, comp);
    assert(test3 == true);
    static constexpr int arr2[] = {10, 9, 7, 8, 5, 99, 99, 99, 99, 99};
    constexpr bool test4 = is_heap(arr2, arr2 + 10, comp);
    assert(test4 == false);
   }
  }

  // min
  {
   {
    constexpr int test1 = min(0, 0);
    assert(test1 == 0);
    constexpr int test2 = min(0, 1);
    assert(test2 == 0);
    constexpr int test3 = min(1, 0);
    assert(test3 == 0);
    constexpr test test4 = min(test{0, 0}, test{0, 1});
    assert(test4.b == 0);
    constexpr test test5 = min(test{0, 0}, test{1, 1});
    assert(test5.b == 0);
    constexpr test test6 = min(test{1, 0}, test{0, 1});
    assert(test6.b == 1);
   }
  }

  // max
  {
   {
    constexpr int test1 = max(0, 0);
    assert(test1 == 0);
    constexpr int test2 = max(0, 1);
    assert(test2 == 1);
    constexpr int test3 = max(1, 0);
    assert(test3 == 1);
    constexpr test test4 = max(test{0, 0}, test{0, 1});
    assert(test4.b == 0);
    constexpr test test5 = max(test{0, 0}, test{1, 1});
    assert(test5.b == 1);
    constexpr test test6 = max(test{1, 0}, test{0, 1});
    assert(test6.b == 0);
   }
  }

  // minmax
  {
   constexpr auto test1 = minmax(0, 0);
   assert(test1.first == 0 && test1.second == 0);
   constexpr auto test2 = minmax(0, 1);
   assert(test2.first == 0 && test2.second == 1);
   constexpr auto test3 = minmax(1, 0);
   assert(test3.first == 0 && test3.second == 1);
   constexpr auto test4 = minmax(test{0, 0}, test{0, 1});
   assert(test4.first.b == 0 && test4.second.b == 1);
   constexpr auto test5 = minmax(test{0, 0}, test{1, 1});
   assert(test5.first.b == 0 && test5.second.b == 1);
   constexpr auto test6 = minmax(test{1, 0}, test{0, 1});
   assert(test6.first.b == 1 && test6.second.b == 0);
  }

  // min_element
  {
   constexpr auto test1 = min_element(a, a);
   assert(test1 == a);
   constexpr auto test2 = min_element(a, a + 1);
   assert(test2 == a);
   constexpr auto test3 = min_element(b, b + 2);
   assert(test3 == b);
   constexpr auto test4 = min_element(e + 6, e + 8);
   assert(test4 == e + 7);
   static constexpr test array[3] = {test{0, 0}, test{0, 1}, test{0, 2}};
   constexpr auto test5 = min_element(array, array + 3);
   assert(test5->b == 0);
  }

  // max_element
  {
   constexpr auto test1 = max_element(a, a);
   assert(test1 == a);
   constexpr auto test2 = max_element(a, a + 1);
   assert(test2 == a);
   constexpr auto test3 = max_element(b, b + 2);
   assert(test3 == b + 1);
   constexpr auto test4 = max_element(e + 6, e + 8);
   assert(test4 == e + 6);
   static constexpr test array[3] = {test{0, 0}, test{0, 1}, test{0, 2}};
   constexpr auto test5 = max_element(array, array + 3);
   assert(test5->b == 0);
  }

  // minmax_element
  {
   constexpr auto test1 = minmax_element(a, a);
   assert(test1.first == a);
   assert(test1.second == a);
   constexpr auto test2 = minmax_element(a, a + 1);
   assert(test2.first == a);
   assert(test2.second == a);
   constexpr auto test3 = minmax_element(b, b + 2);
   assert(test3.first == b);
   assert(test3.second == b + 1);
   constexpr auto test4 = minmax_element(e, e + 8);
   assert(test4.first == e);
   assert(test4.second == e + 6);
   static constexpr test array[3] = {test{0, 0}, test{0, 1}, test{0, 2}};
   constexpr auto test5 = minmax_element(array, array + 3);
   assert(test5.first->b == 0);
   assert(test5.second->b == 2);
  }

  // lexicographical_compare
  {
   constexpr bool test1 = lexicographical_compare(a, a, b, b);
   assert(test1 == false);
   constexpr bool test2 = lexicographical_compare(a, a, b, b + 1);
   assert(test2 == true);
   constexpr bool test3 = lexicographical_compare(a, a + 1, b, b);
   assert(test3 == false);
   static constexpr char s[] = "abc", t[] = "abcd";
   constexpr bool test4 = lexicographical_compare(s, s + 3, t, t + 3);
   assert(test4 == false);
   constexpr bool test5 = lexicographical_compare(s, s + 4, t, t + 5);
   assert(test5 == true);
   constexpr bool test6 = lexicographical_compare(s, s + 3, t, t + 2);
   assert(test6 == false);
  }
 }
}

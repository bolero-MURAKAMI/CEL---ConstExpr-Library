#include<cassert>
#include<sscrisk/cel/range/algorithm.hpp>

constexpr bool is_less_than_2(int i){ return i < 2; }
constexpr bool is_greater_than_1(int i){ return i > 1; }
constexpr bool are_greater_than_2(int i, int j){ return i > 2 && j > 2; }
constexpr bool abs_equal(int i, int j){ return (i < 0 ? -i : i) == (j < 0 ? -j : j); }

int main()
{
 using namespace sscrisk::cel::range;

 static constexpr int a[] = {0};
 static constexpr int b[] = {0, 1};
 static constexpr int c[] = {0, 1, 2};
 static constexpr int d[] = {0, 1, 2, 3};
 static constexpr int e[] = {0, 1, 2, 3, 3, 4, 5, 0};

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
  constexpr bool test1 = all_of(a, is_less_than_2);
  assert(test1);
  constexpr bool test2 = all_of(b, is_less_than_2);
  assert(test2);
  constexpr bool test3 = all_of(c, is_less_than_2);
  assert(!test3);
  constexpr bool test4 = all_of(d, is_less_than_2);
  assert(!test4);
 }

 // any_of
 {
  constexpr bool test1 = any_of(a, is_greater_than_1);
  assert(!test1);
  constexpr bool test2 = any_of(b, is_greater_than_1);
  assert(!test2);
  constexpr bool test3 = any_of(c, is_greater_than_1);
  assert(test3);
  constexpr bool test4 = any_of(d, is_greater_than_1);
  assert(test4);
 }

 // none_of
 {
  constexpr bool test1 = none_of(a, is_greater_than_1);
  assert(test1);
  constexpr bool test2 = none_of(b, is_greater_than_1);
  assert(test2);
  constexpr bool test3 = none_of(c, is_greater_than_1);
  assert(!test3);
  constexpr bool test4 = none_of(d, is_greater_than_1);
  assert(!test4);
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

 // find_end
 {
  constexpr auto test1 = find_end(e, a);
  assert(test1.begin() == e + 7);
 }

 // find_first_of
 {
  static constexpr int f[] = {6, 5};
  constexpr auto test1 = find_first_of(f, a);
  assert(test1.empty());
  constexpr auto test2 = find_first_of(f, e);
  assert(!test2.empty());
  assert(*test2.begin() == 5);
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

 // mismatch
 {
  constexpr auto test1 = mismatch(d, e);
  assert(test1.first == d + 4);
  assert(test1.second == e + 4);
 }

 // equal
 {
  {
   constexpr bool test2 = equal(d, e);
   assert(test2);
   static constexpr int f[] = {0, 1, 2, 4};
   constexpr bool test3 = equal(d, f);
   assert(!test3);
  }
  {
   constexpr bool test2 = equal(d, e, abs_equal);
   assert(test2);
   static constexpr int f[] = {0, 1, 2, 4};
   constexpr bool test3 = equal(d, f, abs_equal);
   assert(!test3);
   static constexpr int g[] = {0, -1, -2, -3};
   constexpr bool test4 = equal(d, g, abs_equal);
   assert(test4);
  }
 }

 // is_permutation
 {
  constexpr bool test1 = is_permutation(a, a);
  assert(test1 == true);
 }

 // search
 {
  constexpr auto test1 = search(b, a);
  assert(test1.begin() == b);
 }

 // search_n
 {
  constexpr auto test1 = search_n(e, 2, 3);
  assert(test1.begin() == e + 3);
 }

 // is_sorted_until
 {
  constexpr auto test1 = is_sorted_until(e);
  assert(test1.begin() == e);
  assert(test1.end() == e + 7);
 }

 // is_sorted
 {
  constexpr bool test1 = is_sorted(a);
  assert(test1 == true);
  constexpr bool test2 = is_sorted(e);
  assert(test2 == false);
 }
}

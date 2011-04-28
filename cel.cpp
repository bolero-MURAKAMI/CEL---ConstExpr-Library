#include<cassert>
#include<array>
#include<sscrisk/cel/cel.hpp>
#include<sscrisk/cel/cel.hpp>

constexpr bool is_less_than_3(int n)
{
 return n < 3;
}

constexpr bool is_greater_than_2(int n)
{
 return n > 2;
}

int main()
{
 using namespace std;
 using namespace sscrisk::cel;

 static constexpr int a[] = {0};
 static constexpr int b[] = {0, 1};
 static constexpr int c[] = {0, 1, 2};
 static constexpr int d[] = {0, 1, 2, 3};

 // begin and end
 {
  constexpr auto beg = begin(a);
  constexpr auto ed = end(a);
  assert(ed - beg == 1);
 }

 // all_of
 {
  // empty
  constexpr bool test = all_of(a, a, is_less_than_3);
  assert(test);
  // not empty
  constexpr bool testa = all_of(a, is_less_than_3);
  assert(testa);
  constexpr bool testb = all_of(b, is_less_than_3);
  assert(testb);
  constexpr bool testc = all_of(c, is_less_than_3);
  assert(testc);
  constexpr bool testd = all_of(d, is_less_than_3);
  assert(!testd);
 }

 // any_of
 {
  // empty
  constexpr bool test = any_of(a, a, is_greater_than_2);
  assert(!test);
  // not empty
  constexpr bool testa = any_of(a, is_greater_than_2);
  assert(!testa);
  constexpr bool testb = any_of(b, is_greater_than_2);
  assert(!testb);
  constexpr bool testc = any_of(c, is_greater_than_2);
  assert(!testc);
  constexpr bool testd = any_of(d, is_greater_than_2);
  assert(testd);
 }

 // none_of
 {
  // empty
  constexpr bool test = none_of(a, a, is_greater_than_2);
  assert(test);
  // not empty
  constexpr bool testa = none_of(a, is_greater_than_2);
  assert(testa);
  constexpr bool testb = none_of(b, is_greater_than_2);
  assert(testb);
  constexpr bool testc = none_of(c, is_greater_than_2);
  assert(testc);
  constexpr bool testd = none_of(d, is_greater_than_2);
  assert(!testd);
 }

 // find
 {
  // empty
  constexpr int const * test = find(d, d, 0);
  assert(test == d);
  constexpr int const * test1 = find(d, end(d), 0);
  assert(*test1 == 0);
  constexpr int const * test2 = find(d, end(d), 3);
  assert(*test2 == 3);
  constexpr int const * test3 = find(d, end(d), 100);
  assert(test3 == end(d));
  // constexpr auto test4 = ::sscrisk::cel::range::find2(d, 3);
  // assert(test4.end() - test4.begin() == 4);
  
 }
}

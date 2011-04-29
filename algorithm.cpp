#include<cassert>
#include<array>
#include<iostream>
#include<sscrisk/cel/algorithm.hpp>

// for name demangling.
#include<cstdlib>
#include <cxxabi.h>
class Demangle
{
private :
    char * realname ;

public :
    Demangle( std::type_info const & ti )
    {
        int status = 0 ;
        realname = abi::__cxa_demangle( ti.name(), 0, 0, &status ) ;
    }

    Demangle( Demangle const & ) = delete ;
    Demangle & operator = ( Demangle const & ) = delete ;

    ~Demangle()
    {
        std::free( realname ) ;
    }

    operator char const * () const
    {
        return realname ;
    }

} ;

constexpr bool is_less_than_3(int n)
{
 return n < 3;
}

constexpr bool is_greater_than_2(int n)
{
 return n > 2;
}

constexpr bool are_greater_than_3(int n, int m)
{
 return n > 3 && m > 3;
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
  // not empty
  constexpr int const * test1 = find(d, end(d), 0);
  assert(*test1 == 0);
  constexpr int const * test2 = find(d, end(d), 3);
  assert(*test2 == 3);
  constexpr int const * test3 = find(d, end(d), 100);
  assert(test3 == end(d));
  constexpr auto test4 = find(d, 3);
  constexpr auto test5 = test4.end();
  constexpr auto test6 = test4.begin();
  constexpr auto test7 = test5 - test6;
  assert(test7 == 1);
 }

 // find_if
 {
  constexpr auto iter = find_if(a, a, is_greater_than_2);
  assert(iter == a);
  {
   constexpr auto range = find_if(a, is_greater_than_2);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if(b, is_greater_than_2);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if(c, is_greater_than_2);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if(d, is_greater_than_2);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 1);
   assert(*first > 2);
  }
 }

 // find_if_not
 {
  constexpr auto iter = find_if_not(a, a, is_less_than_3);
  assert(iter == a);
  {
   constexpr auto range = find_if_not(a, is_less_than_3);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if_not(b, is_less_than_3);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if_not(c, is_less_than_3);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 0);
  }
  {
   constexpr auto range = find_if_not(d, is_less_than_3);
   constexpr auto first = range.begin(), last = range.end();
   constexpr auto diff = last - first;
   assert(diff == 1);
   assert(!(*first < 3));
  }
 }

 // adjacent_find
 {
  constexpr auto test1 = adjacent_find(a, a);
  assert(test1 == a);
  constexpr auto test2 = adjacent_find(begin(a), end(a));
  assert(test2 == end(a));
  constexpr auto test3 = adjacent_find(begin(b), end(b));
  assert(test3 == end(b));
  static constexpr int e[] = {0, 1, 2, 3, 3, 4, 5};
  constexpr auto test4 = adjacent_find(begin(e), end(e));
  assert(*test4 == 3);
  assert(*(test4 + 1) == 3);
  assert(test4 - e == 3);
  constexpr auto test5 = adjacent_find(begin(e), end(e), are_greater_than_3);
  assert(*test5 > 3);
  assert(*(test5 + 1) > 3);
  assert(test5 - e == 5);
 }

 // count
 {
  constexpr auto test1 = count(a, a, 0);
  assert(test1 == 0);
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
  constexpr auto test1 = count_if(a, a, is_less_than_3);
  assert(test1 == 0);
  constexpr auto test2 = count_if(a, is_less_than_3);
  assert(test2 == 1);
  constexpr auto test3 = count_if(d, is_less_than_3);
  assert(test3 == 3);
  static constexpr int e[] = {3, 1, 2, 3, 1, 2, 3};
  constexpr auto test4 = count_if(e, is_less_than_3);
  assert(test4 == 4);
  constexpr auto test5 = count_if(e, is_greater_than_2);
  assert(test5 == 3);
 }
}

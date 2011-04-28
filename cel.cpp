#include<cassert>
#include<array>
#include<iostream>
#include<sscrisk/cel/cel.hpp>

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
}

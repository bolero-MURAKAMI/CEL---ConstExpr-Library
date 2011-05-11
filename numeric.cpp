// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/numeric.hpp>

int main()
{
 using namespace sscrisk::cel;
 static constexpr int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

 // accumulate
 {
  constexpr int test1 = accumulate(a, a, 0);
  assert(test1 == 0);
  constexpr int test2 = accumulate(a, a + 10, 0);
  assert(test2 == 45);
  constexpr int test3 = accumulate(a, a, 1, multiplies<int>());
  assert(test3 == 1);
  constexpr int test4 = accumulate(a + 1, a + 6, 1, multiplies<int>());
  assert(test4 == 120);
 }
}

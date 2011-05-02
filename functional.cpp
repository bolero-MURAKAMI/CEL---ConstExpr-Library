// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/functional.hpp>

int main()
{
 {
  using namespace sscrisk::cel;
  {
   constexpr auto test = equal_to<int>();
   constexpr auto test1 = bind2nd(test, 3);
   constexpr bool test2 = test1(3);
   assert(test2 == true);
   constexpr bool test3 = bind2nd(equal_to<int>(), 3)(3);
   assert(test2 == test3);
  }
 }
}

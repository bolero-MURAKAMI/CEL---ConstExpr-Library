// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include<cassert>
#include<sscrisk/cel/array.hpp>
#include<sscrisk/cel/index_tuple.hpp>

template<std::size_t... Indexes>
constexpr sscrisk::cel::array<int, sizeof...(Indexes)> f(sscrisk::cel::index_tuple<Indexes...>)
{
 return {{Indexes...}};
}

int main()
{
 using namespace sscrisk::cel;
 constexpr auto a = f(index_tuple<>());
 assert(a.size() == 0);
 constexpr auto b = f(index_tuple<42>());
 assert(b.size() == 1);
 assert(b[0] == 42);
 constexpr auto c = f(index_tuple<42, 64>());
 assert(c.size() == 2);
 assert(c[0] == 42);
 assert(c[1] == 64);
 constexpr auto d = f(index_range<0, 10>::type());
 assert(d.size() == 10);
 assert(d[0] == 0);
 assert(d[9] == 9);
 constexpr auto e = f(index_range<0, 10, 3>::type());
 assert(e.size() == 4);
 assert(e[0] == 0);
 assert(e[3] == 9);
}

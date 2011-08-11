// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_LIST_HPP)
#define SSCRISK_CEL_LIST_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// list.hpp

#include<cstddef>

namespace sscrisk{ namespace cel{

template<class T, std::size_t N>
struct list
{
 T value;
 list<T, N - 1> next;
};

template<class T>
struct list<T, 0>
{};

template<class T>
struct list<T, 1>
{
 T value;
};

template<class T, std::size_t N>
constexpr bool empty(list<T, N> const & )
{
 return !N;
}

template<class T, std::size_t N>
constexpr std::size_t size(list<T, N> const & )
{
 return N;
}

template<class T, std::size_t N>
constexpr std::size_t max_size(list<T, N> const & )
{
 return N;
}

template<class T, std::size_t N>
constexpr T front(list<T, N> const & l)
{
 return l.value;
}

template<class T>
constexpr T back(list<T, 1> const & l)
{
 return l.value;
}

template<class T, std::size_t N>
constexpr T back(list<T, N> const & l)
{
 return back(l.next);
}

template<class T>
constexpr list<T, 0> pop_front(list<T, 1> const & )
{
 return {};
}

template<class T, std::size_t N>
constexpr list<T, N - 1> pop_front(list<T, N> const & l)
{
 return l.next;
}

template<class T>
constexpr list<T, 1> push_front(list<T, 0> const & , T const & value)
{
 return {value};
}

template<class T, std::size_t N>
constexpr list<T, N + 1> push_front(list<T, N> const & l, T const & value)
{
 return {value, l};
}

template<class T, std::size_t N>
constexpr list<T, 0> clear(list<T, N> const & )
{
 return {};
}

namespace detail{

template<class T>
constexpr T at(list<T, 1> const & l, std::size_t , std::size_t )
{
 return l.value;
}

template<class T, std::size_t N>
constexpr T at(list<T, N> const & l, std::size_t n, std::size_t current)
{
 return n == current ? l.value : at(l.next, n, current + 1);
}

}

template<class T, std::size_t N>
constexpr T at(list<T, N> const & l, std::size_t n)
{
 return detail::at(l, n, 0);
}

template<class T>
constexpr list<T, 0> make_list()
{
 return {};
}

template<class T>
constexpr list<T, 1> make_list(T element)
{
 return {element};
}

template<class T, class... U>
constexpr list<T, sizeof...(U) + 1> make_list(T head, U... args)
{
 return {head, make_list(args...)};
}

// algorithms
namespace algorithm{

// 25.3.4 Transform
template<class T, class UnaryOperation>
constexpr list<T, 0> transform(list<T, 0> const & , UnaryOperation )
{
 return {};
}

template<class T, class UnaryOperation>
constexpr list<T, 1> transform(list<T, 1> const & l, UnaryOperation op)
{
 return {op(l.value)};
}

template<class T, std::size_t N, class UnaryOperation>
constexpr list<T, N> transform(list<T, N> const & l, UnaryOperation op)
{
 return {op(l.value), transform(l.next, op)};
}

template<class T>
constexpr list<T, 0> iota(list<T, 0> const & , T value)
{
 return {};
}

template<class T>
constexpr list<T, 1> iota(list<T, 1> const & , T value)
{
 return {value};
}

template<class T, std::size_t N>
constexpr list<T, N> iota(list<T, N> const & , T value)
{
 return {value, iota(list<T, N - 1>(), value + 1)};
}

}

}}

#endif

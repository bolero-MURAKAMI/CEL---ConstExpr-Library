// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_ARRAY_HPP)
#define SSCRISK_CEL_ARRAY_HPP

// array.hpp

#include<cstddef>
#include<iterator>
#include<algorithm>
#include<utility>
#include<stdexcept>
#include<sscrisk/cel/algorithm.hpp>

namespace sscrisk{ namespace cel{

template<class T, std::size_t N>
struct array
{
 typedef T& reference;
 typedef T const & const_reference;
 typedef T* iterator;
 typedef T const * const_iterator;
 typedef std::size_t size_type;
 typedef std::ptrdiff_t difference_type;
 typedef T value_type;
 typedef T* pointer;
 typedef T const * const_pointer;
 typedef std::reverse_iterator<iterator> reverse_iterator;
 typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

 T elems[N ? N : 1];

 void fill(T const & value){ std::fill_n(begin(), N, value); }
 void swap(array<T, N>& rhs) noexcept(noexcept(std::swap(std::declval<T&>(), std::declval<T&>())))
 {
  std::swap_ranges(begin(), end(), rhs.begin());
 }

 iterator begin() noexcept{ return elems; }
 constexpr const_iterator begin() const noexcept{ return &elems[0]; }
 iterator end() noexcept{ return elems + N; }
 constexpr const_iterator end() const noexcept{ return &elems[0] + N; }

 reverse_iterator rbegin() noexcept{ return reverse_iterator(end()); }
 const_reverse_iterator rbegin() const noexcept{ return const_reverse_iterator(end()); }
 reverse_iterator rend() noexcept{ return reverse_iterator(begin()); }
 const_reverse_iterator rend() const noexcept{ return const_reverse_iterator(begin()); }

 constexpr const_iterator cbegin() const noexcept{ return elems; }
 constexpr const_iterator cend() const noexcept{ return elems + N; }
 const_reverse_iterator crbegin() const noexcept{ return const_reverse_iterator(end()); }
 const_reverse_iterator crend() const noexcept{ return const_reverse_iterator(begin()); }

 constexpr size_type size() noexcept{ return N; }
 constexpr size_type max_size() noexcept{ return N; }
 constexpr bool empty() noexcept{ return !N; }

 reference operator[](size_type n){ return elems[n]; }
 constexpr const_reference operator[](size_type n) const{ return elems[n]; }
 const_reference at(size_type n) const
 {
  if(n >= size())throw std::out_of_range("array<T, N>::at(size_type) const, out of range");
  return elems[n];
 }
 reference at(size_type n)
 {
  if(n >= size())throw std::out_of_range("array<T, N>::at(size_type), out of range");
  return elems[n];
 }
 reference front(){ return elems[0]; }
 constexpr const_reference front() const{ return elems[0]; }
 reference back(){ return elems[N - 1]; }
 constexpr const_reference back() const{ return elems[N - 1]; }
 T * data() noexcept{ return elems; }
 constexpr const T * data() const noexcept{ return elems; }
};

template<class T, std::size_t N>
constexpr bool operator==(array<T, N> const & x, array<T, N> const & y)
{
 return equal(x.begin(), x.end(), y.begin());
}

template<class T, std::size_t N>
constexpr bool operator!=(array<T, N> const & x, array<T, N> const & y)
{
 return !(x == y);
}

template<class T, std::size_t N>
constexpr bool operator<(array<T, N> const & x, array<T, N> const & y)
{
 return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<class T, std::size_t N>
constexpr bool operator>(array<T, N> const & x, array<T, N> const & y)
{
 return y < x;
}

template<class T, std::size_t N>
constexpr bool operator<=(array<T, N> const & x, array<T, N> const & y)
{
 return !(x > y);
}

template<class T, std::size_t N>
constexpr bool operator>=(array<T, N> const & x, array<T, N> const & y)
{
 return !(x < y);
}

}}

namespace std{

template<class T, std::size_t N>
void swap(sscrisk::cel::array<T, N>& x, sscrisk::cel::array<T, N>& y) noexcept(noexcept(x.swap(y)))
{
 x.swap(y);
}

template<class T>
class tuple_size;

template<std::size_t I, class T>
class tuple_element;

template<class T, std::size_t N>
struct tuple_size<sscrisk::cel::array<T, N>>
{
 static const std::size_t value = N;
};

template<std::size_t I, class T, std::size_t N>
struct tuple_element<I, sscrisk::cel::array<T, N>>
{
 static_assert(I < N, "out of bounds");
 typedef T type;
};

template<std::size_t I, class T, std::size_t N>
T& get(sscrisk::cel::array<T, N>& a) noexcept
{
 static_assert(I < N, "out of bounds");
 return a[I];
}

template<std::size_t I, class T, std::size_t N>
T&& get(sscrisk::cel::array<T, N>&& a) noexcept
{
 return std::move(get<I>(a));
}

template<std::size_t I, class T, std::size_t N>
constexpr T const & get(const sscrisk::cel::array<T, N>& a) noexcept
{
 static_assert(I < N, "out of bounds");
 return a[I];
}

}

#endif

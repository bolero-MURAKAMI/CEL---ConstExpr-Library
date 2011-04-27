#if !defined(SSCRISK_CEL_CEL_HPP)
#define SSCRISK_CEL_CEL_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// cel.hpp

#include<cstddef>

namespace sscrisk{ namespace cel{

  template<class T, size_t N>
  constexpr T const * begin(T const (& array)[N])
  {
   return array;
  }

  template<class T, size_t N>
  constexpr T const * end(T const (& array)[N])
  {
   return array + N;
  }

  // 25.2.1 All of
  template<class Iterator, class Predicate>
  constexpr bool all_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? true : pred(*first) && all_of(first + 1, last, pred);
  }

  template<class Range, class Predicate>
  constexpr bool all_of(Range const & range, Predicate pred)
  {
   return all_of(begin(range), end(range), pred);
  }

  // 25.2.2 Any of
  template<class Iterator, class Predicate>
  constexpr bool any_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? false : pred(*first) || any_of(first + 1, last, pred);
  }

  template<class Range, class Predicate>
  constexpr bool any_of(Range const & range, Predicate pred)
  {
   return any_of(begin(range), end(range), pred);
  }

  // 25.2.3 None of
  template <class InputIterator, class Predicate>
  constexpr bool none_of(InputIterator first, InputIterator last, Predicate pred)
  {
   return first == last ? true : !pred(*first) && none_of(first + 1, last, pred);
  }

  template<class Range, class Predicate>
  constexpr bool none_of(Range const & range, Predicate pred)
  {
   return none_of(begin(range), end(range), pred);
  }
}}

#endif

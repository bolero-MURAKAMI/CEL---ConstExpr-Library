#if !defined(SSCRISK_CEL_CEL_HPP)
#define SSCRISK_CEL_CEL_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// cel.hpp

#include<cstddef>
#include<iterator>
#include<type_traits>

namespace sscrisk{ namespace cel{

  template<class Range>
  constexpr typename Range::const_iterator begin(Range const & range)
  {
   return range.begin();
  }
  
  template<class T, size_t N>
  constexpr T const * begin(T const (& array)[N])
  {
   return array;
  }

  template<class Range>
  constexpr typename Range::const_iterator end(Range const & range)
  {
   return range.end();
  }
  
  template<class T, size_t N>
  constexpr T const * end(T const (& array)[N])
  {
   return array + N;
  }

  template<class Iterator>
  struct range_container
  {
   typedef Iterator const_iterator;
  private:
   Iterator first, last;
  public:
   constexpr range_container(Iterator first, Iterator last)
    : first(first), last(last)
    {}
   constexpr Iterator begin()const{ return first; }
   constexpr Iterator end()const{ return last; }
  };

  // 25.2.1 All of
  template<class Iterator, class Predicate>
  constexpr bool all_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? true : pred(*first) && all_of(first + 1, last, pred);
  }

  template<class Range, class Predicate>
  constexpr bool all_of(Range const & range, Predicate pred)
  {
   return all_of(sscrisk::cel::begin(range), sscrisk::cel::end(range), pred);
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

  // 25.2.5 Find
  template<class InputIterator, class T>
  constexpr InputIterator find(InputIterator first, InputIterator last, T const & value)
  {
   return first == last ? last : *first == value ? first : find(first + 1, last, value);
  }
  
  namespace range{
   template<class Range, class T>
   constexpr range_container<
    typename std::iterator_traits<
     typename std::decay<Range>::type
    >::const_iterator
   >
  find2(Range const & range, T const & value)
  {
   return {find(begin(range), end(range), value), end(range)};
  }
  }
  template<class InputIterator, class Predicate>
  InputIterator find_if(InputIterator first, InputIterator last,
                        Predicate pred);
  template<class InputIterator, class Predicate>
  InputIterator find_if_not(InputIterator first, InputIterator last,
                            Predicate pred);
}}

#endif

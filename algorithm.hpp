// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_ALGORITHM_HPP)
#define SSCRISK_CEL_ALGORITHM_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// algorithm.hpp

#include<cstddef>
#include<iterator>
#include<type_traits>
#include<sscrisk/cel/utility.hpp>
#include<sscrisk/cel/iterator.hpp>
#include<sscrisk/cel/functional.hpp>

namespace sscrisk{ namespace cel{

  // 25.2.1 All of
  template<class Iterator, class Predicate>
  constexpr bool all_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? true : pred(*first) == true && all_of(first + 1, last, pred);
  }

  // 25.2.2 Any of
  template<class Iterator, class Predicate>
  constexpr bool any_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? false : pred(*first) == true || any_of(first + 1, last, pred);
  }

  // 25.2.3 None of
  template <class Iterator, class Predicate>
  constexpr bool none_of(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? true : pred(*first) == false && none_of(first + 1, last, pred);
  }

  // 25.2.5 Find
  template<class Iterator, class T>
  constexpr Iterator find(Iterator first, Iterator last, T const & value)
  {
   return first == last || *first == value ? first : find(first + 1, last, value);
  }

  template<class Iterator, class Predicate>
  constexpr Iterator find_if(Iterator first, Iterator last, Predicate pred)
  {
   return first == last || pred(*first) != false ? first : find_if(first + 1, last, pred);
  }

  template<class Iterator, class Predicate>
  constexpr Iterator find_if_not(Iterator first, Iterator last, Predicate pred)
  {
   return first == last || pred(*first) == false ? first : find_if_not(first + 1, last, pred);
  }

  // 25.2.6 Find end
  template<class Iterator1, class Iterator2>
  constexpr Iterator1 find_end(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return first1 == last1 || first2 == last2 ? last1
    : search(first1, last1, first2, last2) == first1 && search(first1 + 1, last1, first2, last2) == last1
       ? first1
    : find_end(first1 + 1, last1, first2, last2);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr Iterator1 find_end(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2,
                               BinaryPredicate pred)
  {
   return first1 == last1 || first2 == last2 ? last1
    : search(first1, last1, first2, last2, pred) == first1
        && search(first1 + 1, last1, first2, last2, pred) == last1
       ? first1
    : find_end(first1 + 1, last1, first2, last2);
  }

  // 25.2.7 Find first
  template<class Iterator1, class Iterator2>
  constexpr Iterator1 find_first_of(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return first1 == last1 || find(first2, last2, *first1) != last2
    ? first1 : find_first_of(first1 + 1, last1, first2, last2);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr Iterator1 find_first_of(Iterator1 first1, Iterator1 last1,
                                   Iterator2 first2, Iterator2 last2, BinaryPredicate pred)
  {
   return first1 == last1 || find_if(first2, last2, bind2nd(pred, *first1)) != last2
    ? first1 : find_first_of(first1 + 1, last1, first2, last2, pred);
  }

  // 25.2.8 Adjacent find
  template<class Iterator>
  constexpr Iterator adjacent_find(Iterator first, Iterator last)
  {
   return first == last || first + 1 == last ? last
    : *first == *(first + 1) ? first : adjacent_find(first + 1, last);
  }

  template<class Iterator, class BinaryPredicate>
  constexpr Iterator adjacent_find(Iterator first, Iterator last, BinaryPredicate pred)
  {
   return first == last || first + 1 == last ? last
    : pred(*first, *(first + 1)) != false ? first : adjacent_find(first + 1, last, pred);
  }

  // 25.2.9 Count
  template<class Iterator, class T>
  constexpr typename std::iterator_traits<Iterator>::difference_type
  count(Iterator first, Iterator last, const T& value)
  {
   return first == last ? 0 : (*first == value ? 1 : 0) + count(first + 1, last, value);
  }

  template<class Iterator, class Predicate>
  constexpr typename std::iterator_traits<Iterator>::difference_type
  count_if(Iterator first, Iterator last, Predicate pred)
  {
   return first == last ? 0 : (pred(*first) != false ? 1 : 0) + count_if(first + 1, last, pred);
  }

  // 25.2.10 Mismatch
  template<class Iterator1, class Iterator2>
  constexpr pair<Iterator1, Iterator2>
  mismatch(Iterator1 first1, Iterator1 last1, Iterator2 first2)
  {
   return first1 == last1 || !(*first1 == *first2) ? pair<Iterator1, Iterator2>{first1, first2}
    : mismatch(first1 + 1, last1, first2 + 1);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr pair<Iterator1, Iterator2>
  mismatch(Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred)
  {
   return first1 == last1 || pred(*first1, *first2) == false ? pair<Iterator1, Iterator2>{first1, first2}
    : mismatch(first1 + 1, last1, first2 + 1);
  }

  // 25.2.11 Equal
  template<class Iterator1, class Iterator2>
  constexpr bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
  {
   return first1 == last1 ? true : *first1 == *first2 && equal(first1 + 1, last1, first2 + 1);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred)
  {
   return first1 == last1 ? true : pred(*first1, *first2) != false && equal(first1 + 1, last1, first2 + 1, pred);
  }

  namespace detail{

   template<class Iterator1, class Iterator2>
   constexpr bool is_permutation_impl(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator1 first1_)
   {
    return first1_ == last1 ? true
     : count(first1, last1, *first1_) == count(first2, first2 + distance(first1, last1), *first1_)
       && is_permutation_impl(first1, last1, first2, first1_ + 1) ? true
     : false;
   }

   template<class Iterator1, class Iterator2, class BinaryPredicate>
   constexpr bool is_permutation_impl(Iterator1 first1, Iterator1 last1, Iterator2 first2,
                                      Iterator1 first1_, BinaryPredicate pred)
   {
    return first1_ == last1 ? true
     : count_if(first1, last1, bind2nd(pred, *first1_))
        == count_if(first2, first2 + distance(first1, last1), bind2nd(pred, *first1_))
       && is_permutation_impl(first1, last1, first2, first1_ + 1, pred) ? true
     : false;
   }

  }

  // 25.2.12 Is permutation
  template<class Iterator1, class Iterator2>
  constexpr bool is_permutation(Iterator1 first1, Iterator1 last1, Iterator2 first2)
  {
   return detail::is_permutation_impl(first1, last1, first2, first1);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr bool is_permutation(Iterator1 first1, Iterator1 last1, Iterator2 first2, BinaryPredicate pred)
  {
   return detail::is_permutation_impl(first1, last1, first2, first1, pred);
  }

  // 25.2.13 Search
  template<class Iterator1, class Iterator2>
  constexpr Iterator1 search(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return first1 == last1 || first2 == last2 ? first1
    : distance(first1, last1) < distance(first2, last2) ? last1
    : *first1 == *first2 && search(first1 + 1, last1, first2 + 1, last2) == first1 + 1 ? first1
    : search(first1 + 1, last1, first2, last2);
  }

  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr Iterator1 search(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2,
                             BinaryPredicate pred)
  {
   return first1 == last1 || first2 == last2 ? first1
    : distance(first1, last1) < distance(first2, last2) ? last1
    : *first1 == *first2 && search(first1 + 1, last1, first2 + 1, last2, pred) == first1 + 1 ? first1
    : search(first1 + 1, last1, first2, last2, pred);
  }

  template<class Iterator, class Size, class T>
  constexpr Iterator search_n(Iterator first, Iterator last, Size count, const T& value)
  {
   return first == last || count == 0 ? first
    : first + 1 == last && count > 1 ? last
    : *first == value && search_n(first + 1, last, count - 1, value) == first + 1 ? first
    : search_n(first + 1, last, count, value);
  }

  template<class Iterator, class Size, class T, class BinaryPredicate>
  constexpr Iterator search_n(Iterator first, Iterator last, Size count, const T& value, BinaryPredicate pred)
  {
   return first == last || count == 0 ? first
    : first + 1 == last && count > 1 ? last
    : *first == value && search_n(first + 1, last, count - 1, value, pred) == first + 1 ? first
    : search_n(first + 1, last, count, value, pred);
  }

  // 25.4.1.5 is_sorted
  template<class Iterator>
  constexpr Iterator is_sorted_until(Iterator first, Iterator last)
  {
   return first == last || first + 1 == last ? last
    : *(first + 1) < *first ? first + 1
    : is_sorted_until(first + 1, last);
  }

  template<class Iterator, class Compare>
  constexpr Iterator is_sorted_until(Iterator first, Iterator last, Compare comp)
  {
   return first == last || first + 1 == last ? last
    : comp(*(first + 1), *first) != false ? first + 1
    : is_sorted_until(first + 1, last);
  }

  namespace range{

   namespace cel = ::sscrisk::cel;

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

   template<class Array>
   struct array_to_const_ptr
   {
    typedef typename std::decay<
     typename std::add_const<Array>::type
    >::type type;
   };

   template<class Iterator>
   struct range_container
   {
    typedef Iterator const_iterator;
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
   private:
    Iterator first, last;
   public:
    constexpr range_container(Iterator first, Iterator last)
     : first(first), last(last)
    {}
    constexpr Iterator begin()const{ return first; }
    constexpr Iterator end()const{ return last; }
    constexpr bool empty()const{ return first == last; }
   };

   // 25.2.1 All of
   template<class Range, class Predicate>
   constexpr bool all_of(Range const & range, Predicate pred)
   {
    return cel::all_of(begin(range), end(range), pred);
   }

   // 25.2.2 Any of
   template<class Range, class Predicate>
   constexpr bool any_of(Range const & range, Predicate pred)
   {
    return cel::any_of(begin(range), end(range), pred);
   }

   // 25.2.3 None of
   template<class Range, class Predicate>
   constexpr bool none_of(Range const & range, Predicate pred)
   {
    return cel::none_of(begin(range), end(range), pred);
   }

   // 25.2.5 Find
   template<class Range, class T>
   constexpr range_container<
    typename array_to_const_ptr<Range>::type
   >
   find(Range const & range, T const & value)
   {
    return {cel::find(begin(range), end(range), value), end(range)};
   }

   template<class Range, class Predicate>
   constexpr range_container<
    typename array_to_const_ptr<Range>::type
   >
   find_if(Range const & range, Predicate pred)
   {
    return {cel::find_if(begin(range), end(range), pred), end(range)};
   }

   template<class Range, class Predicate>
   constexpr range_container<
    typename array_to_const_ptr<Range>::type
   >
   find_if_not(Range const & range, Predicate pred)
   {
    return {cel::find_if_not(begin(range), end(range), pred), end(range)};
   }

   // 25.2.7 Find first
   template<class Range1, class Range2>
   constexpr range_container<
    typename array_to_const_ptr<Range1>::type
   >
   find_first_of(Range1 const & range1, Range2 const & range2)
   {
    return {cel::find_first_of(begin(range1), end(range1), begin(range2), end(range2)), end(range1)};
   }

   // 25.2.8 Adjacent find
   template<class Range>
   constexpr range_container<
    typename array_to_const_ptr<Range>::type
   >
   adjacent_find(Range const & range)
   {
    return {cel::adjacent_find(begin(range), end(range)), end(range)};
   }

   template<class Range, class BinaryPredicate>
   constexpr range_container<
    typename array_to_const_ptr<Range>::type
   >
   adjacent_find(Range const & range, BinaryPredicate pred)
   {
    return {cel::adjacent_find(begin(range), end(range), pred), end(range)};
   }

   // 25.2.9 Count
   template<class Range, class T>
   constexpr typename std::iterator_traits<typename array_to_const_ptr<Range>::type>::difference_type
   count(Range const & range, T const & value)
   {
    return cel::count(begin(range), end(range), value);
   }

   template<class Range, class Predicate>
   constexpr typename std::iterator_traits<typename array_to_const_ptr<Range>::type>::difference_type
   count_if(Range const & range, Predicate pred)
   {
    return cel::count_if(begin(range), end(range), pred);
   }

   // 25.2.11 Equal
   template<class Range1, class Range2>
   constexpr bool equal(Range1 const & range1, Range2 const & range2)
   {
    return cel::equal(begin(range1), end(range1), begin(range2));
   }

   template<class Range1, class Range2, class BinaryPredicate>
   constexpr bool equal(Range1 const & range1, Range2 const & range2, BinaryPredicate pred)
   {
    return cel::equal(begin(range1), end(range1), begin(range2), pred);
   }
  }

}}

#endif

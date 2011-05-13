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

  namespace detail{

   template<class Iterator1, class Iterator2>
   struct iter_equal_to
   {
    constexpr bool operator()(typename std::iterator_traits<Iterator1>::value_type const & x,
                              typename std::iterator_traits<Iterator2>::value_type const & y)const
    {
     return x == y;
    }
   };

  }

  // 25.2.6 Find end
  template<class Iterator1, class Iterator2, class BinaryPredicate>
  constexpr Iterator1 find_end(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2,
                               BinaryPredicate pred)
  {
   return first1 == last1 || first2 == last2 ? last1
    : search(first1, last1, first2, last2, pred) == first1
      && search(first1 + 1, last1, first2, last2, pred) == last1
       ? first1
    : find_end(first1 + 1, last1, first2, last2, pred);
  }

  template<class Iterator1, class Iterator2>
  constexpr Iterator1 find_end(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return find_end(first1, last1, first2, last2, detail::iter_equal_to<Iterator1, Iterator2>());
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
   return adjacent_find(first, last, equal_to<typename std::iterator_traits<Iterator>::value_type>());
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
  count(Iterator first, Iterator last, T const & value)
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
  constexpr Iterator search_n(Iterator first, Iterator last, Size count, T const & value)
  {
   return first == last || count == 0 ? first
    : first + 1 == last && count > 1 ? last
    : *first == value && search_n(first + 1, last, count - 1, value) == first + 1 ? first
    : search_n(first + 1, last, count, value);
  }

  template<class Iterator, class Size, class T, class BinaryPredicate>
  constexpr Iterator search_n(Iterator first, Iterator last, Size count, T const & value, BinaryPredicate pred)
  {
   return first == last || count == 0 ? first
    : first + 1 == last && count > 1 ? last
    : *first == value && search_n(first + 1, last, count - 1, value, pred) == first + 1 ? first
    : search_n(first + 1, last, count, value, pred);
  }

  // 25.4.1.5 is_sorted
  template<class Iterator>
  constexpr bool is_sorted(Iterator first, Iterator last)
  {
   return is_sorted_until(first, last) == last;
  }

  template<class Iterator, class Compare>
  constexpr bool is_sorted(Iterator first, Iterator last, Compare comp)
  {
   return is_sorted_until(first, last, comp) == last;
  }

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

  // 25.4.3.1 lower_bound
  template<class Iterator, class T>
  constexpr Iterator lower_bound(Iterator first, Iterator last, T const & value)
  {
   return first == last ? last
    : first + 1 == last ? *first < value ? last : first
    : *(first + distance(first, last) / 2) < value
       ? lower_bound(first + distance(first, last) / 2, last, value)
       : lower_bound(first, first + distance(first, last) / 2, value);
  }

  template<class Iterator, class T, class Compare>
  constexpr Iterator lower_bound(Iterator first, Iterator last, T const & value, Compare comp)
  {
   return first == last ? last
    : first + 1 == last ? comp(*first, value) ? last : first
    : comp(*(first + distance(first, last) / 2), value)
       ? lower_bound(first + distance(first, last) / 2, last, value, comp)
       : lower_bound(first, first + distance(first, last) / 2, value, comp);
  }

  // 25.4.3.2 upper_bound
  template<class Iterator, class T>
  constexpr Iterator upper_bound(Iterator first, Iterator last, T const & value)
  {
   return first == last ? last
    : first + 1 == last ? !(value < *first) ? last : first
    : !(value < *(first + distance(first, last) / 2))
       ? upper_bound(first + distance(first, last) / 2, last, value)
       : upper_bound(first, first + distance(first, last) / 2, value);
  }

  template<class Iterator, class T, class Compare>
  constexpr Iterator upper_bound(Iterator first, Iterator last, T const & value, Compare comp)
  {
   return first == last ? last
    : first + 1 == last ? !comp(value, *first) ? last : first
    : !comp(value, *(first + distance(first, last) / 2))
       ? upper_bound(first + distance(first, last) / 2, last, value, comp)
       : upper_bound(first, first + distance(first, last) / 2, value, comp);
  }

  // 25.4.3.3 equal_range
  template<class Iterator, class T>
  constexpr pair<Iterator, Iterator> equal_range(Iterator first, Iterator last, T const & value)
  {
   return {lower_bound(first, last, value), upper_bound(first, last, value)};
  }

  template<class Iterator, class T, class Compare>
  constexpr pair<Iterator, Iterator> equal_range(Iterator first, Iterator last, T const & value, Compare comp)
  {
   return {lower_bound(first, last, value, comp), upper_bound(first, last, value, comp)};
  }

  // 25.4.3.4 binary_search
  template<class Iterator, class T>
  constexpr bool binary_search(Iterator first, Iterator last, T const & value)
  {
   return first == last ? false
    : first + 1 == last ? !(*first < value) && !(value < *first) ? true : false
    : *(first + distance(first, last) / 2) < value ?
       binary_search(first + distance(first, last) / 2, last, value)
    : value < *(first + distance(first, last)) / 2 ?
       binary_search(first, first + distance(first, last) / 2, value)
    : true;
  }

  template<class Iterator, class T, class Compare>
  constexpr bool binary_search(Iterator first, Iterator last, T const & value, Compare comp)
  {
   return first == last ? false
    : first + 1 == last ? !comp(*first, value) && !comp(value, *first) ? true : false
    : comp(*(first + distance(first, last) / 2), value) ?
       binary_search(first + distance(first, last) / 2, last, value)
    : comp(value, *(first + distance(first, last)) / 2) ?
       binary_search(first, first + distance(first, last) / 2, value)
    : true;
  }

  template<class Iterator1, class Iterator2>
  constexpr bool includes(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return first2 == last2 ? true
    : first1 == last1 ? false
    : !(*first1 < *first2) && !(*first2 < *first1) ? includes(first1 + 1, last1, first2 + 1, last2)
    : includes(first1 + 1, last1, first2, last2);
  }

  template<class Iterator1, class Iterator2, class Compare>
  constexpr bool includes(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare comp)
  {
   return first2 == last2 ? true
    : first1 == last1 ? false
    : !comp(*first1, *first2) && !comp(*first2, *first1) ? includes(first1 + 1, last1, first2 + 1, last2)
    : includes(first1 + 1, last1, first2, last2);
  }

  namespace detail{

   template<class Iterator, class Compare>
   constexpr Iterator is_heap_until_impl(Iterator first, Iterator last, Compare comp, std::size_t n)
   {
    return first + n == last || comp(first[n], first[n / 2]) ? first + n
     : is_heap_until_impl(first, last, comp, n + 1);
   }

  }

  // 25.4.6.5 is_heap
  template<class Iterator>
  constexpr bool is_heap(Iterator first, Iterator last)
  {
   return is_heap_until(first, last) == last;
  }

  template<class Iterator, class Compare>
  constexpr bool is_heap(Iterator first, Iterator last, Compare comp)
  {
   return is_heap_until(first, last, comp) == last;
  }

  template<class Iterator>
  constexpr Iterator is_heap_until(Iterator first, Iterator last)
  {
   return is_heap_until(first, last, less<decltype(*first)>());
  }

  template<class Iterator, class Compare>
  constexpr Iterator is_heap_until(Iterator first, Iterator last, Compare comp)
  {
   return distance(first, last) < 2 ? last : detail::is_heap_until_impl(first, last, comp, 0);
  }

  // 25.4.7 Minimum and maximum
  template<class T>
  constexpr T const & min(T const & a, T const & b)
  {
   return min(a, b, less<T>());
  }

  template<class T, class Compare>
  constexpr T const & min(T const & a, T const & b, Compare comp)
  {
   return comp(b, a) ? b : a;
  }

  template<class T>
  constexpr T const & max(T const & a, T const & b)
  {
   return max(a, b, less<T>());
  }

  template<class T, class Compare>
  constexpr T const & max(T const & a, T const & b, Compare comp)
  {
   return comp(a, b) ? b : a;
  }

  template<class T>
  constexpr pair<T, T> minmax(T const & a, T const & b)
  {
   return minmax(a, b, less<T>());
  }

  template<class T, class Compare>
  constexpr pair<T, T> minmax(T const & a, T const & b, Compare comp)
  {
   return comp(b, a) ? pair<T, T>(b, a) : pair<T, T>(a, b);
  }

  namespace detail{

   template<class Iterator, class Compare>
   constexpr Iterator min_element_impl(Iterator first, Iterator last, Compare comp, Iterator min)
   {
    return first == last ? min : min_element_impl(first + 1, last, comp, comp(*first, *min) ? first : min);
   }

   template<class Iterator, class Compare>
   constexpr Iterator max_element_impl(Iterator first, Iterator last, Compare comp, Iterator max)
   {
    return first == last ? max : max_element_impl(first + 1, last, comp, comp(*max, *first) ? first : max);
   }

   template<class Iterator, class Compare>
   constexpr pair<Iterator, Iterator>
   minmax_element_impl(Iterator first, Iterator last, Compare comp, Iterator min, Iterator max)
   {
    return first == last ? pair<Iterator, Iterator>(min, max)
     : comp(*first, *min) ? minmax_element_impl(first + 1, last, comp, first, max)
     : minmax_element_impl(first + 1, last, comp, min, comp(*first, *max) ? max : first);
   }

  }

  template<class Iterator>
  constexpr Iterator min_element(Iterator first, Iterator last)
  {
   return min_element(first, last, less<typename std::iterator_traits<Iterator>::value_type>());
  }

  template<class Iterator, class Compare>
  constexpr Iterator min_element(Iterator first, Iterator last, Compare comp)
  {
   return detail::min_element_impl(first, last, comp, first);
  }

  template<class Iterator>
  constexpr Iterator max_element(Iterator first, Iterator last)
  {
   return max_element(first, last, less<typename std::iterator_traits<Iterator>::value_type>());
  }

  template<class Iterator, class Compare>
  constexpr Iterator max_element(Iterator first, Iterator last, Compare comp)
  {
   return detail::max_element_impl(first, last, comp, first);
  }

  template<class Iterator>
  constexpr pair<Iterator, Iterator> minmax_element(Iterator first, Iterator last)
  {
   return minmax_element(first, last, less<typename std::iterator_traits<Iterator>::value_type>());
  }

  template<class Iterator, class Compare>
  constexpr pair<Iterator, Iterator> minmax_element(Iterator first, Iterator last, Compare comp)
  {
   return detail::minmax_element_impl(first, last, comp, first, first);
  }

  template<class Iterator1, class Iterator2>
  constexpr bool lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
  {
   return lexicographical_compare(first1, last1, first2, last2, less<decltype(*first1 + *first2)>());
  }

  template<class Iterator1, class Iterator2, class Compare>
  constexpr bool
  lexicographical_compare(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2, Compare comp)
  {
   return first2 == last2 ? false
    : first1 == last1 || comp(*first1, *first2) ? true
    : comp(*first2, *first1) ? false
    : lexicographical_compare(first1 + 1, last1, first2 + 1, last2, comp);
  }

  namespace range{

   namespace cel = ::sscrisk::cel;

   template<class Range>
   constexpr typename Range::const_iterator begin(Range const & range)
   {
    return range.begin();
   }

   template<class T, std::size_t N>
   constexpr T const * begin(T const (& array)[N])
   {
    return array;
   }

   template<class Range>
   constexpr typename Range::const_iterator end(Range const & range)
   {
    return range.end();
   }

   template<class T, std::size_t N>
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

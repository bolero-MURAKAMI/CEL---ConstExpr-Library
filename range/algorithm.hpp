// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_RANGE_ALGORITHM_HPP)
#define SSCRISK_CEL_RANGE_ALGORITHM_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// algorithm.hpp

#include<sscrisk/cel/algorithm.hpp>

namespace sscrisk{ namespace cel{ namespace range{

   namespace cel = ::sscrisk::cel;

   template<class Range>
   constexpr typename Range::const_iterator begin(Range const & range)
   {
    return range.begin();
   }

   template<class Range>
   constexpr typename Range::const_iterator end(Range const & range)
   {
    return range.end();
   }

   template<class T, std::size_t N>
   constexpr T const * begin(T const (& array)[N])
   {
    return array;
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
    constexpr std::size_t size()const{ return distance(first, last); }
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

   // 25.2.6 Find end
   template<class Range1, class Range2>
   constexpr range_container<
    typename array_to_const_ptr<Range1>::type
   >
   find_end(Range1 const & range1, Range2 const & range2)
   {
    return {cel::find_end(begin(range1), end(range1), begin(range2), end(range2)), end(range1)};
   }

   template<class Range1, class Range2, class BinaryPredicate>
   constexpr range_container<
    typename array_to_const_ptr<Range1>::type
   >
   find_end(Range1 const & range1, Range2 const & range2, BinaryPredicate pred)
   {
    return {cel::find_end(begin(range1), end(range1), begin(range2), end(range2), pred), end(range1)};
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

   template<class Range1, class Range2>
   constexpr pair<typename array_to_const_ptr<Range1>::type, typename array_to_const_ptr<Range2>::type>
   mismatch(Range1 const & range1, Range2 const & range2)
   {
    return cel::mismatch(begin(range1), end(range1), begin(range2));
   }

   template<class Range1, class Range2, class BinaryPredicate>
   constexpr pair<typename array_to_const_ptr<Range1>::type, typename array_to_const_ptr<Range2>::type>
   mismatch(Range1 const & range1, Range2 const & range2, BinaryPredicate pred)
   {
    return cel::mismatch(begin(range1), end(range1), begin(range2), pred);
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

   // 25.2.12 Is permutation
   template<class Range1, class Range2>
   constexpr bool is_permutation(Range1 const & range1, Range2 const & range2)
   {
    return cel::is_permutation(begin(range1), end(range1), begin(range2));
   }

   template<class Range1, class Range2, class BinaryPredicate>
   constexpr bool is_permutation(Range1 const & range1, Range2 const & range2, BinaryPredicate pred)
   {
    return cel::is_permutation(begin(range1), end(range1), begin(range2), pred);
   }

   // 25.2.13 Search
   template<class Range1, class Range2>
   constexpr range_container<typename array_to_const_ptr<Range1>::type>
   search(Range1 const & range1, Range2 const & range2)
   {
    return {cel::search(begin(range1), end(range1), begin(range2), end(range2)), end(range1)};
   }

   template<class Range1, class Range2, class BinaryPredicate>
   constexpr range_container<typename array_to_const_ptr<Range1>::type>
   search(Range1 const & range1, Range2 const & range2, BinaryPredicate pred)
   {
    return {cel::search(begin(range1), end(range1), begin(range2), end(range2), pred), end(range1)};
   }

   template<class Range, class Size, class T>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   search_n(Range const & range, Size count, T const & value)
   {
    return {cel::search_n(begin(range), end(range), count, value), end(range)};
   }

   template<class Range, class Size, class T, class BinaryPredicate>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   search_n(Range const & range, Size count, T const & value, BinaryPredicate pred)
   {
    return {cel::search_n(begin(range), end(range), count, value, pred), end(range)};
   }

   // 25.4.1.5 is_sorted
   template<class Range>
   constexpr bool is_sorted(Range const & range)
   {
    return cel::is_sorted(begin(range), end(range));
   }

   template<class Range, class Compare>
   constexpr bool is_sorted(Range const & range, Compare comp)
   {
    return cel::is_sorted(begin(range), end(range), comp);
   }

   template<class Range>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   is_sorted_until(Range const & range)
   {
    return {begin(range), cel::is_sorted_until(begin(range), end(range))};
   }

   template<class Range, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   is_sorted_until(Range const & range, Compare comp)
   {
    return {begin(range), cel::is_sorted_until(begin(range), end(range), comp)};
   }

   // 25.4.3.1 lower_bound
   template<class Range, class T>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   lower_bound(Range const & range, const T& value)
   {
    return {begin(range), cel::lower_bound(begin(range), end(range), value)};
   }

   template<class Range, class T, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   lower_bound(Range const & range, const T& value, Compare comp)
   {
    return {begin(range), cel::lower_bound(begin(range), end(range), value, comp)};
   }

   // 25.4.3.2 upper_bound
   template<class Range, class T>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   upper_bound(Range const & range, const T& value)
   {
    return {cel::upper_bound(begin(range), end(range), value), end(range)};
   }

   template<class Range, class T, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   upper_bound(Range const & range, const T& value, Compare comp)
   {
    return {cel::upper_bound(begin(range), end(range), value, comp), end(range)};
   }

   // 25.4.3.3 equal_range
   template<class Range, class T>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   equal_range(Range const & range, const T& value)
   {
    return {cel::equal_range(begin(range), end(range), value).first,
            cel::equal_range(begin(range), end(range), value).second};
   }

   template<class Range, class T, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   equal_range(Range const & range, const T& value, Compare comp)
   {
    return {cel::equal_range(begin(range), end(range), value, comp).first,
            cel::equal_range(begin(range), end(range), value, comp).second};
   }

   // 25.4.3.4 binary_search
   template<class Range, class T>
   constexpr bool binary_search(Range const & range, const T& value)
   {
    return cel::binary_search(begin(range), end(range), value);
   }

   template<class Range, class T, class Compare>
   constexpr bool binary_search(Range const & range, const T& value, Compare comp)
   {
    return cel::binary_search(begin(range), end(range), value, comp);
   }

   // 25.4.5.1 includes
   template<class Range1, class Range2>
   constexpr bool includes(Range1 const & range1, Range2 const & range2)
   {
    return cel::includes(begin(range1), end(range1), begin(range2), end(range2));
   }

   template<class Range1, class Range2, class Compare>
   constexpr bool includes(Range1 const & range1, Range2 const & range2, Compare comp)
   {
    return cel::includes(begin(range1), end(range1), begin(range2), end(range2), comp);
   }

   // 25.4.6.5 is_heap
   template<class Range>
   constexpr bool is_heap(Range const & range)
   {
    return cel::is_heap(begin(range), end(range));
   }

   template<class Range, class Compare>
   constexpr bool is_heap(Range const & range, Compare comp)
   {
    return cel::is_heap(begin(range), end(range), comp);
   }

   template<class Range>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   is_heap_until(Range const & range)
   {
    return {begin(range), cel::is_heap_until(begin(range), end(range))};
   }

   template<class Range, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   is_heap_until(Range const & range, Compare comp)
   {
    return {begin(range), cel::is_heap_until(begin(range), end(range), comp)};
   }

   // 25.4.7 Minimum and maximum
   template<class Range>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   min_element(Range const & range)
   {
    return {cel::min_element(begin(range), end(range)), end(range)};
   }

   template<class Range, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   min_element(Range const & range, Compare comp)
   {
    return {cel::min_element(begin(range), end(range), comp), end(range)};
   }

   template<class Range>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   max_element(Range const & range)
   {
    return {cel::max_element(begin(range), end(range)), end(range)};
   }

   template<class Range, class Compare>
   constexpr range_container<typename array_to_const_ptr<Range>::type>
   max_element(Range const & range, Compare comp)
   {
    return {cel::max_element(begin(range), end(range), comp), end(range)};
   }

   template<class Range>
   constexpr pair<
    range_container<typename array_to_const_ptr<Range>::type>,
    range_container<typename array_to_const_ptr<Range>::type>
   >
   minmax_element(Range const & range)
   {
    return {{cel::minmax_element(begin(range), end(range)).first, end(range)},
            {cel::minmax_element(begin(range), end(range)).second, end(range)}};
   }

   template<class Range, class Compare>
   constexpr pair<
    range_container<typename array_to_const_ptr<Range>::type>,
    range_container<typename array_to_const_ptr<Range>::type>
   >
   minmax_element(Range const & range, Compare comp)
   {
    return {{cel::minmax_element(begin(range), end(range), comp).first, end(range)},
            {cel::minmax_element(begin(range), end(range), comp).second, end(range)}};
   }

   // 25.4.8 Lexicographical comparison
   template<class Range1, class Range2>
   constexpr bool lexicographical_compare(Range1 const & range1, Range2 const & range2)
   {
    return cel::lexicographical_compare(begin(range1), end(range1), begin(range2), end(range2));
   }

   template<class Range1, class Range2, class Compare>
   constexpr bool lexicographical_compare(Range1 const & range1, Range2 const & range2, Compare comp)
   {
    return cel::lexicographical_compare(begin(range1), end(range1), begin(range2), end(range2), comp);
   }

}}}

#endif

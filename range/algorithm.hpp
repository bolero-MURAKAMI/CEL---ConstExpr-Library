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

// algorithm.hop

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

}}}

#endif
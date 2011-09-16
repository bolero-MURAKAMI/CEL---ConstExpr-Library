// Copyright (C) 2011 RiSK (sscrisk)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(SSCRISK_CEL_INDEX_TUPLE_HPP)
#define SSCRISK_CEL_INDEX_TUPLE_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1020
#pragma once
#endif

// index_tuple.hpp

#include<cstddef>

namespace sscrisk{ namespace cel{

template<std::size_t... Indexes>
struct index_tuple
{};

template<std::size_t Start, std::size_t Finish, std::size_t Step = 1, class Acc = index_tuple<>,
         bool Break = Start >= Finish>
struct index_range
{
 typedef Acc type;
};

template<std::size_t Start, std::size_t Finish, std::size_t Step, std::size_t... Indexes>
struct index_range<Start, Finish, Step, index_tuple<Indexes...>, false>
 : index_range<Start + Step, Finish, Step, index_tuple<Indexes..., Start>>
{};

}}

#endif

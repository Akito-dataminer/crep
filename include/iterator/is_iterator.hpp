/*****************************
 * iterator/is_iterator.hpp
 *****************************/

#pragma once

#include <iterator>
#include <utility>

#include "config/config.hpp"
#include "type_traits/has_member.hpp"
#include "util/util.hpp"

namespace crep {

namespace detail {

MAKE_TYPE_HAS( iterator_category )

template <typename MaybeInt>
STATIC_CONSTEXPR bool is_int_v = std::is_integral_v<MaybeInt> && std::is_signed_v<MaybeInt>;

}  // namespace detail

template <typename MaybeIterator>
STATIC_CONSTEXPR bool has_iterator_category_v = detail::has_iterator_category_t<MaybeIterator>::value;

#if CXX_STD < 202002
template <typename MaybeIterator>
STATIC_CONSTEXPR bool does_satisfy_minimum_iterator_requirement_v =
    std::is_invocable_v<decltype( &MaybeIterator::operator* ), MaybeIterator> &&
    std::is_same_v<decltype( ++std::declval<MaybeIterator>() ), MaybeIterator &> &&
    std::is_same_v<
        std::remove_cv_t<std::remove_reference_t<decltype( *std::declval<MaybeIterator>()++ )>>,
        typename MaybeIterator::value_type> &&
    std::is_swappable_v<decltype( std::declval<typename MaybeIterator::value_type>() )> &&
    std::is_copy_constructible_v<MaybeIterator> && std::is_copy_assignable_v<MaybeIterator> &&
    std::is_destructible_v<MaybeIterator> &&
    detail::is_int_v<typename std::iterator_traits<MaybeIterator>::difference_type>;
#else
#endif

}  // namespace crep

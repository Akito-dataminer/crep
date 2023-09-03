/*****************************
 * include/iterator/index_t.hpp
 *****************************/

#pragma once

#include <utility>

#include "iterator/is_iterator.hpp"
#include "type_traits/has_member.hpp"
#include "util/util.hpp"

namespace crep {

namespace detail {

MAKE_TYPE_HAS( iterator )
MAKE_TYPE_HAS( const_iterator )
MAKE_TYPE_HAS( reverse_iterator )
MAKE_TYPE_HAS( const_reverse_iterator )

template <typename MaybeUInt>
STATIC_CONSTEXPR bool is_uint_v = std::is_integral_v<MaybeUInt> && std::is_unsigned_v<MaybeUInt>;

}  // namespace detail

template <typename IndexT, util::if_nullp_c<detail::is_uint_v<IndexT>> = nullptr>
STATIC_CONSTEXPR IndexT npos_v = -1;

template <typename IndexT>
class index_t {
public:
  using value_type = IndexT;

  constexpr index_t() : index_( npos_v<IndexT> ) {}
  template <typename ContainerT, util::if_nullp_c<detail::has_const_iterator_t<ContainerT>::value> = nullptr>
  constexpr index_t( ContainerT const & container, typename ContainerT::const_iterator const &citr ) : index_( npos_v<IndexT> ) {
    if ( citr != container.cbegin() ) {
      index_ = std::distance( container.cbegin(), citr );
    }
  }
  constexpr index_t( index_t const & ) = default;
  constexpr index_t &operator=( index_t const & ) = default;
  constexpr index_t( index_t && ) noexcept = default;
  constexpr index_t &operator=( index_t && ) noexcept = default;
  ~index_t() = default;

  constexpr operator value_type() { return index_; }

private:
  value_type index_;
};

}  // namespace crep

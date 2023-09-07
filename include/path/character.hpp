/*****************************
 * path/character.hpp
 *****************************/

#pragma once

#include <utility>

namespace crep {

namespace character {

namespace detail {

template <typename CharT, std::size_t N>
struct character_list_impl {
public:
  using value_type = CharT;
  using size_type = std::size_t;

  constexpr explicit character_list_impl() : list_{ '\0' } {}
  template <size_type... INDICES>
  constexpr character_list_impl( CharT const ( &char_list )[N], std::index_sequence<INDICES...> )
      : list_{ char_list[INDICES]... } {}
  constexpr character_list_impl( character_list_impl const & ) = default;
  constexpr character_list_impl( character_list_impl && ) noexcept = default;
  ~character_list_impl() = default;

  CharT list_[N];
};

}  // namespace detail

template <typename CharT, std::size_t N>
struct character_list {
  using container_type = detail::character_list_impl<CharT, N>;
  using value_type = typename container_type::value_type;
  using size_type = typename container_type::size_type;

  constexpr character_list( CharT const ( &char_array )[N] )
      : list_impl_( char_array, std::make_index_sequence<N>() ) {}
  constexpr character_list( character_list const & ) = default;
  constexpr character_list &operator=( character_list const & ) = default;
  constexpr character_list( character_list && ) noexcept = default;
  constexpr character_list &operator=( character_list && ) noexcept = default;
  ~character_list() = default;

  constexpr size_type size() const noexcept { return N; }
  constexpr value_type operator[]( size_type const index ) const noexcept { return list_impl_.list_[index]; }

  container_type list_impl_;

  constexpr bool is_there( value_type const &maybe_member ) const noexcept {
    bool result = false;
    for ( size_type i = 0; i < size(); ++i ) {
      if ( list_impl_.list_[i] == maybe_member ) {
        result = true;
      }
    }
    return result;
  }
};

}  // namespace character

}  // namespace crep

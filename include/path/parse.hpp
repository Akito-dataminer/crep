/*****************************
 * path/parse.hpp
 *****************************/

#pragma once

#include "config/config.hpp"
#include "util/util.hpp"

#include <vector>

namespace path {

namespace parse {

enum class role {
  ROOT,
  DELIMITER,
  BRANCH,  // is alias of path element

  TYPE_NUM
};

class branch_parse {
public:
  explicit branch_parse() = default;
  constexpr branch_parse( role const type, std::size_t const index, std::size_t const length )
      : branch_type_( type ), head_index_( index ), length_( length ) {}
  constexpr branch_parse( branch_parse const & ) = default;
  constexpr branch_parse &operator=( branch_parse const & ) = default;
  constexpr branch_parse( branch_parse && ) noexcept = default;
  constexpr branch_parse &operator=( branch_parse && ) noexcept = default;
  ~branch_parse() = default;

  constexpr role type() const noexcept { return branch_type_; }
  constexpr std::size_t index() const noexcept { return head_index_; }
  constexpr std::size_t length() const noexcept { return length_; }

private:
  role branch_type_;
  std::size_t head_index_;
  std::size_t length_;
};

class index {
public:
  explicit index() = default;
  index( std::string const & );
  index( index const & ) = default;
  index &operator=( index const & ) = default;
  index( index && ) noexcept = default;
  index &operator=( index && ) noexcept = default;
  ~index() = default;

  branch_parse const &operator[]( std::size_t const index ) const noexcept { return token_sequence_[index]; }
  branch_parse const &at( std::size_t const index ) const {
    if ( index > token_sequence_.size() ) {
      throw std::range_error( "out of range" );
    }
    return token_sequence_[index];
  }
  std::size_t branch_num() const noexcept { return token_sequence_.size(); }

private:
  std::vector<branch_parse> token_sequence_;

  role type_detection( std::string::const_iterator &, std::size_t const ) const;
  std::size_t token_length( std::string::const_iterator &, role const ) const noexcept;
};

}  // namespace parse

}  // namespace path

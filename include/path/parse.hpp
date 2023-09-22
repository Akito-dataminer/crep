/*****************************
 * path/parse.hpp
 *****************************/

#pragma once

#include <vector>

#include "config/config.hpp"
#include "util/throw_if.hpp"
#include "util/util.hpp"

namespace crep {

namespace path {

namespace parse {

enum class role {
  ROOT,
  DELIMITER,
  BRANCH,  // is alias of path element

  TYPE_NUM
};

class branch_token {
public:
  explicit branch_token() = default;
  constexpr branch_token( role const type, std::size_t const index, std::size_t const length )
      : branch_type_( type ), head_index_( index ), length_( length ) {}
  constexpr branch_token( branch_token const & ) = default;
  constexpr branch_token &operator=( branch_token const & ) = default;
  constexpr branch_token( branch_token && ) noexcept = default;
  constexpr branch_token &operator=( branch_token && ) noexcept = default;
  ~branch_token() = default;

  constexpr role type() const noexcept { return branch_type_; }
  constexpr std::size_t index() const noexcept { return head_index_; }
  constexpr std::size_t length() const noexcept { return length_; }

private:
  role branch_type_;
  std::size_t head_index_;
  std::size_t length_;
};

class branch_parse {
public:
  explicit branch_parse() = default;
  branch_parse( std::string const & );
  branch_parse( branch_parse const & ) = default;
  branch_parse &operator=( branch_parse const & ) = default;
  branch_parse( branch_parse && ) noexcept = default;
  branch_parse &operator=( branch_parse && ) noexcept = default;
  ~branch_parse() = default;

  std::string operator[]( std::size_t const index ) const noexcept { return getString( index ); }
  std::string at( std::size_t const index ) const {
    throw_if<std::range_error>( index > token_sequence_.size(), "out of range" );
    return getString( index );
  }
  std::size_t size() const noexcept { return token_sequence_.size(); }

private:
  std::string original_string_;
  std::vector<branch_token> token_sequence_;

  inline std::string getString( std::size_t const index ) const noexcept {
    auto required_token = token_sequence_[index];
    return original_string_.substr( required_token.index(), required_token.length() );
  }

  role type_detection( std::string::const_iterator &, std::size_t const ) const;
  std::size_t token_length( std::string::const_iterator &, role const ) const noexcept;
};

}  // namespace parse

}  // namespace path

}  // namespace crep

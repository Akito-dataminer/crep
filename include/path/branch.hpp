/*****************************
 * path/branch.hpp
 *****************************/

#pragma once

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

#include "config/config.hpp"
#include "util/util.hpp"

namespace path {

namespace detail {

enum class role {
  ROOT,
  DELIMITER,
  BRANCH,

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

class index {
public:
  explicit index() = default;
  index( std::string const & );
  index( index const & ) = default;
  index &operator=( index const & ) = default;
  index( index && ) noexcept = default;
  index &operator=( index && ) noexcept = default;
  ~index() = default;

  branch_token const &operator[]( std::size_t const index ) const noexcept { return token_sequence_[index]; }
  branch_token const &at( std::size_t const index ) const {
    if ( index > token_sequence_.size() ) {
      throw std::range_error( "out of range" );
    }
    return token_sequence_[index];
  }
  std::size_t branch_num() const noexcept { return token_sequence_.size(); }

private:
  std::vector<branch_token> token_sequence_;

  role type_detection( std::string::const_iterator &, std::size_t const ) const;
  std::size_t token_length( std::string::const_iterator &, role const ) const noexcept;
};

}  // namespace detail

class branch;

// Define conditions by concept and metafunction.
#ifdef __cpp_concepts
template <typename T>
concept convertible_to_branch = std::is_convertible_v<T, branch>;
#else
template <typename T>
STATIC_CONSTEXPR bool const is_convertible_to_branch = std::is_convertible_v<T, branch>;
#endif

// Absorb the difference between concepts and meta-functions.
#ifdef __cpp_concepts
#  define TEMPLATE_HEAD_BRANCH template <convertible_to_branch T>
#else
#  define TEMPLATE_HEAD_BRANCH template <typename T, util::if_nullp_c<is_convertible_to_branch<T>> * = nullptr>
#endif

class branch {
public:
  explicit branch() = delete;
  branch( std::string const & );
  branch( branch const & ) = default;
  branch &operator=( branch const & ) = default;
  branch( branch && ) noexcept = default;
  branch &operator=( branch && ) noexcept = default;
  ~branch() = default;

  [[deprecated]] void modify( std::function<void( std::string & )> );
  std::string to_string() noexcept { return path_element_; }
  std::string const &to_string() const noexcept { return path_element_; }

  TEMPLATE_HEAD_BRANCH
  inline branch &operator+=( T const &rhs ) noexcept { return this->connect<T>( rhs ); }

  TEMPLATE_HEAD_BRANCH
  friend inline branch operator+( branch const &lhs, T const &rhs ) noexcept { return branch( lhs ) += rhs; }

  friend inline bool operator==( branch const &lhs, branch const &rhs ) noexcept {
    return lhs.to_string() == rhs.to_string();
  }
  friend inline bool operator!=( branch const &lhs, branch const &rhs ) noexcept { return !( lhs == rhs ); }

  branch operator[]( std::size_t const index ) const noexcept {
    auto i = index_[index].index();
    auto len = index_[index].length();
    return branch( path_element_.substr( i, len ) );
  }

private:
  std::string path_element_;
  detail::index index_;

  // 不正な文字列が使われていないかどうかを調べる
  void isCorrect( std::string const & ) const;

  TEMPLATE_HEAD_BRANCH
  branch &connect( T const &rhs ) noexcept {
    path_element_ += PATH_SEPARATOR;
    if constexpr ( std::is_same_v<T, branch> ) {
      path_element_ += rhs.path_element_;
    } else {
      path_element_ += rhs;
    }
    return *this;
  }
};

}  // namespace path

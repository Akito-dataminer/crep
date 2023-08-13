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

class branch;

// Define conditions by concept and metafunction.
#ifdef __cpp_concepts
template <typename T>
concept convirtible_to_branch = std::is_convertible_v<T, branch>;
#else
template <typename T>
STATIC_CONSTEXPR bool const is_convertible_to_branch = std::is_convertible_v<T, branch>;
#endif

// Absorb the difference between concepts and meta-functions.
#ifdef __cpp_concepts
#  define TEMPLATE_HEAD_BRANCH template <convirtible_to_branch T>
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

  friend inline constexpr bool operator==( branch const &lhs, branch const &rhs ) noexcept {
    return lhs.to_string() == rhs.to_string();
  }
  friend inline constexpr bool operator!=( branch const &lhs, branch const &rhs ) noexcept { return !( lhs == rhs ); }

private:
  std::string path_element_;

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

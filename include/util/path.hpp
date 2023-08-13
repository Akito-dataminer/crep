/*****************************
 * util/path
 *****************************/

#pragma once

#include "config/config.hpp"

#include <functional>
#include <string>
#include <type_traits>
#include <vector>
#include <type_traits>

namespace path {

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths );
std::vector<std::string> recursive_scan_directory( std::string const &scanning_path );

class joint;

#ifdef __cpp_concepts
template <typename T>
concept convirtible_to_joint = std::is_convertible_v<T, joint>;
#else
template<typename T>
STATIC_CONSTEXPR bool const is_jointable_v = std::is_convertible_v<T, joint>;

template<typename T>
struct Jointable {
  using type = std::enable_if_t<is_jointable_v<T>, std::type_identity<T>>;
};
#endif

#if __cpp_concepts
#  define TEMPLATE_HEAD_JOINTABLE template <convirtible_to_joint T>
#  define JOINTABLE_TYPE T
#else
#  define TEMPLATE_HEAD_JOINTABLE template <convirtible_to_joint Jointable>
#  define JOINTABLE_TYPE Jointable<T>
#endif

class joint {
public:
  explicit joint() = delete;
  joint( std::string const & );
  joint( joint const & ) = default;
  joint &operator=( joint const & ) = default;
  joint( joint && ) noexcept = default;
  joint &operator=( joint && ) noexcept = default;
  ~joint() = default;

  [[deprecated]] void modify( std::function<void ( std::string & )> );
  std::string to_string() noexcept { return path_element_; }
  std::string const & to_string() const noexcept { return path_element_; }

  TEMPLATE_HEAD_JOINTABLE
  inline joint &operator+= ( JOINTABLE_TYPE const &rhs ) noexcept {
    return concate<T>( rhs );
  }

  TEMPLATE_HEAD_JOINTABLE
  friend inline joint operator+( joint const &lhs, JOINTABLE_TYPE const &rhs ) noexcept {
    return joint( lhs ) += rhs;
  }

  friend inline constexpr bool operator== ( joint const & lhs, joint const & rhs ) noexcept {
    return lhs.to_string() == rhs.to_string();
  }
  friend inline constexpr bool operator!= ( joint const & lhs, joint const & rhs ) noexcept {
    return !( lhs == rhs );
  }
private:
  std::string path_element_;

  // 不正な文字列が使われていないかどうかを調べる
  void isCorrect( std::string const & ) const;

  TEMPLATE_HEAD_JOINTABLE
  joint &concate( JOINTABLE_TYPE const &rhs ) noexcept;
};

TEMPLATE_HEAD_JOINTABLE
joint& joint::concate( JOINTABLE_TYPE const &rhs ) noexcept {
  path_element_ += PATH_SEPARATOR;
  if constexpr ( std::is_same_v<JOINTABLE_TYPE, joint> ) {
    path_element_ += rhs.path_element_;
  } else {
    path_element_ += rhs;
  }
  return *this;
}

} // path

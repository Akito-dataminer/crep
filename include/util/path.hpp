/*****************************
 * util/path
 *****************************/

#pragma once

#include "config/config.hpp"

#include <functional>
#include <string>
#include <type_traits>
#include <vector>

namespace path {

void recursive_scan_directory( std::string const &scanning_path, std::vector<std::string> &paths );
std::vector<std::string> recursive_scan_directory( std::string const &scanning_path );

class joint;

template <typename T>
concept convirtible_to_joint = std::is_convertible_v<T, joint>;

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

  template<convirtible_to_joint Jointable>
  inline joint& operator+= ( Jointable const &rhs ) noexcept {
    return concate( rhs );
  }

  template<convirtible_to_joint Jointable>
  friend inline joint operator+ ( joint const &lhs, Jointable const &rhs ) noexcept {
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

  template <convirtible_to_joint Jointable>
  joint &concate( Jointable const &rhs ) noexcept;
};

template<convirtible_to_joint Jointable>
joint& joint::concate( Jointable const &rhs ) noexcept {
  path_element_ += PATH_SEPARATOR;
  if constexpr ( std::is_same_v<Jointable, joint> ) {
    path_element_ += rhs.path_element_;
  } else {
    path_element_ += rhs;
  }
  return *this;
}

} // path

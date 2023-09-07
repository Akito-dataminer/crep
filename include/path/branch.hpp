/*****************************
 * path/branch.hpp
 *****************************/

#pragma once

#include <string>
#include <type_traits>
#include <vector>

#include "config/config.hpp"
#include "iterator/index_t.hpp"
#include "path/parse.hpp"
#include "util/util.hpp"

namespace crep {

namespace path {

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
  using container_type = std::vector<std::string>;
  using iterator = container_type::iterator;
  using const_iterator = container_type::const_iterator;
  using reverse_iterator = container_type::reverse_iterator;
  using const_reverse_iterator = container_type::const_reverse_iterator;
  using index_type = crep::index_t<container_type::size_type>;

  explicit branch() = delete;
  branch( std::string const & );
  branch( branch const & ) = default;
  branch &operator=( branch const & ) = default;
  branch( branch && ) noexcept = default;
  branch &operator=( branch && ) noexcept = default;
  ~branch() = default;

  // [[deprecated]] void modify( std::function<void( std::string & )> );
  std::string to_string() const noexcept { return buildBranch(); }
  inline bool is_path() const noexcept { return ( is_absolute_path() || is_relative_path() ); }
  inline bool is_absolute_path() const noexcept { return ( isRoot( path_element_.cbegin() ) ); }
  inline bool is_relative_path() const noexcept { return ( isCurrentDirectory( path_element_.cbegin() ) ); }
  void truncate( branch const &truncate_target );
  index_type contains( branch const & ) const noexcept;

  TEMPLATE_HEAD_BRANCH
  inline branch &operator+=( T const &rhs ) noexcept { return this->addBranch<T>( rhs ); }

  TEMPLATE_HEAD_BRANCH
  friend inline branch operator+( branch const &lhs, T const &rhs ) noexcept { return branch( lhs ) += rhs; }

  friend inline bool operator==( branch const &lhs, branch const &rhs ) noexcept {
    return lhs.buildBranch() == rhs.buildBranch();
  }
  friend inline bool operator!=( branch const &lhs, branch const &rhs ) noexcept { return !( lhs == rhs ); }

  std::string const &operator[]( std::size_t const index ) const noexcept { return path_element_[index]; }

  inline std::size_t size() const noexcept { return path_element_.size(); }

  iterator begin() noexcept { return path_element_.begin(); }
  iterator end() noexcept { return path_element_.end(); }
  const_iterator cbegin() const noexcept { return path_element_.cbegin(); }
  const_iterator cend() const noexcept { return path_element_.cend(); }
  reverse_iterator rbegin() noexcept { return path_element_.rbegin(); }
  reverse_iterator rend() noexcept { return path_element_.rend(); }
  const_reverse_iterator crbegin() const noexcept { return path_element_.crbegin(); }
  const_reverse_iterator crcend() const noexcept { return path_element_.crend(); }

  explicit operator std::filesystem::path() const { return std::filesystem::path( buildBranch() ); }

private:
  std::vector<std::string> path_element_;

  std::string buildBranch() const noexcept;
  bool isRoot( container_type::const_iterator ) const noexcept;
  bool isCurrentDirectory( container_type::const_iterator ) const noexcept;

  TEMPLATE_HEAD_BRANCH
  branch &addBranch( T const &branchable ) noexcept {
    if constexpr ( std::is_same_v<T, branch> ) {
      path_element_.insert( path_element_.end(), branchable.path_element_.begin(), branchable.path_element_.end() );
    } else {
      path_element_.emplace_back( branchable );
    }
    return *this;
  }
};

}  // namespace path

}  // namespace crep

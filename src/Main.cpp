/****************************************
 ****************************************/

// std
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#if defined( MSC_VER ) && defined( _MSVC_LANG )
#  define CXX_STD _MSVC_LANG
#else
#  define CXX_STD __cplusplus
#endif

/* C++17 was when filesystems entered the c++ standard. */
#if CXX_STD >= 201703
#  include <filesystem>
#endif

int main( int argc, char const * argv[] ) {
  // スケルトンプログラムを保管しているディレクトリを設定する。
#ifdef _WIN32
  std::string skeleton_dir( std::getenv( "LocalAppData" ) );
  if ( skeleton_dir == nullptr ) {
    std::cerr << "The environment variable \"LOCALAPPDATA\" is not defined." << std::endl;
    return -1;
  }
#elif __linux__
  char const * home_dir = std::getenv( "HOME" );
  if ( home_dir == nullptr ) {
    std::cerr << "The environment variable \"LOCALAPPDATA\" is not defined." << std::endl;
    return -1;
  }
  std::string skeleton_dir = std::string( home_dir ) + std::string( "\\.config\\crep" );
#endif
  std::string const skeleton_name = ".cpp_skeleton";
  std::string const program_name = "crep";
  std::string const skeleton_path = std::string( skeleton_dir ) + '\\' + program_name + '\\' + skeleton_name;

  bool is_project_skeleton_exist = std::filesystem::is_directory( skeleton_path );

  if ( !is_project_skeleton_exist ) {
    std::cerr << "Tere is NOT project skeleton in " << skeleton_path << std::endl;
  }

  // コピー元のリストを作成
  std::filesystem::directory_iterator d_itr( skeleton_path ), end;

  std::vector<std::string> file_paths;

  for ( ; d_itr != end; ++d_itr ) {
    const std::filesystem::directory_entry entry = *d_itr;

    file_paths.emplace_back( entry.path().string() );
  }

  for ( auto itr : file_paths ) {
    std::cout << "file_path : " << itr << std::endl;
  }

  return 0;
}

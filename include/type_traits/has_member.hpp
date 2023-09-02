/*****************************
 * type_traits/has_member.hpp
 *****************************/

#pragma once

#define PP_CONCATENATE( STR1, STR2 ) PP_CONCATENATE_IMPL( STR1, STR2 )
#define PP_CONCATENATE_IMPL( STR1, STR2 ) STR1##STR2

#define WINDOW_ARG_NUM( ... ) WINDOW_ARG_NUM_IMPL( __VA_ARGS__ )
#define WINDOW_ARG_NUM_IMPL( dummy0, dummy1, dummy2, dummy3, dummy4, dummy5, dummy6, dummy7, size, ... ) size
#define ARG_NUM( ... ) WINDOW_ARG_NUM( __VA_ARGS__, ARG_NUM_LIST )
#define ARG_NUM_LIST 8, 7, 6, 5, 4, 3, 2, 1

#define IMPLEMENT_CHECKER( TYPE_ALIAS, CLASS_NAME, FEATURE_NAME )               \
  template <typename MaybeCallable>                                             \
  struct CLASS_NAME {                                                           \
  private:                                                                      \
    template <typename TargetT, typename = decltype( TargetT::FEATURE_NAME() )> \
    STATIC_CONSTEXPR auto check( TargetT const & ) -> std::true_type;           \
    STATIC_CONSTEXPR auto check( ... ) -> std::false_type;                      \
                                                                                \
  public:                                                                       \
    using type = decltype( check( std::declval<MaybeCallable>() ) );            \
  };                                                                            \
                                                                                \
  template <typename T>                                                         \
  using TYPE_ALIAS = typename CLASS_NAME<T>::type;

#define MAKE_ALIAS_NAME( BASE_NAME ) MAKE_ALIAS_NAME_IMPL( has_, BASE_NAME, _t )
#define MAKE_ALIAS_NAME_IMPL( PREFIX, BASE_NAME, SUFFIX ) PP_CONCATENATE( PP_CONCATENATE( PREFIX, BASE_NAME ), SUFFIX )
#define MAKE_CLASS_NAME( BASE_NAME ) PP_CONCATENATE( has_, BASE_NAME )

// MAKE_CHECKER2、機能名をそのまま使うとエラーとなるような
// メンバーに対するhas_xxxを作りたいときに使う。例えばoperator*など。
#define MAKE_CHECKER_1( FEATURE_NAME ) \
  IMPLEMENT_CHECKER( MAKE_ALIAS_NAME( FEATURE_NAME ), MAKE_CLASS_NAME( FEATURE_NAME ), FEATURE_NAME )
#define MAKE_CHECKER_2( CLASS_NAME, FEATURE_NAME ) \
  IMPLEMENT_CHECKER( MAKE_ALIAS_NAME( CLASS_NAME ), MAKE_CLASS_NAME( CLASS_NAME ), FEATURE_NAME )

#define MAKE_HAS_MEMBER_CHECKER( ... ) \
  MAKE_HAS_MEMBER_CHECKER_IMPL( MAKE_CHECKER_, ARG_NUM( __VA_ARGS__ ), __VA_ARGS__ )
#define MAKE_HAS_MEMBER_CHECKER_IMPL( SUFFIX, ARGUMENT_NUM, ... ) \
  PP_CONCATENATE( MAKE_CHECKER_, ARGUMENT_NUM )( __VA_ARGS__ )

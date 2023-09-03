/*****************************
 * type_traits/has_member.hpp
 *****************************/

#pragma once

#define PP_CONCATENATE( STR1, STR2 ) PP_CONCATENATE_IMPL( STR1, STR2 )
#define PP_CONCATENATE_IMPL( STR1, STR2 ) STR1##STR2

#define MEMBER_TYPE_CHECKER( TYPE_ALIAS, CLASS_NAME, TYPE )            \
  template <typename MaybeHasTheType>                                  \
  struct CLASS_NAME {                                                  \
  private:                                                             \
    template <typename TargetT, typename = decltype( TargetT::TYPE )>  \
    STATIC_CONSTEXPR auto check( TargetT const & ) -> std::true_type;  \
    STATIC_CONSTEXPR auto check( ... ) -> std::false_type;             \
                                                                       \
  public:                                                              \
    using type = decltype( check( std::declval<MaybeHasTheType>() ) ); \
  };                                                                   \
                                                                       \
  template <typename T>                                                \
  using TYPE_ALIAS = typename CLASS_NAME<T>::type;

#define MAKE_CLASS_NAME( BASE_NAME ) PP_CONCATENATE( has_, BASE_NAME )
#define MAKE_ALIAS_NAME( BASE_NAME ) MAKE_ALIAS_NAME_IMPL( BASE_NAME, _t )
#define MAKE_ALIAS_NAME_IMPL( BASE_NAME, SUFFIX ) PP_CONCATENATE( MAKE_CLASS_NAME( BASE_NAME ), SUFFIX )

#define MAKE_TYPE_HAS( TYPE_NAME ) \
  MEMBER_TYPE_CHECKER( MAKE_ALIAS_NAME( TYPE_NAME ), MAKE_CLASS_NAME( TYPE_NAME ), TYPE_NAME )

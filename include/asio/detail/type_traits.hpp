//
// detail/type_traits.h
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_DETAIL_TYPE_TRAITS_HPP
#define ASIO_DETAIL_TYPE_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"

#if defined(ASIO_HAS_STD_TYPE_TRAITS)
# include <type_traits>
#else // defined(ASIO_HAS_STD_TYPE_TRAITS)
# include <boost/type_traits/add_const.h>
# include <boost/type_traits/add_lvalue_reference.h>
# include <boost/type_traits/aligned_storage.h>
# include <boost/type_traits/alignment_of.h>
# include <boost/type_traits/conditional.h>
# include <boost/type_traits/decay.h>
# include <boost/type_traits/has_nothrow_copy.h>
# include <boost/type_traits/has_nothrow_destructor.h>
# include <boost/type_traits/integral_constant.h>
# include <boost/type_traits/is_base_of.h>
# include <boost/type_traits/is_class.h>
# include <boost/type_traits/is_const.h>
# include <boost/type_traits/is_convertible.h>
# include <boost/type_traits/is_constructible.h>
# include <boost/type_traits/is_copy_constructible.h>
# include <boost/type_traits/is_destructible.h>
# include <boost/type_traits/is_function.h>
# include <boost/type_traits/is_object.h>
# include <boost/type_traits/is_same.h>
# include <boost/type_traits/remove_cv.h>
# include <boost/type_traits/remove_pointer.h>
# include <boost/type_traits/remove_reference.h>
# include <boost/utility/declval.h>
# include <boost/utility/enable_if.h>
# include <boost/utility/result_of.h>
#endif // defined(ASIO_HAS_STD_TYPE_TRAITS)

namespace asio {

#if defined(ASIO_HAS_STD_TYPE_TRAITS)
using std::add_const;
using std::add_lvalue_reference;
using std::aligned_storage;
using std::alignment_of;
using std::conditional;
using std::decay;
using std::declval;
using std::enable_if;
using std::false_type;
using std::integral_constant;
using std::is_base_of;
using std::is_class;
using std::is_const;
using std::is_constructible;
using std::is_convertible;
using std::is_copy_constructible;
using std::is_destructible;
using std::is_function;
using std::is_move_constructible;
using std::is_nothrow_copy_constructible;
using std::is_nothrow_destructible;
using std::is_object;
using std::is_reference;
using std::is_same;
using std::is_scalar;
using std::remove_cv;
template <typename T>
struct remove_cvref : remove_cv<typename std::remove_reference<T>::type> {};
using std::remove_pointer;
using std::remove_reference;
#if defined(ASIO_HAS_STD_INVOKE_RESULT)
template <typename> struct result_of;
template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};
#else // defined(ASIO_HAS_STD_INVOKE_RESULT)
using std::result_of;
#endif // defined(ASIO_HAS_STD_INVOKE_RESULT)
using std::true_type;
#else // defined(ASIO_HAS_STD_TYPE_TRAITS)
using boost::add_const;
using boost::add_lvalue_reference;
using boost::aligned_storage;
using boost::alignment_of;
template <bool Condition, typename Type = void>
struct enable_if : boost::enable_if_c<Condition, Type> {};
using boost::conditional;
using boost::decay;
using boost::declval;
using boost::false_type;
using boost::integral_constant;
using boost::is_base_of;
using boost::is_class;
using boost::is_const;
using boost::is_constructible;
using boost::is_convertible;
using boost::is_copy_constructible;
using boost::is_destructible;
using boost::is_function;
#if defined(ASIO_HAS_MOVE)
template <typename T>
struct is_move_constructible : false_type {};
#else // defined(ASIO_HAS_MOVE)
template <typename T>
struct is_move_constructible : is_copy_constructible<T> {};
#endif // defined(ASIO_HAS_MOVE)
template <typename T>
struct is_nothrow_copy_constructible : boost::has_nothrow_copy<T> {};
template <typename T>
struct is_nothrow_destructible : boost::has_nothrow_destructor<T> {};
using boost::is_object;
using boost::is_reference;
using boost::is_same;
using boost::is_scalar;
using boost::remove_cv;
template <typename T>
struct remove_cvref : remove_cv<typename boost::remove_reference<T>::type> {};
using boost::remove_pointer;
using boost::remove_reference;
using boost::result_of;
using boost::true_type;
#endif // defined(ASIO_HAS_STD_TYPE_TRAITS)

template <typename> struct void_type { typedef void type; };

#if defined(ASIO_HAS_VARIADIC_TEMPLATES)

template <typename...> struct conjunction : true_type {};
template <typename T> struct conjunction<T> : T {};
template <typename Head, typename... Tail> struct conjunction<Head, Tail...> :
  conditional<Head::value, conjunction<Tail...>, Head>::type {};

#endif // defined(ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace asio

#endif // ASIO_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_MP11_DETAIL_MP_MAP_FREEZE_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_MAP_FREEZE_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/list.hpp>

namespace boost
{
namespace mp11
{

// mp_map_freeze
namespace detail
{

template<class... T> struct mp_frozen_map {};

template<class E> struct mp_frozen_map_entry;

template<template<class...> class E, class K, class... U> struct mp_frozen_map_entry<E<K, U...>>
{
    static E<K, U...> f(K*);
};

#if __cplusplus >= 201406L
template<class... T> struct mp_frozen_map_find : mp_frozen_map_entry<T>...
{
    using mp_frozen_map_entry<T>::f...;

    static void f(...);
};
#else
template<class... T> struct mp_frozen_map_find;

template<class T0, class... T> struct mp_frozen_map_find<T0, T...> : mp_frozen_map_entry<T0>, mp_frozen_map_find<T...>
{
    using mp_frozen_map_entry<T0>::f;
    using mp_frozen_map_find<T...>::f;
};

template<> struct mp_frozen_map_find<>
{
    static void f(...);
};
#endif

} // namespace detail

template<class M> using mp_map_freeze = mp_rename<M, detail::mp_frozen_map>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_MAP_FREEZE_HPP_INCLUDED

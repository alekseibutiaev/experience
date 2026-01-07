#pragma once
#include <iterator>

// #define __cplusplus 199711L c++03
// #define __cplusplus 201103L c++11
// #define __cplusplus 201402L c++14
// #define __cplusplus 201703L c++17

#if __cplusplus < 201103L

#include <boost/optional.hpp>

namespace std {

  template<template type_t, std::size_t N >
  type_t* begin(type_t(&a)[N]) {
    return &a[0];
  }

  template<template type_t, std::size_t N >
  type_t* end(type_t(&a)[N]) {
    return &a[N];
  }

  template<typename type_t>
  using optional = boost::optional<type_t>;

} /* namespace std */
#endif

#if __cplusplus < 201703L

#include <boost/optional.hpp>

namespace std {

  template <typename type_t, std::size_t N>
  std::size_t size(const type_t(&)[N]) noexcept {
    return N;
  }

  template <typename container_t> 
  constexpr auto size(const container_t& c) -> decltype(c.size()) {
    return c.size();
  }

  template<typename type_t>
  using optional = boost::optional<type_t>;

} /* namespace std */

#endif

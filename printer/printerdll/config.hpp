#pragma once

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <boost/config.hpp>

#if defined( BOOST_ALL_DYN_LINK ) || defined( BOOST_PRINTERDLL_SOURCE )
# if defined( BOOST_PRINTERDLL_SOURCE )
#   define BOOST_PRINTERDLL_DECL BOOST_SYMBOL_EXPORT
# else
#   define BOOST_PRINTERDLL_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define BOOST_PRINTERDLL_DECL
#endif

#endif /* __CONFIG_HPP__ */
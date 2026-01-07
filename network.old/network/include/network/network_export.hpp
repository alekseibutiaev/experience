#pragma once

#ifndef __NETWORK_NETWORK_EXPORT_HPP__
#define __NETWORK_NETWORK_EXPORT_HPP__

#include <boost/config.hpp>

#if defined( NETWORK_SOURCES )
#define NETWORK_SYMBOL BOOST_SYMBOL_EXPORT
#else
#define NETWORK_SYMBOL BOOST_SYMBOL_IMPORT
#endif

#endif /* __NETWORK_NETWORK_EXPORT_HPP__ */
#pragma once

#ifndef __WINDLL_EXPORT_H__
#define __WINDLL_EXPORT_H__

#if defined( BUILD_DLL ) && defined( SOURCES )
#define EXPORT_SYMBOL __declspec( dllexport )
#define EXTERN_IMPLEMENTATION_TEMPLATE
#else
#define EXPORT_SYMBOL __declspec( dllimport )
//#define EXTERN_IMPLEMENTATION_TEMPLATE extern
#define EXTERN_IMPLEMENTATION_TEMPLATE
#endif

#endif /* __WINDLL_EXPORT_H__ */

#pragma once

#ifndef __WINDLL_C_H__
#define __WINDLL_C_H__

#include "windll_export.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

double EXPORT_SYMBOL multiply( double f_a, double f_b ); 

#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* __WINDLL_C_H__ */

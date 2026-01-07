#ifndef __opensslconf_h__
#define __opensslconf_h__

#if defined(_WIN64)
#include <openssl/opensslconf64.h>
#else
#include <openssl/opensslconf32.h>
#endif

#endif __opensslconf_h__

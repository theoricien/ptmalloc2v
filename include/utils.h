#ifndef _UTILS_H
#define _UTILS_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ptassert.h"
#include "arch/config.h"

addr_t * ptm2v_array (addr_t, ...);

char * multi_fmt (const char *);

#endif // _UTILS_H

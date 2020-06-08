#ifndef _PTASSERT_H
#define _PTASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

void ptassert  (int, const char *, ...);
void ptasserte (int);

#endif // _PTASSERT_H

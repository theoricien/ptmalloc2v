#ifndef _PTASSERT_H
#define _PTASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

/*
 * ptassert.h header file consist
 * of assertion-like functions for this project.
 */

// Classic one, use it like printf format for customizable error message
void ptassert   (int, const char *, ...);

// Return the errno error message
void ptasserte  (int);

// Return the dlerror() message
void ptassertdl (int);

#endif // _PTASSERT_H

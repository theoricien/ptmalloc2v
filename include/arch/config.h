#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>
#include <stdlib.h>

#if __GNUC__
// If GCC
#if __X86_64__ || __ppc64__ || _____LP64_____  || UINTPTR_MAX == 0xffffffffffffffff
// If 64 bit system
#include "arch/x86-64.h"
#else
// Else we use 32 bit system
#include "arch/x86.h"
#endif // __X86_64__ || __ppc64__
#else
// By default we think we are on 32 bit system
#include "arch/x86.h"
#endif // __GNUC__

#endif // _CONFIG_H

#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdint.h>
#include <stdlib.h>

/*
 * = heap_base + 0x10
 * GDB won't allow you to print any information about tcache
 * PwnDBG do.
 * Steps to reproduce to re-find this offset:
 * -Install PwnDBG
 * -break at the end of main & run
 * -pwndbg> info proc mapping // Take the heap base
 * -pwndbg> tcache
 * -pwndbg> find <[heap] base>,+99999,<info of tcache>
 */
#define OFF_TCACHE 0x10

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

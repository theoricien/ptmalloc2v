#ifndef _X86_64_H
#define _X86_64_H

#define AMD64

#define __ADDR_SIZE 16

// __GI___libc_malloc + OFFSET = &main_arena
#define OFF_MAIN_ARENA 0x1378f0

/*
 * In 64 bits, size_t = unsigned long int = 8 bytes.
 * And MALLOC_ALIGNEMENT == 2 * sizeof(size_t)
 * So logically, NSMALLBINS = 64 = (NSMALLBINS - MALLOC_ALIGNEMENT > 2 * sizeof(size_t))
 * So the min larg size of a large bin is of 64 * 16 = 1024
 */
// (NSMALLBINS - SMALLBIN_CORRECTION) * SMALLBIN_WIDTH)
#define MIN_LARGE_SIZE 1024

// Define the address type, we just can't read the referenced value
typedef long * addr_t;

#endif // _X86_64_H
